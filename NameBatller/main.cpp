
//	HAL�����@AT11E-341�@13�ԁ@����q�l
//	�b�o��o�ۑ�
//
//	�l�[���o�g���[�@

//////�S�̗̂���
//�@�v���g�^�C�v�錾�E�O���[�o���ϐ��錾�I����Amain���̍ŏ��Ŋe�t�@�C����ǂݍ��ށB
//�Amain���̒�����title�֐����Ăяo���^�C�g����\���B�^�C�g���\����Ȃ�炩�̓��͂�main���֖߂�B
//�Bmain�����̖������[�v�̒��Ƀ��j���[�\��������A��������e���[�h�ւƈڍs�B
//�Ccreate�֐��ŃL�����N�^�[���l�ȏ�ݒ肵�Abattle�֐��Ő퓬���J�n�B
//�Dbattle�֐��ŃL������I�����A�퓬�p�̉��̕ϐ��ɑ���B
//�E���[�v�������J�n���Abattle_disp�֐��Ő퓬��ʂ�W�J�Aanime�֐��Ŋ當���\���AB1,B2�֐��Ő퓬���̃L�����̍s�������݂ɉ��Z�B
//�Fbattle�֐����łǂ��炩�̃L�����̗̑͂��O�ɂȂ�΁Amain���֖߂�B


////�L�����N�^�[�̃p�����[�^�̐ݒ���@
//�@���͂������O�̂��ׂĂ̕����R�[�h�����v���A����̕��ς��o���B
//�A��ڂ̕����R�[�h�ɕ��ϒl�𑫂����l��̗͂Ƃ���B
//�B�l�ڂ̕����R�[�h�ɕ��ϒl�𑫂����l���U���ɐݒ肷��B
//�C���ϒl��2�{�ɂ����l��h��͂ɂ���B
//�D�S�X�e�[�^�X�����v���A����̏\���ȉ��̒l���X�s�[�h�Ƃ���B(�����ق�����s�����B)
//�E�S�����R�[�h�̍��v�l�̈ꌅ�ڂ��o���A��������ɑ��������߂�B
//�F�̗́E�U���E�h��̂����ł������X�e�[�^�X�Ƒ����ɂ���āA���̃L�����N�^�[�̃X�L����ݒ�B
//�G�̗͂����̂܂ܔ��f����Ɛ퓬�������ɏI��邽�߁A�퓬���Ԓ����̂��߂ɍŌ�ɑ̗͂̒l��4.3�{����B
//�Hexistance�ϐ��ɂP�����A���̔ԍ��̃L�����N�^�[�����݂��邱�Ƃ������B(�ݒ肳��Ă��Ȃ��ꍇ��0�ɂȂ��Ă���B)


//�L�����N�^�[�̑���
//���͕��A���ɋ���
//���͐��A���ɋ���
//���͉��A���ɋ���
//���͉��A���A���ɋ����B
//�ł͌��ɋ����B
//���͈łɋ����B
//���͑����I�ȗL���s���͑��݂��Ȃ��B

//�퓬���̃X�L���������ɂ̂ݔ������鑮��
//��c���ׂĂ̑����ɑ΂��Ď��g�̍U�����㉻�����B(�З͌���)
//�o���c���ׂĂ̑����ɑ΂��Ď��g�̍U�����㏸����B�E���^�[��������
//OV-C�c���^�[�������łł����������ŘA���U�����ł���(�ő�܉�)�E���^�[��������

//�X�L���ɂ���
//�L�����N�^�[�̗̑͂�50���ȉ��ɂȂ�ƁA�퓬���Ɉ�x�����X�L���𔭓��B
//���ꂼ��X�e�[�^�X��g�ݍ��킹���v�Z�ɂ��_���[�W�t�^��̗͂̉񕜁A�X�e�[�^�X�̕ϓ��⑮���̕ω��Ȃǂ�����B








#define _CRT_SECURE_NO_WARNINGS

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



status character[4] =	//�e�����o�[�����l
{
	"�@",		//name
	0,		//hp
	0,		//mp
	0,		//def
	0,		//speed
	"�@",		//element
	"�@",			//�X�L����
	0		//existance(���݂��邩�ǂ����@�P�F���݁@0�F���݂��Ȃ�)
};


//BGM�A�h���X�i�[�ϐ�
int mmf;	//menu music file
int bmf1;		//battle music file
int bmf2;		//bsttle music file2



/////�֐��v���g�^�C�v�錾

void title();	//�^�C�g��
void check();	//�L�����N�^�[�\��
int create(int notsaved);	//�L�����N�^�[�쐬
void battle();	//�퓬�V�X�e��
int save(int notsaved);	//�L�����N�^�[�f�[�^�̃Z�[�u
void read();			//�L�����N�^�[�f�[�^�̃��[�h(����)
int datadelete(int notsaved);	//�S�f�[�^�̍폜
int gameend(int notsaved);

//�퓬��ʂ̊當��

int main()
{

	//BGM�y�ȃt�@�C���W�J

	mmf = opensound("���j���[��.mp3");
	if (mmf == 0)
	{
		printf("�t�@�C���̓W�J���ł��܂���B\n�v���O�������I�����܂��B\n�G���[�F���j���[��");
		getch();
		exit(ABEND);
	}

	bmf1 = opensound("�퓬�ȂP.mp3");
	if (bmf1 == 0)
	{
		printf("�t�@�C���̓W�J���ł��܂���\n�v���O�������I�����܂��B\n�G���[�F�퓬��1");
		getch();
		exit(ABEND);
	}

	bmf2 = opensound("�퓬�ȂQ.mp3");
	if (bmf2 == 0)
	{
		printf("�t�@�C���̓W�J���ł��܂���\n�v���O�������I�����܂��B\n�G���[:�퓬��2");
		getch();
		exit(ABEND);
	}

	setvolume(mmf, 20);
	setvolume(bmf1, 10);
	setvolume(bmf2, 10);

	char windowtitle[15];
	strcpy(windowtitle, "�l�[���o�g���[");
	setcaption(windowtitle);

	textcolor(WHITE);
	setcursortype(NOCURSOR);



	read();	//�Ō�ɃZ�[�u�����f�[�^��ǂݍ���


	title();	//�^�C�g�����o��
	system("cls");	//��ʂ��N���A




					//////////////////////////////////////////////////////////////////////////////////��������Q�[�����n�܂�



	int notsaved = 0;

	for (;;)		//�Q�[���S�̖̂������[�v���J�n�B
	{
		srand(timeGetTime());	//���j���[�̘g�̐F�𗐐��Ō��߂�

		system("cls");

		int select;

		if (notsaved == 0)	//�ʏ�̃��j���[�\��
		{
			int color = rand() % 10;
			gotoxy(7, 7);
			switch (color)
			{
			case 0:textcolor(WHITE); break;	//�����̈ꌅ��0�Ȃ甒
			case 1:case 2:textcolor(LIGHTRED); break;//�����̈ꌅ��1�܂���2�Ȃ��
			case 3:case 4:textcolor(LIGHTBLUE); break;//�����̈ꌅ��3�܂���4�Ȃ��
			case 5:case 6:textcolor(LIGHTGREEN); break;//�����̈ꌅ��5�܂���6�Ȃ��
			case 7:case 8:textcolor(YELLOW); break;//�����̈ꌅ��7�܂���8�Ȃ物
			case 9:textcolor(LIGHTMAGENTA); break;//�����̈ꌅ��9�Ȃ率
			}
			printf("��������������������������������������������������������"); gotoxy(7, 8); textcolor(WHITE);
			printf("���@ �@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@�@�@�@�@��"); gotoxy(7, 9);
			printf("�� �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@�@�@�@��"); gotoxy(7, 10);
			printf("��"); textcolor(WHITE); printf("�@�@1:�L�����N�^�[�̊m�F�@�@�@�@ �@ �@�@�@�@�@�@�@�@"); textcolor(WHITE); printf("��"); gotoxy(7, 11);
			printf("���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@�@ �@�@�@�@�@�@�@��"); gotoxy(7, 12);
			printf("��"); textcolor(WHITE); printf("�@�@2:�L�����N�^�[�����@�@ �@�@�@�@�@ �@�@�@�@�@�@"); textcolor(WHITE); printf("��"); gotoxy(7, 13);
			printf("���@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@ �@�@�@�@�@��"); gotoxy(7, 14);
			printf("��"); textcolor(WHITE); printf("�@�@3:�퓬�J�n�@�@�@�@�@ �@�@�@�@�@�@�@�@ �@�@�@�@�@"); textcolor(WHITE); printf("��"); gotoxy(7, 15);
			printf("���@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@�@�@�@ �@�@�@�@��"); gotoxy(7, 16);
			printf("��"); textcolor(WHITE); printf("�@�@4:�Z�[�u�@           �@�@�@�@�@�@�@�@�@�@ �@�@�@"); textcolor(WHITE); printf("��"); gotoxy(7, 17);
			printf("���@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@��"); gotoxy(7, 18);
			printf("��"); textcolor(WHITE); printf("�@�@5:�I���@�@�@�@ �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@"); textcolor(WHITE); printf("��"); gotoxy(7, 19);
			printf("���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@ �@��"); gotoxy(7, 20);
			printf("��"); textcolor(WHITE); printf(" �@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@9:�f�[�^���폜����"); textcolor(WHITE); printf("��"); gotoxy(7, 21); textcolor(BLUE);
			color = rand() % 10;
			switch (color)
			{
			case 0:textcolor(WHITE); break;	//�����̈ꌅ��0�Ȃ甒
			case 1:case 2:textcolor(LIGHTRED); break;//�����̈ꌅ��1�܂���2�Ȃ��
			case 3:case 4:textcolor(LIGHTBLUE); break;//�����̈ꌅ��3�܂���4�Ȃ��
			case 5:case 6:textcolor(LIGHTGREEN); break;//�����̈ꌅ��5�܂���6�Ȃ��
			case 7:case 8:textcolor(YELLOW); break;//�����̈ꌅ��7�܂���8�Ȃ物
			case 9:textcolor(LIGHTMAGENTA); break;//�����̈ꌅ��9�Ȃ率
			}
			printf("��������������������������������������������������������"); textcolor(WHITE);

			gotoxy(8, 25);
			printf("�ԍ���I��ł��������B\n");
		}

		else if (notsaved == 1)	//�Z�[�u�����{�x���\������
		{
			gotoxy(7, 7);
			int color = rand() % 10;
			gotoxy(7, 7);
			switch (color)
			{
			case 0:textcolor(WHITE); break;	//�����̈ꌅ��0�Ȃ甒
			case 1:case 2:textcolor(LIGHTRED); break;//�����̈ꌅ��1�܂���2�Ȃ��
			case 3:case 4:textcolor(LIGHTBLUE); break;//�����̈ꌅ��3�܂���4�Ȃ��
			case 5:case 6:textcolor(LIGHTGREEN); break;//�����̈ꌅ��5�܂���6�Ȃ��
			case 7:case 8:textcolor(YELLOW); break;//�����̈ꌅ��7�܂���8�Ȃ物
			case 9:textcolor(LIGHTMAGENTA); break;//�����̈ꌅ��9�Ȃ率
			}
			printf("��������������������������������������������������������"); gotoxy(7, 8); textcolor(WHITE);
			printf("���@ �@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@�@�@�@�@��"); gotoxy(7, 9);
			printf("�� �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@�@�@�@��"); gotoxy(7, 10);
			printf("��"); textcolor(WHITE); printf("�@�@1:�L�����N�^�[�̊m�F�@�@�@�@ �@ �@�@�@�@�@�@�@�@"); textcolor(WHITE); printf("��"); gotoxy(7, 11);
			printf("���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@�@ �@�@�@�@�@�@�@��"); gotoxy(7, 12);
			printf("��"); textcolor(WHITE); printf("�@�@2:�L�����N�^�[�����@�@ �@�@�@�@�@ �@�@�@�@�@�@"); textcolor(WHITE); printf("��"); gotoxy(7, 13);
			printf("���@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@ �@�@�@�@�@��"); gotoxy(7, 14);
			printf("��"); textcolor(WHITE); printf("�@�@3:�퓬�J�n�@�@�@�@�@ �@�@�@�@�@�@�@�@ �@�@�@�@�@"); textcolor(WHITE); printf("��"); gotoxy(7, 15);
			printf("���@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@�@�@�@ �@�@�@�@��"); gotoxy(7, 16);
			printf("��"); textcolor(WHITE); printf("�@�@4:�Z�[�u");; textcolor(LIGHTRED); printf("(�Z�[�u����Ă��܂���)                  "); textcolor(WHITE);		//�Z�[�u����Ă��Ȃ��ꍇ�A�x���Ƃ��Đԕ����ŕ\������B
			printf("��"); gotoxy(7, 17);
			printf("���@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@��"); gotoxy(7, 18);
			printf("��"); textcolor(WHITE); printf("�@�@5:�I���@�@�@�@ �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@"); textcolor(WHITE); printf("��"); gotoxy(7, 19);
			printf("���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@�@�@ �@��"); gotoxy(7, 20);
			printf("��"); textcolor(WHITE); printf(" �@�@�@�@�@�@�@�@�@�@�@ �@�@�@�@�@9:�f�[�^���폜����"); textcolor(WHITE); printf("��"); gotoxy(7, 21); textcolor(BLUE);

			color = rand() % 10;
			switch (color)
			{
			case 0:textcolor(WHITE); break;	//�����̈ꌅ��0�Ȃ甒
			case 1:case 2:textcolor(LIGHTRED); break;//�����̈ꌅ��1�܂���2�Ȃ��
			case 3:case 4:textcolor(LIGHTBLUE); break;//�����̈ꌅ��3�܂���4�Ȃ��
			case 5:case 6:textcolor(LIGHTGREEN); break;//�����̈ꌅ��5�܂���6�Ȃ��
			case 7:case 8:textcolor(YELLOW); break;//�����̈ꌅ��7�܂���8�Ȃ物
			case 9:textcolor(LIGHTMAGENTA); break;//�����̈ꌅ��9�Ȃ率
			}
			printf("��������������������������������������������������������"); textcolor(WHITE);

			gotoxy(8, 25);
			printf("�ԍ���I��ł��������B\n");
		}

		select = getch();	//���[�h�̑I��


		if (select == '1')
		{
			check();	//�L�����N�^�[�ڍ׏��m�F
		}

		if (select == '2')
		{
			notsaved = create(notsaved);	//�L�����N�^�[�ݒ�@(�N�����ݒ肳���΃Z�[�u�𑣂����j���[�ɂȂ�)
		}

		if (select == '3')
		{
			battle();		//�퓬�J�n�@�i�֐����Ő퓬�Ɋւ��鏈���ւƔh���j
		}

		if (select == '4')
		{
			notsaved = save(notsaved);	//�f�[�^�Z�[�u�@�i�Z�[�u���s�����ƂŖ����{�x���̂Ȃ��ʏ탁�j���[�ɂȂ�j
		}

		if (select == '5')
		{
			gameend(notsaved);		//�v���O�����̏I���@�i�Z�[�u�����{�ł���΁A�I���m�F���Ɍx����\������B�j
		}

		if (select == '9')
		{
			notsaved = datadelete(notsaved);	//�S�f�[�^�̍폜�@�i�폜�����ꍇ�A�Z�[�u�����{�x���̂Ȃ��ʏ탁�j���[�ɂȂ�j
		}


	}



}
