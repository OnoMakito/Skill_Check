
#define CONIOEX

#include "conioex.h"

typedef struct	//status�^�̍쐬
{
	char name[35];
	float hp;
	int mp;
	int def;
	int speed;
	char element[6];
	char skill[35];
	int existance;
}status;

extern status character[4];

void check()	//�L�����N�^�[�ڍ׏��m�F
{
	system("cls");
	printf("\n���݂̃L�����N�^�[\n\n");

	for (int i = 0; i < 4; i++)
	{
		printf("\n%d�Ԗ�\n���O�F%s\n�̗́F%.0f         ���́F%d       �h��́F%d       ���x:%d\n�U�������F", i + 1, character[i].name, character[i].hp, character[i].mp, character[i].def, character[i].speed);	//�S���̃X�e�[�^�X�\��

																																															//�������ƂɃe�L�X�g�J���\��ς���	
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(LIGHTGRAY);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(LIGHTRED);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(LIGHTCYAN);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(YELLOW);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(LIGHTGREEN);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(LIGHTMAGENTA);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(YELLOW);
		}
		printf("%s", character[i].element);

		textcolor(WHITE);

		printf("       �X�L�����F");

		if (strcmp(character[i].element, "��") == 0)	//�������ƂɃX�L�����Ɏg���e�L�X�g�J���\��ݒ�
		{
			textcolor(LIGHTGRAY);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(LIGHTRED);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(LIGHTCYAN);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(YELLOW);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(LIGHTGREEN);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(LIGHTMAGENTA);
		}
		if (strcmp(character[i].element, "��") == 0)
		{
			textcolor(YELLOW);
		}

		printf("%s\n", character[i].skill);
		textcolor(WHITE);
		printf("\n---------------------------------------------------------------");
	}
	getch();

	return;
}