
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



int battle_disp(float H1, float H2, int M1, int M2, float D1, float D2, char E1[6], char E2[6], int select1, int select2)		//�퓬�p���
{



	int icon = H1 / character[select1 - '1'].hp * 10;	//��l�ڂ̌�HP�ƍő�HP���r�����ۂ̊���
	int icon2 = H2 / character[select2 - '1'].hp * 10;//��l�ڂ̌�HP�ƍő�HP���r�����ۂ̊���

													  ///////////////////////////////////////////////////////////////////////////
													  //��l�ڕ\��
	int count = 0;	//HP�A�C�R���v���ϐ�

	system("cls");


	if (H1 < 0)
	{
		H1 = 0;		//�̗͂��}�C�i�X�̒l�ɂȂ�Ȃ��悤�ɂ���B
	}


	printf("�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q\n");
	printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@| �̗́F%.0f\n", H1);
	printf("|�@�@�@");



	printf("%s", character[select1 - '1'].name);		//���O

	for (int i = 0; i < 38 - strlen(character[select1 - '1'].name); i++)
	{
		printf(" ");			//���O����̋�
	}

	printf("|�@�@�@�@�@  ���́F%d\n", M1);	//�󔒂̏I���

	printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@| �����F");

	if (strcmp(E1, "��") == 0 || strcmp(E1, "�o��") == 0 || strcmp(E1, "OV-C") == 0)
	{
		textcolor(WHITE);
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
	if (strcmp(E1, "��") == 0)
	{
		textcolor(LIGHTGRAY);
	}

	printf("%s\n", E1);

	textcolor(WHITE);


	printf("|  �̗́F");


	//textbackground(LIGHTGRAY);
	if (strcmp(E1, "��") == 0|| strcmp(E1, "�o��") == 0|| strcmp(E1, "OV-C") == 0)
	{
		textcolor(WHITE);
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
	if (strcmp(E1, "��") == 0)
	{
		textcolor(LIGHTGRAY);
	}

	for (int i = 1; i <= icon; i++)			//hp�̍ő�A�C�R���\����10�ɌŒ�
	{
		printf("��");
		count += 1;
	}
	textbackground(BLACK);
	textcolor(WHITE);
	for (int i = 1; i <= 18 - count; i++)			//�����\������̋�
	{
		printf("�@");
	}




	printf("|�@�@�@�@�@�@�h��́F%.0f\n", D1 * 1000);	//�󔒂̏I���



											//��2�Q
	printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@|\n");
	printf("�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P\n");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��l�ڕ\��

	count = 0;	//�̗̓A�C�R���v���ϐ��̏�����


	if (H2 < 0)
	{
		H2 = 0;		//�̗͂��}�C�i�X�̒l�ɂȂ�Ȃ��悤�ɂ���B
	}

	printf("�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q\n");	//��l�ڏo�͊J�n
	printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@| �̗́F%.0f\n", H2);
	printf("|�@�@�@");

	printf("%s", character[select2 - '1'].name);		//���O�̕\��

	for (int i = 0; i < 38 - strlen(character[select2 - '1'].name); i++)
	{
		printf(" ");			//���O����̋�
	}

	printf("|�@�@�@�@�@�@���́F%d\n", M2);	//�󔒂̏I���	
	printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@| �����F");

	if (strcmp(E2, "��") == 0 || strcmp(E2, "�o��") == 0 || strcmp(E2, "OV-C") == 0)
	{
		textcolor(WHITE);
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
	if (strcmp(E2, "��") == 0)
	{
		textcolor(LIGHTGRAY);
	}


	printf("%s\n", E2);

	textcolor(WHITE);


	printf("|  �̗́F");	//�̗͕\���J�n

	//textbackground(LIGHTGRAY);
	if (strcmp(E2, "��") == 0||strcmp(E2,"�o��")==0||strcmp(E2,"OV-C")==0)
	{
		textcolor(WHITE);
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
	if (strcmp(E2, "��") == 0)
	{
		textcolor(LIGHTGRAY);
	}

	for (int i = 1; i <= icon2; i++)			//hp�̃A�C�R���ő�\����10�ɌŒ�
	{
		printf("��");
		count += 1;
	}
	textbackground(BLACK);
	textcolor(WHITE);
	for (int i = 1; i <= 18 - count; i++)			//�����\������̋�
	{
		printf("�@");
	}


	printf("|�@�@�@�@�@�@�h��́F%.0f\n", D2 * 1000);//�󔒂̏I���
	printf("|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@|\n");
	printf("�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P\n");		//��l�ڏo�͏I��



	return 0;
}