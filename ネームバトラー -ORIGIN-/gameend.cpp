
#define CONIOEX
#include "conioex.h"

#define NEND 0		//exit�֐��F����I��
#define  ABEND 1	//exit�֐��F�ُ�I��

extern int mmf;
extern int bmf1;
extern int bmf2;

int gameend(int notsaved)	//�v���O�����̏I��
{
	int select;

	for (;;)	//
	{
		system("cls");

		if (notsaved == 1)	//�Z�[�u�����{�̏ꍇ�x�������o��
		{
			gotoxy(20, 14);
			textcolor(LIGHTRED);	//�Ԏ��ŋ���
			printf("���ӁF�f�[�^���ۑ�����Ă��܂���I");
			textcolor(WHITE);
		}

		gotoxy(25, 15);
		printf("�Q�[�����I�����܂����H");	//�I���m�F
		gotoxy(29, 17);
		printf("Yes: 1   No:0\n");

		select = getch();

		if (select == '1')
		{
			closesound(mmf);	//�I�����ɉ��y�t�@�C�������
			closesound(bmf1);
			closesound(bmf2);
			exit(NEND);
		}
		else if (select == '0')	//0����͂����ꍇ���j���[�֖߂�
		{
			return notsaved;
		}
	}
}