
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

void read()		//�t�@�C���ɕۑ�����Ă���f�[�^��ǂ݂��ށB
{
	FILE *fp;
	fp = fopen("�f�[�^�t�@�C��.csv", "rb");	//�t�@�C���W�J

	if (fp == NULL)
	{
		printf("�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B\n�v���O�������I�����܂��B");
		getch();
		exit(ABEND);
	}

	for (int i = 0; i < 4; i++)	//4��ǂݍ���
	{
		if (fread(&character[i], sizeof(character[i]), 1, fp) <= 0)	//�v���C���[�̃f�[�^��ǂݍ���
		{
			break;
		}

	}

	fclose(fp);	//�t�@�C�������

	return;
}