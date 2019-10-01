
#define CONIOEX
#include "conioex.h"

void animeA2H(char E2[5])	//二人目攻撃ヒット時
{
	gotoxy(25, 16);
	printf("ｸﾞﾊｯ(ﾟДﾟ(");
	if (strcmp(E2, "無") == 0)
	{
		textcolor(LIGHTGRAY);
	}
	if (strcmp(E2, "炎") == 0)
	{
		textcolor(LIGHTRED);
	}
	if (strcmp(E2, "水") == 0)
	{
		textcolor(LIGHTCYAN);
	}
	if (strcmp(E2, "雷") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E2, "風") == 0)
	{
		textcolor(LIGHTGREEN);
	}
	if (strcmp(E2, "闇") == 0)
	{
		textcolor(LIGHTMAGENTA);
	}
	if (strcmp(E2, "光") == 0)
	{
		textcolor(YELLOW);
	}
	printf("◆ ");
	textcolor(WHITE);
	printf("三 = --＼(ﾟДﾟ三 = \n\n");
}