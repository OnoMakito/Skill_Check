
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

extern int mmf;
extern int bmf1;
extern int bmf2;

int battle_disp(float H1, float H2, int M1, int M2, float D1, float D2, char E1[6], char E2[6], int select1, int select2);		//�퓬�p���
int B1(int *M1, int *M2, int select1, int select2, float *H1, float *H2, float *D1, float *D2, char *E1, char *E2, int *sa1, int *counter1, int dmg, int *regene);	//��l�ڂ̃^�[��
int B2(int *M2, int *M1, int select2, int select1, float *H1, float *H2, float *D1, float *D2, char *E1, char *E2, int *sa2, int *counter2, int dmg, int *regene);	//��l�ڂ̃^�[��
void animeWait();	//�ҋ@���

void battle()	//�퓬�J�n
{


	//�퓬���s���邩�ǂ������m�F
	if (character[0].existance + character[1].existance + character[2].existance + character[3].existance < 2)	//�S�L�����N�^�[����existance�����Z�B2�ȏ�łȂ���΃��j���[(main)�֖߂�B
	{
		printf("\n�I�ׂ�L�����N�^�[�����Ȃ��ł��I\n�L�����N�^�[���l�ȏ�ݒ肵�܂��傤�B");
		getch();
		return;
	}

	int counter1 = 0;	//��l�ڂ̃X�L���A���Ԑ����̃J�E���^�[����(2:�J�E���^�[����,1:�J�E���^�[�҂�,0:�ʏ�s��)
	int counter2 = 0;	//��l�ڂ̃X�L���A���Ԑ����̃J�E���^�[����(2:�J�E���^�[����,1:�J�E���^�[�҂�,0:�ʏ�s��)
	int dmg = 0;	//�_���[�W�v���ϐ�
	int countdmg1 = 0;	//��l�ڂ̃J�E���^�[�p�_���[�W�ϐ�
	int countdmg2 = 0;	//��l�ڂ̃J�E���^�[�p�_���[�W�ϐ�
	int regene1 = 0;	//���^�[��������(1:�� 0:�������Ȃ�)
	int regene2 = 0;	//���^�[��������(1�F�񕜁@0�F�������Ȃ�)
	int sa1 = 0;	//��l�ڂ̃X�L���������(2:�����ς݁E1:���������B���E0:������)		���FSkill Activated1
	int sa2 = 0;	//��l�ڂ̃X�L���������(2:�����ς݁E1:���������B���E0:������)		���FSkill Activated2

	int select1;
	int select2;

	system("cls");
	printf("\n�P:%s\n\n�Q:%s\n\n�R:%s\n\n�S:%s\n", character[0].name, character[1].name, character[2].name, character[3].name);	//�L�����N�^�[���\��
	printf("\n��l�ڂ̃L�����N�^�[��I��ł��������B(0�ŃL�����Z��)\n");		//��l�ڂ̃L�����N�^�[���w��
	select1 = getch();


	for (select1; select1 != '0' && character[select1 - '1'].existance == 0 || select1 == 13;)	//�I�΂ꂽ�ԍ��ɃL�����N�^�[�����Ȃ��ꍇ�ƁA�G���^�[�L�[�����͂��ꂽ�ꍇ�̍ē��͗v���B-1�̔ԍ������L�����N�^�[�͂��Ȃ�����0����͂��ꂽ�ꍇ�͖�������
	{
		system("cls");
		printf("\n�P:%s\n\n�Q:%s\n\n�R:%s\n\n�S:%s\n", character[0].name, character[1].name, character[2].name, character[3].name);	//�L�����N�^�[���̕\��
		printf("\n���̔ԍ��̃L�����N�^�[�͑��݂��܂���B\n������x�I��ł��������B(0�ŃL�����Z��)");
		select1 = getch();
	}


	if (select1 == '0')	//�O����͂��ꂽ�ꍇ�A���j���[(main)�֖߂�
	{
		return;
	}

	printf("\n%s", character[select1 - '1'].name);

	char N1[21];
	strcpy(N1, character[select1 - '1'].name);	//��l�ڂ̖��O����
	float H1 = character[select1 - '1'].hp;	//��l�ڂ̃v���C���[�̗̑́@
	int M1 = character[select1 - '1'].mp;	//��l�ڂ̃v���C���[�̍U����
	float D1 = character[select1 - '1'].def;	//��l�ڂ̃v���C���[�̖h���(1000�Ŋ���A����̍U����h��͂̊��������y������)
	D1 /= 1000;
	int speed1 = character[select1 - '1'].speed;	//��l�ڂ̑��x�v�Z

	char E1[6];
	strcpy(E1, character[select1 - '1'].element);	//��l�ڂ̃v���C���[�̑���

	char skill1[35];
	strcpy(skill1, character[select1 - '1'].skill);	//��l�ڂ̃v���C���[�̃X�L����





	printf("\n\n��l�ڂ̃L�����N�^�[��I��ł��������B\n");		//��l�ڂ̃L�����N�^�[���w��

	select2 = getch();


	for (select2; select2 != '0' && (select2 == select1 || character[select2 - '1'].existance == 0) || select2 == 13;)	//��l�ڂ̔ԍ���I�񂾍ۂɈ�l�ڂƔ���Ă���ꍇ�ƃG���^�[�L�[�������ꂽ�ꍇ�A�ē��͗v��
	{
		system("cls");
		printf("\n�P:%s\n\n�Q:%s\n\n�R:%s\n\n�S:%s\n", character[0].name, character[1].name, character[2].name, character[3].name);	//�e�L�����N�^�[�\��
		if (select2 == select1)	//��l�ڂ���l�ڂƃL�������
		{
			printf("\n��l�ڂƓ����L�����N�^�[�͑I�ׂ܂���B");
		}
		if (select2 != '0' && character[select2 - '1'].existance == 0)	//�I�΂ꂽ�ԍ��ɃL���������Ȃ��ꍇ�̍ē��͏����B�@-1�̔ԍ��ɃL�����͂��Ȃ����߁A0�������ꂽ�ꍇ�͖�������B
		{
			printf("\n���̃L�����N�^�[�͑��݂��܂���B");
		}
		printf("\n������x���͂��Ă��������B(0�ŃL�����Z��)");
		select2 = getch();
	}

	if (select2 == '0')	//0����͂��ꂽ�ꍇ�Ƀ��j���[�֖߂�
	{
		return;
	}

	printf("\n%s", character[select2 - '1'].name);	//��l�ڂ̃L�����N�^�[����\��

	char N2[21];
	strcpy(N2, character[select2 - '1'].name);
	float H2 = character[select2 - '1'].hp;	//��l�ڂ̗̑�
	int M2 = character[select2 - '1'].mp;	//��l�ڂ̍U����
	float D2 = character[select2 - '1'].def;	//��l�ڂ̖h���(5000�Ŋ���A�h��͂̊�����������̍U�����y������B)
	D2 /= 1000;
	int speed2 = character[select2 - '1'].speed;	//��l�ڂ̑��x

	char E2[6];
	strcpy(E2, character[select2 - '1'].element);	//��l�ڂ̑���

	char skill2[35];
	strcpy(skill2, character[select2 - '1'].skill);		//��l�ڂ̃X�L����


	stopsound(mmf);

	textcolor(LIGHTRED);
	gotoxy(5, 20);
	printf("�퓬���J�n���܂��B");
	gotoxy(6, 21);
	printf("Please AnyKey");
	textcolor(WHITE);
	getch();

	if (speed1 < speed2)	//��l�ڂ���ɍs������
	{
		srand(timeGetTime());
		int music = rand() % 10;	//���y�Đ�(�Ȃ͂Q�p�^�[��)
		if (music >= 5)
		{
			playsound(bmf1, 1);
		}
		else
		{
			playsound(bmf2, 1);
		}

		system("cls");//��ʃ��Z�b�g
		battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//�퓬���
		printf("\n%s�̐搧�U���I�I", N2);
		getch();



		for (; H1 > 0 && H2 > 0;)	//�ǂ��炩�̃v���C���[�̗̑͂�0�ɂȂ�܂Ń��[�v
		{
			if (H1 > 0 && H2 > 0)	//�^�[�����Ƃɐ퓬�̌p�����m�F����B
			{
				if (H2 <= character[select2 - '1'].hp / 2 && sa2 == 0)	//�̗͂������ȉ��ɂȂ�ƁA��x�����X�L���𔭓�����
				{
					sa2 = 1;
				}


				battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//�퓬���
				animeWait();	//�ҋ@�A�j��
				printf("\n%s�̍U���I\n", N2);
				getch();
				dmg = H1;
				B2(&M2, &M1, select2, select1, &H1, &H2, &D1, &D2, &E1[0], &E2[0], &sa2, &counter2, countdmg2, &regene2);	//��l�ڂ̃^�[��
				dmg -= H1;	//���̃^�[���ŗ^�����_���[�W
				if (counter1 == 1)	//���肪�J�E���^�[�҂��̏ꍇ
				{
					countdmg1 = dmg;
					counter1 = 2;	//���肪�J�E���^�[�����Ɉڂ�B
				}
				printf("\n���v%d�̃_���[�W�I", dmg);
				getch();
			}


			if (H1 > 0 && H2 > 0)	//�^�[�����Ƃɐ퓬�̌p�����m�F����B
			{

				if (H1 <= character[select1 - '1'].hp / 2 && sa1 == 0)	//�̗͂������ȉ��ɂȂ�ƁA��x�����X�L���𔭓�����B
				{
					sa1 = 1;
				}

				battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//�퓬���
				animeWait();	//�ҋ@�A�j��
				printf("\n%s�̍U���I", N1);
				getch();
				dmg = H2;
				B1(&M1, &M2, select1, select2, &H1, &H2, &D1, &D2, &E1[0], &E2[0], &sa1, &counter1, countdmg1, &regene1);	//��l�ڂ̃^�[��
				dmg -= H2;	//���̃^�[���ŗ^�����_���[�W
				if (counter2 == 1)	//���肪�J�E���^�[�҂��̏ꍇ
				{
					countdmg2 = dmg;
					counter2 = 2;	//���肪�J�E���^�[�����Ɉڂ�B
				}
				printf("\n���v%d�̃_���[�W�I", dmg);
				getch();
			}

		}

		if (H1 <= 0)
		{
			battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//�퓬���
			printf("\n%s�̏����I�I", N2);	//�����Җ��\��
			getch();
			if (music >= 5)	//���y��~
			{
				stopsound(bmf1);
			}
			else
			{
				stopsound(bmf2);
			}


			playsound(mmf, 1);	//���j���[�ȍĐ�
			return;	//���j���[�ɖ߂�
		}
		if (H2 <= 0)
		{
			battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//�퓬���
			printf("\n%s�̏����I�I", N1);	//�����Җ��\��
			getch();

			if (music >= 5)	//���y��~
			{
				stopsound(bmf1);
			}
			else
			{
				stopsound(bmf2);
			}

			playsound(mmf, 1);	//���j���[�ȍĐ�
			return;	//���j���[�ɖ߂�
		}


	}
	else	//��l�ڂ���ɍs������
	{
		srand(timeGetTime());
		int music = rand() % 10;	//���y�Đ�(�Ȃ͂Q�p�^�[��)
		if (music >= 5)
		{
			playsound(bmf1, 1);
		}
		else
		{
			playsound(bmf2, 1);
		}



		battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);
		printf("\n%s�̐搧�U���I�I", N1);

		for (; H1 > 0 && H2 > 0;)	//�ǂ��炩�̗̑͂�0�ɂȂ�܂Ń��[�v
		{

			if (H1 > 0 && H2 > 0)	//�^�[�����Ƃɐ퓬�̌p�����m�F����B
			{
				if (H1 <= character[select1 - '1'].hp / 2 && sa1 == 0)	//�̗͂������ȉ��ɂȂ�ƁA��x�����X�L���𔭓�����B
				{
					sa1 = 1;
				}

				battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//�퓬���
				animeWait();	//�ҋ@�A�j��
				printf("\n%s�̍U���I", N1);
				getch();
				dmg = H2;
				B1(&M1, &M2, select1, select2, &H1, &H2, &D1, &D2, &E1[0], &E2[0], &sa1, &counter1, countdmg1, &regene1);	//��l�ڂ̃^�[��
				dmg -= H2;	//���̃^�[���ŗ^�����_���[�W
				if (counter2 == 1)	//���肪�J�E���^�[�҂��̏ꍇ
				{
					countdmg2 = dmg;
					counter2 = 2;	//���肪�J�E���^�[�����ɂ���B
				}
				printf("\n���v%d�̃_���[�W�I", dmg);
				getch();
			}

			if (H1 > 0 && H2 > 0)//�^�[�����Ƃɐ퓬�̌p�����m�F����B
			{
				if (H2 <= character[select2 - '1'].hp / 2 && sa2 == 0)	//�̗͂������ȉ��ɂȂ�ƁA��x�����X�L���𔭓�����
				{
					sa2 = 1;
				}

				battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//�퓬���
				animeWait();	//�ҋ@�A�j��
				printf("\n%s�̍U���I\n", N2);
				getch();
				dmg = H1;
				B2(&M2, &M1, select2, select1, &H1, &H2, &D1, &D2, &E1[0], &E2[0], &sa2, &counter2, countdmg2, &regene2);	//�퓬��ʕ\��
				dmg -= H1;	//���̃^�[���ŗ^�����_���[�W
				if (counter1 == 1)	//���肪�J�E���^�[�҂��̏ꍇ
				{
					countdmg1 = dmg;
					counter1 = 2;	//���肪�J�E���^�[�����Ɉڂ�B
				}
				printf("\n���v%d�̃_���[�W�I", dmg);
				getch();
			}


		}

		if (H1 <= 0)
		{
			battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//�퓬���
			printf("\n%s�̏����I�I", N2);	//�����Җ��\��
			getch();

			if (music >= 5)	//���y��~
			{
				stopsound(bmf1);
			}
			else
			{
				stopsound(bmf2);
			}
			playsound(mmf, 1);	//���j���[�ȍĐ�
			return;	//���j���[��
		}
		if (H2 <= 0)
		{
			battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//�퓬���
			printf("\n%s�̏����I�I", N1);	//�����Җ��\��
			getch();

			if (music >= 5)	//���y��~
			{
				stopsound(bmf1);
			}
			else
			{
				stopsound(bmf2);
			}

			playsound(mmf, 1);	//���j���[�ȍĐ�
			return;	//���j���[��
		}

	}



}