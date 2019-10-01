#define CONIOEX
#include "conioex.h"

void animeA1H(char E1[5])	//一人目攻撃ヒット時
{
	gotoxy(24, 16);
	printf(" =三ﾟДﾟ)ノ --=三 ");
	if (strcmp(E1, "無") == 0)
	{
		textcolor(LIGHTGRAY);
	}
	if (strcmp(E1, "炎") == 0)
	{
		textcolor(LIGHTRED);
	}
	if (strcmp(E1, "水") == 0)
	{
		textcolor(LIGHTCYAN);
	}
	if (strcmp(E1, "雷") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E1, "風") == 0)
	{
		textcolor(LIGHTGREEN);
	}
	if (strcmp(E1, "闇") == 0)
	{
		textcolor(LIGHTMAGENTA);
	}
	if (strcmp(E1, "光") == 0)
	{
		textcolor(YELLOW);
	}
	printf(" ◆");
	textcolor(WHITE);
	printf(")ﾟДﾟ)ｷﾞｬｰ!\n\n");
}