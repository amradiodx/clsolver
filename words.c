#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "includes.h"
#include "words.h"
#include "verify.h"


char usedltrs[6];

void getguess(char* g)
{
	do
	{
		printf("\nPlease enter valid word to start: ");
		fgets(g, 6, stdin);
		printf("Guess is %s\n", g);
		char* newln = strrchr(g, '\n');
		if(newln == NULL)
		{
			char c = getchar();
			if(c == '\n')
			{
				printf("Newline found!\n");
			}
		}	
	} while(verifyword(g) == 0);
}

void getresults(char* r)
{
	do
	{
		printf("\nPlease entire valid results: ");
		fgets(r, 6, stdin);
		char* newln = strrchr(r, '\n');
		if(newln == NULL)
		{
			char c = getchar();
			if(c == '\n')
			{
				printf("Newline found!\n");
			}
		}
	} while(verifyresults(r) == 0);
}

void addtousedltrs(char c)
{
}


void getunusedltrs(char iw[], char rw[], char unused[], char used[])
{
	int unusedidx = 0;
	int usedidx = 0;
	memset(used, '\0', CLWSTRLEN + 1);
	memset(unused, '\0', CLWSTRLEN + 1);
	for(int i = 0; i < CLWSTRLEN; ++i)
	{
		if(rw[i] != '-')
		{
			used[usedidx++] = iw[i];
		}
	}
	for(int i = 0; i < CLWSTRLEN; ++i)
	{
		if((rw[i] == '-') && (strchr(used, iw[i]) == NULL))
		{
			unused[unusedidx++] = iw[i];
		}
	}
}


bool ispossibleword(char gs[], char w[], char r[], char u[])
{
	char wwork[7];
	char rwork[7];

	strncpy(wwork, w, 7);
	strncpy(rwork, r, 7);

	/* Check for unused letters */
	size_t spn = strcspn(w, u);
	if(spn != strlen(wwork))
	{
		return false;
	}

	/* Check for exact matches */
	for(int i = 0; i < CLWSTRLEN; ++i)
	{
		if(gs[i] == wwork[i])
		{
			/* Possible word if green */
			if(rwork[i] == 'g')
			{
				rwork[i] = '-';
				wwork[i] = '-';
			}
			else
			{
				return false;
			}
		}
	}

	/* Loop through results looking for yellow letters */
	for(int i = 0; i < CLWSTRLEN; ++i)
	{
		if(rwork[i] == 'y')
		{
			for(int j = 0; j < CLWSTRLEN; ++j)
			{
				if(i == j) continue;
				if((gs[i] == wwork[j]) /* && (i != j) && (gs[i] != wwork[i]) */)
				{
					rwork[i] = '-';
					wwork[j] = '-';
					break;
				}
			}
		}
	}
	if(strncmp(rwork, "-----", CLWSTRLEN) == 0)
	{
		return true;
	}

	return false;
} 

bool issolved(char r[])
{
	return strncmp(r, SOLVED, strlen(SOLVED)) == 0;
}
