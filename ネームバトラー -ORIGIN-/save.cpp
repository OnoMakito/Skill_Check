
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


int save(int notsaved)		//���݂̏󋵂��Z�[�u
{
	FILE *fp;

	fp = fopen("�f�[�^�t�@�C��.csv", "wb");	//�t�@�C���W�J

	if (fp == NULL)
	{
		printf("�Z�[�u�Ɏ��s���܂����B\n�v���O�������I�����܂��B");
		getch();
		exit(ABEND);
	}

	fwrite(character, sizeof(character[0]), 4, fp);		//�f�[�^��������

	fclose(fp);	//�t�@�C�������

	printf("�Z�[�u���������܂����B");

	getch();

	notsaved = 0;

	return notsaved;
}