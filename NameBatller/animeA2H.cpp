
#define CONIOEX
#include "conioex.h"

void animeA2H(char E2[5])	//��l�ڍU���q�b�g��
{
	gotoxy(25, 16);
	printf("��ʯ(߄D�(");
	if (strcmp(E2, "��") == 0)
	{
		textcolor(LIGHTGRAY);
	}
	if (strcmp(E2, "��") == 0)
	{
		textcolor(LIGHTRED);
	}
	if (strcmp(E2, "��") == 0)
	{
		textcolor(LIGHTCYAN);
	}
	if (strcmp(E2, "��") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E2, "��") == 0)
	{
		textcolor(LIGHTGREEN);
	}
	if (strcmp(E2, "��") == 0)
	{
		textcolor(LIGHTMAGENTA);
	}
	if (strcmp(E2, "��") == 0)
	{
		textcolor(YELLOW);
	}
	printf("�� ");
	textcolor(WHITE);
	printf("�O = --�_(߄DߎO = \n\n");
}