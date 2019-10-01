
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


int battle_disp(float H1, float H2, int M1, int M2, float D1, float D2, char E1[6], char E2[6], int select1, int select2);		//�퓬�p���

void animeWait();	//�ҋ@���
void animeA2H(char E2[5]);	//��l�ڍU���q�b�g��
void animeA2A(char E2[5]);	//��l�ڍU�����s��

int B2(int *M2, int *M1, int select2, int select1, float *H1, float*H2, float *D1, float *D2, char *E1, char *E2, int *sa2, int *counter2, int dmg, int *regene)	//��l�ڂ̃^�[��
{

	srand(timeGetTime());




	int random = rand() % 10;

	if (strcmp(E2, "��") == 0)
	{
		if (*sa2 == 0 || *sa2 == 2)	//�ʏ�U��
		{
			if (strcmp(E1, "��") == 0 || strcmp(E1, "��") == 0)
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n�������L�����I");
					getch();
					*H1 -= (*M2*(1 - *D1))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
					getch();
					*H1 -= (*M2*(1 - *D1)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2A(E2);
					printf("\n%s�͍U����������I", character[select1 - '1'].name);
				}


			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					*H1 -= (*M2*(1 - *D1));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n��S�̈ꌂ�I�I");
					getch();
					*H1 -= (*M2*(1 - *D1)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2A(E2);
					printf("\n%s�͍U����������I", character[select1 - '1'].name);
				}
			}
		}
		else if (*sa2 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			getch();

			if (strcmp(character[select2 - '1'].skill, "��e�͂Ȃ��̑唚��") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(LIGHTRED);
				printf("\n\n<< ��e�͂Ȃ��̑唚�� >>");
				textcolor(WHITE);
				*H2 *= 0.1;
				*H1 -= (*M2*(1 - *D1)) * 3.3;
				getch();
				printf("\n�����̉e���Ŏ������_���[�W���󂯂��B");
			}
			if (strcmp(character[select2 - '1'].skill, "�A�g�~�b�N�C���p�N�g") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(LIGHTRED);
				printf("\n\n<< �A�g�~�b�N�C���p�N�g >>");
				textcolor(WHITE);
				*H1 -= (*M2*(1 - *D2))*1.4;
				*D1 /= 2;
				getch();
				printf("\n����̖h��͂����������I");
			}
			if (strcmp(character[select2 - '1'].skill, "���e�I���C�g") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(LIGHTRED);
				printf("\n\n<< ���e�I���C�g >>");
				textcolor(WHITE);
				*H1 -= (*M2*(1 - *D1)) * 2;
				getch();
				printf("\n��_���[�W�I");

			}

			*sa2 = 2;	//SkillActivated���Q�ɂ���B(�X�L�������ς�)

		}

	}

	if (strcmp(E2, "��") == 0)
	{
		if (*counter2 == 0)
		{
			if (*sa2 == 0 || *sa2 == 2)//�ʏ�U��
			{
				if (strcmp(E1, "��") == 0 || strcmp(E1, "��") == 0)
				{

					if (random >= 2 && random <= 7)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
						animeA2H(E2);
						printf("\n�������L�����I");
						getch();
						*H1 -= (*M2*(1 - *D1))*1.25;
					}
					else if (random >= 8)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
						animeA2H(E2);
						printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
						getch();
						*H1 -= (*M2*(1 - *D1)) * 1.3;

					}
					else
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
						animeA2A(E2);
						printf("\n%s�͍U����������I", character[select1 - '1'].name);
					}

				}
				else
				{

					if (random >= 2 && random <= 7)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
						animeA2H(E2);
						*H1 -= (*M2*(1 - *D1));
					}
					else if (random >= 8)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
						animeA2H(E2);
						printf("\n��S�̈ꌂ�I�I");
						getch();
						*H1 -= (*M2*(1 - *D1)) * 1.2;
					}
					else
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
						animeA2A(E2);
						printf("\n%s�͍U����������I", character[select1 - '1'].name);
					}
				}
			}
			else if (*sa2 == 1)	//�X�L������
			{
				printf("\n�X�L�������I�I");
				getch();

				if (strcmp(character[select2 - '1'].skill, "�I�[�V�����Y�A�M�g") == 0)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					textcolor(LIGHTCYAN);
					printf("\n\n<< �I�[�V�����Y�A�M�g >>");
					textcolor(WHITE);
					*H1 -= (*M2*(1 - *D1))*1.5;
					*M1 *= 0.7;
					getch();
					printf("\n����̍U���͂����������I");
				}
				if (strcmp(character[select2 - '1'].skill, "�C�n�I�P�A�m�X") == 0)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					textcolor(LIGHTCYAN);
					printf("\n\n<< �C�n�I�P�A�m�X >>");
					textcolor(WHITE);
					*H1 -= *M2*1.5;
					getch();
					printf("\n����̖h��𖳎���������Ȉꌂ�I�I");
				}
				if (strcmp(character[select2 - '1'].skill, "���Ԑ���") == 0)
				{
					textcolor(LIGHTCYAN);
					printf("\n\n<< ���Ԑ��� >>");
					textcolor(WHITE);
					*counter2 = 1;
					getch();
					printf("\n%s�͏W���͂����߂�c", character[select2 - '1'].name);

				}
				*sa2 = 2;
			}
		}
		else if (*counter2 == 1)
		{
			//�������Ȃ�
		}
		else if (*counter2 == 2)
		{
			if (dmg != 0)	//�J�E���^�[�̐���
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				printf("\n�J�E���^�[�����I�I");
				*H1 -= (dmg*(1 - *D1)) * 3.8;
				getch();
				*counter2 = 0;
			}
			else			//�J�E���^�[�̎��s
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeWait();
				printf("\n�J�E���^�[���s�c");
				getch();
				*counter2 = 0;
			}

		}


	}

	if (strcmp(E2, "��") == 0)
	{

		if (*sa2 == 0 || *sa2 == 2)//�ʏ�U��
		{
			if (strcmp(E1, "��") == 0 || strcmp(E1, "��") == 0)
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n�������L�����I");
					getch();
					*H1 -= (*M2*(1 - *D1))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
					getch();
					*H1 -= (*M2*(1 - *D1)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2A(E2);
					printf("\n%s�͍U����������I", character[select1 - '1'].name);

				}

			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					*H1 -= (*M2*(1 - *D1));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n��S�̈ꌂ�I�I");
					getch();
					*H1 -= (*M2*(1 - *D1)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2A(E2);
					printf("\n%s�͍U����������I", character[select1 - '1'].name);

				}
			}
		}
		else if (*sa2 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			getch();

			if (strcmp(character[select2 - '1'].skill, "���C�W���O�X�g�[��") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(LIGHTGREEN);
				printf("\n\n<< ���C�W���O�X�g�[�� >>");
				textcolor(WHITE);
				*M2 *= 1.5;
				*D2 *= 1.5;
				*H1 -= (*M1*(1 - *D1))*0.8;
				getch();
				printf("\n�U���Ɩh�䂪�㏸�����I�I");
			}
			if (strcmp(character[select2 - '1'].skill, "�����{��") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(LIGHTGREEN);
				printf("\n\n<< �����{�� >>");
				textcolor(WHITE);
				for (int i = 0; i < 4; i++)
				{
					int enemy = *H1;
					srand(timeGetTime());
					random = rand() % 10;
					if (random >= 3 && random <= 7)
					{
						*H1 -= (*M2*(1 - *D1))*0.6;
						enemy -= *H1;
						printf("\n%d�̃_���[�W�I", abs(enemy));
					}
					else if (random >= 8)
					{
						printf("\n��S�̈ꌂ�I�I");
						getch();
						*H1 -= (*M2*(1 - *D1)) * 0.7;
						enemy -= *H1;
						printf("\n%d�̃_���[�W�I", abs(enemy));
					}
					else
					{

						printf("\n%s�͍U����������I", character[select1 - '1'].name);

					}
				}
				getch();
				printf("\n4��U���I�I");
			}
			if (strcmp(character[select2 - '1'].skill, "�T�C�N�����G�b�W") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(LIGHTGREEN);
				printf("\n\n<< �T�C�N�����G�b�W >>");
				textcolor(WHITE);
				*H1 -= ((character[select2 - '1'].speed * 3) + (*M2*1.1))*(1 - *D1);
				getch();
				printf("\n�ڂɂ��~�܂�ʎa���I�I");

			}
			*sa2 = 2;
		}

	}

	if (strcmp(E2, "��") == 0)
	{

		if (*sa2 == 0 || *sa2 == 2)	//�ʏ�U��
		{
			if (strcmp(E1, "��") == 0 || strcmp(E1, "��") == 0 || strcmp(E1, "��") == 0)
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n�������L�����I");
					getch();
					*H1 -= (*M2*(1 - *D1))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
					getch();
					*H1 -= (*M2*(1 - *D1)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2A(E2);
					printf("\n%s�͍U����������I", character[select1 - '1'].name);

				}


			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					*H1 -= (*M2*(1 - *D1));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n��S�̈ꌂ�I�I");
					getch();
					*H1 -= (*M2*(1 - *D1)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2A(E2);
					printf("\n%s�͍U����������I", character[select1 - '1'].name);

				}
			}
		}
		else if (*sa2 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			getch();

			if (strcmp(character[select2 - '1'].skill, "���C�g�j���O�X���b�V��") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(YELLOW);
				printf("\n\n<< ���C�g�j���O�X���b�V�� >>");
				textcolor(WHITE);
				*H1 -= (*M2*(1 - *D1 / 2))*2.2;
				getch();
				printf("\n��_���[�W�I�I");
			}
			if (strcmp(character[select2 - '1'].skill, "�A�[�N�u���X�g") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(YELLOW);
				printf("\n\n<< �A�[�N�u���X�g >>");
				textcolor(WHITE);
				int arc = *H2;
				*H2 /= 2;
				arc -= *H2;
				*H1 -= arc * 3;
				getch();
				printf("\n�̂Đg�̈ꌂ�I");
			}
			if (strcmp(character[select2 - '1'].skill, "�}�}���K��") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(YELLOW);
				printf("\n\n<< �}�}���K�� >>");
				textcolor(WHITE);
				int mm = *M2 + *D2;
				*H1 -= (mm*(1 - *D1))*2.2;
				getch();
				printf("\n��_���[�W�I");

			}

			*sa2 = 2;	//SkillActivated���Q�ɂ���B(�X�L�������ς�)

		}


	}

	if (strcmp(E2, "��") == 0)
	{
		if (*sa2 == 0 || *sa2 == 2)//�ʏ�U��
		{
			if (strcmp(E1, "��") == 0)
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n�������L�����I");
					getch();
					*H1 -= (*M2*(1 - *D1))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
					getch();
					*H1 -= (*M2*(1 - *D1)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2A(E2);
					printf("\n%s�͍U����������I", character[select1 - '1'].name);

				}

			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					*H1 -= (*M2*(1 - *D1));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n��S�̈ꌂ�I�I");
					getch();
					*H1 -= (*M2*(1 - *D1)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2A(E2);
					printf("\n%s�͍U����������I", character[select1 - '1'].name);

				}
			}
		}
		else if (*sa2 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			getch();

			if (strcmp(character[select2 - '1'].skill, "���̖���") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(LIGHTMAGENTA);
				printf("\n\n<< ���̖��� >>");
				textcolor(WHITE);
				int yoi = *M2;
				*M2 *= 0.5;//�U���͂𔼌�����
				yoi -= *M2;//�U���͂̌������l�����ϐ��ɑ��
				yoi += *D2;
				*D2 *= 0.5;//�h��͂𔼌�����
				yoi -= *D2;//�h��͂̌������l�����ϐ��ɑ��

				*H1 -= (yoi*2.5) * (1 - *D1);
				*H2 += yoi * 1.5;
				getch();
				printf("\n�U���͂Ɩh��͂�㏞�ɁA���͂Ȉꌂ�I�I\n�̗͂��񕜂����I");
			}
			if (strcmp(character[select2 - '1'].skill, "�u���b�f�B�M�A") == 0)
			{
				textcolor(LIGHTMAGENTA);
				printf("\n\n<< �u���b�f�B�M�A >>");
				textcolor(WHITE);

				int blood = *H2;	//�ϐ��Ɍ��݂̎����̗̑͂��i�[
				*H2 /= 2;			//�̗͂�����
				blood /= 2;		//�i�[�����l������(�̗͂Ɠ�����������)

				*M2 += blood * 2;	//�������̗͂�2�{�̒l�A�U���ɉ��Z
				*D2 += (blood * 2) / 1000;	//�������̗͂�2�{�̒l�A�h��͂ɉ��Z
				getch();
				printf("\n�̗͂������������A\n�U���Ɩh�䂪�啝�ɏ㏸�����I�I");
			}
			if (strcmp(character[select2 - '1'].skill, "�u���b�N�A�|�J���v�X") == 0)
			{
				textcolor(LIGHTMAGENTA);
				printf("\n\n<< �u���b�N�A�|�J���v�X >>");
				textcolor(WHITE);
				*M2 += *D1;
				*D1 = 0;
				getch();
				printf("\n����̖h��͂�D�����I�I\n����͖h��͂�0�ɂȂ����I�I");

			}
			*sa2 = 2;
		}
	}

	if (strcmp(E2, "��") == 0)
	{
		if (*sa2 == 0 || *sa2 == 2)//�ʏ�U��
		{
			if (strcmp(E1, "��") == 0)
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n�������L�����I");
					getch();
					*H1 -= (*M2*(1 - *D1))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
					getch();
					*H1 -= (*M2*(1 - *D1)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2A(E2);
					printf("\n%s�͍U����������I", character[select1 - '1'].name);

				}

			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					*H1 -= (*M2*(1 - *D1));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2H(E2);
					printf("\n��S�̈ꌂ�I�I");
					getch();
					*H1 -= (*M2*(1 - *D1)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
					animeA2A(E2);
					printf("\n%s�͍U����������I", character[select1 - '1'].name);

				}
			}
		}
		else if (*sa2 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			getch();

			if (strcmp(character[select2 - '1'].skill, "�����̖���") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(YELLOW);
				printf("\n\n<< �����̖��� >>");
				textcolor(WHITE);
				int ake = *M2;
				*M2 *= 0.5;//�U���͂𔼌�����
				ake -= *M2;//�U���͂̌������l�����ϐ��ɑ��
				ake += *D2;
				*D2 *= 0.5;//�h��͂𔼌�����
				ake -= *D2;//�h��͂̌������l�����ϐ��ɑ��

				*H1 -= (ake*2.5) * (1 - *D1);
				*H2 += ake * 1.5;
				getch();
				printf("\n�U���͂Ɩh��͂�㏞�ɁA���͂Ȉꌂ�I�I\n�̗͂��񕜂����I");
			}
			if (strcmp(character[select2 - '1'].skill, "�V���C�j���O�X�s�A") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(YELLOW);
				printf("\n\n<< �V���C�j���O�X�s�A >>");
				textcolor(WHITE);
				*H1 -= *M2*1.5;
				getch();
				printf("\n����̖h��𖳎���������Ȉꌂ�I�I");
			}
			if (strcmp(character[select2 - '1'].skill, "�����̌�") == 0)
			{
				textcolor(YELLOW);
				printf("\n\n<< �����̌� >>");
				textcolor(WHITE);
				*regene = 1;
				*D2 *= 1.5;
				getch();
				printf("\n�����񕜕t�^�I\n�h��͂��㏸�����I");


			}
			*sa2 = 2;
		}

	}

	if (strcmp(E2, "��") == 0)
	{
		if (*sa2 == 0 || *sa2 == 2)//�ʏ�U��
		{
			if (random >= 2 && random <= 7)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				*H1 -= (*M2*(1 - *D1));
			}
			else if (random >= 8)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				printf("\n��S�̈ꌂ�I�I");
				getch();
				*H1 -= (*M2*(1 - *D1)) * 1.2;
			}
			else
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2A(E2);
				printf("\n%s�͍U����������I", character[select1 - '1'].name);

			}
		}
		else if (*sa2 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			if (strcmp(character[select2 - '1'].skill, "�o��") == 0)
			{
				textcolor(LIGHTGRAY);
				printf("\n<< �o�� >>");
				textcolor(WHITE);

				strcpy(E2, "�o��");
				getch();
				*H2 *= 1.28;
				*regene = 1;
				printf("\n�������ω������I�I\n�����񕜌��ʕt�^�I\n�U�����͂���Ȃ��Ȃ����B");
				return 0;

			}
			if (strcmp(character[select2 - '1'].skill, "�I�[�o�[�N���b�N") == 0)
			{
				textcolor(LIGHTGRAY);
				printf("\n<< �I�[�o�[�N���b�N >>");
				textcolor(WHITE);

				strcpy(E2, "OV-C");
				printf("\n�������ω������B");
				printf("\n�U���񐔂����������I");
				*regene = 1;
				printf("\n�����񕜌��ʕt�^�I");
				return 0;
			}
			if (strcmp(character[select2 - '1'].skill, "�G�������g�u���C�N") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				textcolor(LIGHTGRAY);
				printf("\n<< �G�������g�u���C�N >>");
				textcolor(WHITE);

				strcpy(E1, "��");
				*H1 -= (*M2*(1 - *D1))*1.3;
				printf("\n����̑�����j�󂵂��I\n����͎�̉������I");
				printf("\n����̓_���[�W���󂯂��B");
			}
			*sa2 = 2;
		}
	}

	if (strcmp(E2, "�o��") == 0)
	{

		if (random >= 1 && random <= 7)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA2H(E2);
			*H1 -= (*M2*(1 - *D1))*1.4;
		}
		else if (random >= 8)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA2H(E2);
			printf("\n��S�̈ꌂ�I�I");
			getch();
			*H1 -= (*M2*(1 - *D1)) * 1.7;
		}
	}

	if (strcmp(E2, "��") == 0)
	{
		if (random >= 3 && random <= 7)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA2H(E2);
			*H1 -= (*M2*(1 - *D1))*0.9;
		}
		else if (random >= 8)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA2H(E2);
			printf("\n��S�̈ꌂ�I�I");
			getch();
			*H1 -= (*M2*(1 - *D1));
		}
		else
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA2A(E2);
			printf("\n%s�͍U����������I", character[select1 - '1'].name);

		}
	}

	if (strcmp(E2, "OV-C") == 0)
	{
		srand(timeGetTime());
		int ov = rand() % 10;	//�������������_���l�̈ꌅ�ڂ����߂�
		ov /= 2;	//�����_���l�̈ꌅ�ڂ�2�Ŋ���A�ō���4�̒l�ɕω�������B
		ov += 1;	//�Œ�ł��P�̒l�ɂ��邽�߂ɂP��ǉ�����B(�Œ�F1�@�ō��F5)

		for (int i = 0; i < ov; i++)
		{

			srand(timeGetTime());
			random = rand() % 10;	//�����_���l�̈ꌅ�ڂ�������B

			if (random >= 2 && random <= 7)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				printf("\n\n�N���b�N%d�I", i + 1);
				int enemy = *H1;
				*H1 -= (*M2*(1 - *D1))*0.7;
				enemy -= *H1;
				printf("\n%d�̃_���[�W�I", enemy);
			}
			else if (random >= 8)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2H(E2);
				printf("\n\n�N���b�N%d�I", i + 1);
				int enemy = *H1;
				printf("\n��S�̈ꌂ�I�I");
				*H1 -= (*M2*(1 - *D1)) * 0.8;
				enemy -= *H1;
				printf("\n%d�̃_���[�W�I", enemy);
			}
			else
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA2A(E2);
				printf("\n\n�N���b�N%d�I", i + 1);
				printf("\n%s�͍U����������I", character[select1 - '1'].name);

			}

			getch();
		}

		printf("\n%d��U���I�I", ov);
		getch();
	}


	if (*regene == 1)
	{
		*H2 *= 1.38;
		printf("\n�񕜌��ʔ���");
	}

	return *M2, select2, select1, *H1, *D1, *E1, *E2;
}