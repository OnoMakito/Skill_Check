

#define CONIOEX
#include "conioex.h"



void animeA2A(char E2[5])	//ìÒêlñ⁄çUåÇé∏îséû
{
	gotoxy(34, 16);
	if (strcmp(E2, "ñ≥") == 0)
	{
		textcolor(LIGHTGRAY);
	}
	if (strcmp(E2, "âä") == 0)
	{
		textcolor(LIGHTRED);
	}
	if (strcmp(E2, "êÖ") == 0)
	{
		textcolor(LIGHTCYAN);
	}
	if (strcmp(E2, "óã") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E2, "ïó") == 0)
	{
		textcolor(LIGHTGREEN);
	}
	if (strcmp(E2, "à≈") == 0)
	{
		textcolor(LIGHTMAGENTA);
	}
	if (strcmp(E2, "åı") == 0)
	{
		textcolor(YELLOW);
	}
	printf("Åü ");
	textcolor(WHITE);
	printf("éO = --Å_(ﬂÑDﬂéO = \n\n");
	gotoxy(25, 17);
	printf("(''ﬂÑDﬂ)≥‹Ø!\n\n");
}
