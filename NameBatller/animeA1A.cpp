
#define CONIOEX
#include "conioex.h"



void animeA1A(char E1[5])	//��l�ڍU�����s��	
{
	gotoxy(24, 16);
	printf(" =�O߄D�)�m --=�O ");
	if (strcmp(E1, "��") == 0)
	{
		textcolor(LIGHTGRAY);
	}
	if (strcmp(E1, "��") == 0)
	{
		textcolor(LIGHTRED);
	}
	if (strcmp(E1, "��") == 0)
	{
		textcolor(LIGHTCYAN);
	}
	if (strcmp(E1, "��") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E1, "��") == 0)
	{
		textcolor(LIGHTGREEN);
	}
	if (strcmp(E1, "��") == 0)
	{
		textcolor(LIGHTMAGENTA);
	}
	if (strcmp(E1, "��") == 0)
	{
		textcolor(YELLOW);
	}
	printf(" ��");
	textcolor(WHITE);
	gotoxy(34, 17);
	printf("���ȯ(߄D��')�\n\n");
}