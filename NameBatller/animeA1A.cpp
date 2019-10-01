
#define CONIOEX
#include "conioex.h"



void animeA1A(char E1[5])	//àÍêlñ⁄çUåÇé∏îséû	
{
	gotoxy(24, 16);
	printf(" =éOﬂÑDﬂ)Ém --=éO ");
	if (strcmp(E1, "ñ≥") == 0)
	{
		textcolor(LIGHTGRAY);
	}
	if (strcmp(E1, "âä") == 0)
	{
		textcolor(LIGHTRED);
	}
	if (strcmp(E1, "êÖ") == 0)
	{
		textcolor(LIGHTCYAN);
	}
	if (strcmp(E1, "óã") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E1, "ïó") == 0)
	{
		textcolor(LIGHTGREEN);
	}
	if (strcmp(E1, "à≈") == 0)
	{
		textcolor(LIGHTMAGENTA);
	}
	if (strcmp(E1, "åı") == 0)
	{
		textcolor(YELLOW);
	}
	printf(" Åü");
	textcolor(WHITE);
	gotoxy(34, 17);
	printf("±Ãﬁ»Ø(ﬂÑDﬂ…')…\n\n");
}