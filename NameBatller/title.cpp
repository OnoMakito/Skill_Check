
#define CONIOEX
#define  ABEND 1	//exit�֐��F�ُ�I��

#include "conioex.h"

extern int mmf;

void title()
{


	//�T�E���h�Ɋւ��钍�ӊ��N�y�у��C�Z���X�\��
	textcolor(LIGHTRED);
	gotoxy(28, 18);
	printf("���ӁF�����o�܂��I");
	gotoxy(28, 20);
	printf("-Please  Anykey-");
	textcolor(WHITE);
	gotoxy(9, 36);
	printf("�t���[�z�z�y�Ȏg�p");
	gotoxy(9, 37);
	printf("��ȎҁF�@Mr.Kimy�@MAKOOTO�@�J���T�L���X�q��");
	gotoxy(9, 38);
	printf("�z�z�T�C�g�FDova-Symdorome");

	getch();



	//////�^�C�g���A�j���[�V�����J�n
	system("cls");
	gotoxy(24, 1);
	printf("�l�@�[�@���@�o�@�g�@���@�[");
	Sleep(80);
	system("cls");
	gotoxy(24, 2);
	printf("�l�@�[�@���@�o�@�g�@���@�[");
	Sleep(80);
	for (int i = 0; i <= 11; i++)
	{
		gotoxy(1, 1);

		insline();
		Sleep(80);
	}


	system("cls");

	Sleep(250);

	srand(timeGetTime());

	for (int i = 0; i <= 1000; i++)	//��i���̔w�i��W�J(���ׂďo�͂���̂Ƀ��O�����邪�A������A�j���[�V�����Ƃ��Ĉ����B)
	{
		int x = rand() % 100;
		for (x; x >= 71;)
		{
			x = rand() % 100;
		}

		int y = rand() % 100;
		for (y; y >= 41;)
		{
			y = rand() % 100;
		}

		switch (x % 10)
		{
		case 1:
		case 2:
			textcolor(RED);
			break;
		case 3:
		case 4:
			textcolor(BLUE);
			break;
		case 5:
		case 6:
			textcolor(GREEN);
			break;
		case 7:
		case 8:
			textcolor(MAGENTA);
			break;
		case 9:
		case 0:
			textcolor(CYAN);
			break;
		}

		gotoxy(x, y);
		if (rand() % 10 >= 5)
		{
			printf("0");
		}
		else
		{
			printf("1");
		}

		if (i % 100 == 50)
		{
			Sleep(5);
		}
	}


	//�O���f�[�V������i���W�J(�^�C�g���㕔)
	gotoxy(1, 13);
	textcolor(LIGHTCYAN);
	printf("1110001");
	textcolor(CYAN);
	printf("0001011");
	textcolor(LIGHTBLUE);
	printf("1000111");
	textcolor(MAGENTA);
	printf("0101011");
	textcolor(LIGHTMAGENTA);
	printf("0110010");
	textcolor(LIGHTRED);
	printf("1010110");
	textcolor(YELLOW);
	printf("1001101");
	textcolor(LIGHTGREEN);
	printf("0110011");
	textcolor(GREEN);
	printf("0010101");
	textcolor(DARKGRAY);
	printf("0010100");


	//�Q�[�����W�J
	textcolor(LIGHTRED);
	gotoxy(5, 14);
	printf("                  __________________________                    "); gotoxy(5, 15);
	printf(" _  _ __�Q�^�^�^�^   �l �[ �� �o �g �� �[   �_�_�_�_�Q__ _  _   "); gotoxy(5, 16);
	printf("�@        �_�_�_�________Name.Battler_______�^�^�^�^            "); gotoxy(5, 17);
	printf("                     �P�P�P�P�P�P�P�P�P�P                       ");


	//�O���f�[�V������i���W�J(�^�C�g������)
	gotoxy(1, 18);
	textcolor(DARKGRAY);
	printf("0010100");
	textcolor(GREEN);
	printf("0010101");
	textcolor(LIGHTGREEN);
	printf("0110011");
	textcolor(YELLOW);
	printf("1001101");
	textcolor(LIGHTRED);
	printf("1010110");
	textcolor(LIGHTMAGENTA);
	printf("0110010");
	textcolor(MAGENTA);
	printf("0101011");
	textcolor(LIGHTBLUE);
	printf("1000111");
	textcolor(CYAN);
	printf("0001011");
	textcolor(LIGHTCYAN);
	printf("1110001");


	//����Җ��y�я������\��
	gotoxy(9, 39);
	printf("����F�g�`�k�����@�`�s�P�P�d�\�R�S�P�@�P�R�ԁ@����q�l");



	//�^�C�g�������ׂĕ\�����ꂽ��A���j���[�Ȃ��J�n
	playsound(mmf, 1);


	//���炩�̓��͂��󂯕t���A���̃Q�[���̓����E��|�����
	getch();
	textcolor(LIGHTCYAN);
	gotoxy(23, 23);
	printf("�l�[���o�g���[�ւ悤�����I"); gotoxy(5, 24);
	printf("���̐��E�ł̓L�����N�^�[�̖��O�����Ƀp�����[�^�����肳��܂��I");
	gotoxy(5, 26);
	printf("���������A���Ȃ������̍ŋ��̃L�����N�^�[�������o���܂��傤�I");

	textcolor(WHITE);

	getch();


}