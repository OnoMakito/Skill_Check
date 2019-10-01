
#define CONIOEX
#include "conioex.h"

#define NEND 0		//exit�֐��F����I��
#define  ABEND 1	//exit�֐��F�ُ�I��


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


int datadelete(int notsaved)
{
	int select = 0;

	for (;;)
	{
		system("cls");

		textcolor(LIGHTRED);
		gotoxy(34, 15);
		printf("���ӁI");
		gotoxy(20, 16);
		printf("�ۑ����ꂽ�f�[�^���폜����܂��I");	//�폜�x��
		gotoxy(24, 17);
		printf("�������f�[�^�͖߂��܂���");


		textcolor(WHITE);
		gotoxy(26, 19);
		printf("�{���ɍ폜���܂����H");		//�ŏI�m�F
		gotoxy(29, 21);
		printf("Yes: 9   No:0\n");

		select = getch();	//���[�U�̑I��



		if (select == '9')	//�P���w�肵���ꍇ(����ȊO�͉������Ȃ�)
		{
			FILE *fp;

			fp = fopen("�f�[�^�t�@�C��.csv", "wb");

			if (fp == NULL)
			{
				printf("�f�[�^�̍폜�Ɏ��s���܂����B\n�v���O�������I�����܂��B");
				getch();
				exit(ABEND);
			}

			fwrite(NULL, 0, 1, fp);

			fclose(fp);	//�t�@�C�������

			for (int i = 0; i < 4; i++)		//�e�L�����N�^�[�X�e�[�^�X������
			{
				strcpy(character[i].name, "");
				character[i].hp = 0;
				character[i].mp = 0;
				character[i].def = 0;
				character[i].speed = 0;
				strcpy(character[i].element, "");
				strcpy(character[i].skill, "");
				character[i].existance = 0;

			}

			notsaved = 0;	//���ׂẴf�[�^�������Z�[�u�̕K�v���Ȃ��Ȃ������߁A���j���[�ȂǂŋN����Z�[�u�����{�̌x������������

			system("cls");
			printf("�f�[�^���폜���܂����B");
			getch();
			return notsaved;
		}
		else if (select == '0')
		{
			return notsaved;
		}

	}


}