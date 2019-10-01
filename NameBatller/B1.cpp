
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
void animeA1H(char E1[5]);	//��l�ڍU���q�b�g��
void animeA1A(char E1[5]);	//��l�ڍU�����s��	


int B1(int *M1, int *M2, int select1, int select2, float *H1, float *H2, float *D1, float *D2, char *E1, char *E2, int *sa1, int *counter1, int dmg, int *regene)	//��l�ڂ̃^�[��
{

	srand(timeGetTime());

	int random = rand() % 10;	//�������ꂽ�����̈ꌅ�ڂ��i�[

	if (strcmp(E1, "��") == 0)	//���������̏ꍇ
	{
		if (*sa1 == 0 || *sa1 == 2)	//�ʏ�U��
		{
			if (strcmp(E2, "��") == 0 || strcmp(E2, "��") == 0)	//����̑��������������͗��̏ꍇ
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
					animeA1H(E1);	//�U���A�j��
					printf("\n�������L�����I");
					getch();
					*H2 -= (*M1*(1 - *D2))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
					animeA1H(E1);	//�U���A�j��
					printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
					animeA1A(E1);//����A�j��
					printf("\n%s�͍U����������I", character[select2 - '1'].name);
					//����񐔂�����Z
				}


			}
			else	//����̑���������ȊO�̏ꍇ
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
					animeA1H(E1);	//�U���A�j��
					*H2 -= (*M1*(1 - *D2));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
					animeA1H(E1);	//�U���A�j��
					printf("\n��S�̈ꌂ�I�I");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
					animeA1A(E1);	//����A�j��
					printf("\n%s�͍U����������I", character[select2 - '1'].name);
				}
			}
		}
		else if (*sa1 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			getch(); battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
			animeA1H(E1);	//�U���A�j��

			if (strcmp(character[select1 - '1'].skill, "��e�͂Ȃ��̑唚��") == 0)
			{
				textcolor(LIGHTRED);
				printf("\n\n<< ��e�͂Ȃ��̑唚�� >>");
				textcolor(WHITE);
				*H1 *= 0.1;
				*H2 -= (*M1*(1 - *D2)) * 3.3;
				getch();
				printf("\n�����̉e���Ŏ������_���[�W���󂯂��B");
			}
			if (strcmp(character[select1 - '1'].skill, "�A�g�~�b�N�C���p�N�g") == 0)
			{
				textcolor(LIGHTRED);
				printf("\n\n<< �A�g�~�b�N�C���p�N�g >>");
				textcolor(WHITE);
				*H2 -= (*M1*(1 - *D2))*1.4;
				*D2 /= 2;
				getch();
				printf("\n����̖h��͂����������I");
			}
			if (strcmp(character[select1 - '1'].skill, "���e�I���C�g") == 0)
			{
				textcolor(LIGHTRED);
				printf("\n\n<< ���e�I���C�g >>");
				textcolor(WHITE);
				*H2 -= (*M1*(1 - *D2)) * 2;
				getch();
				printf("\n��_���[�W�I");

			}

			*sa1 = 2;	//SkillActivated���Q�ɂ���B(�X�L�������ς�)

		}

	}

	if (strcmp(E1, "��") == 0)	//���������̏ꍇ
	{
		if (*counter1 == 0)	//�J�E���^�[�ҋ@�����Ă��Ȃ����
		{
			if (*sa1 == 0 || *sa1 == 2)//�ʏ�U��
			{
				if (strcmp(E2, "��") == 0 || strcmp(E2, "��") == 0)	//����̑��������������͗��̏ꍇ
				{

					if (random >= 2 && random <= 7)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
						animeA1H(E1);	//�U���A�j��
						printf("\n�������L�����I");
						getch();
						*H2 -= (*M1*(1 - *D2))*1.25;
					}
					else if (random >= 8)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
						animeA1H(E1);//�U���A�j��
						printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
						getch();
						*H2 -= (*M1*(1 - *D2)) * 1.3;

					}
					else
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
						animeA1A(E1);	//����A�j��
						printf("\n%s�͍U����������I", character[select2 - '1'].name);
					}

				}
				else
				{

					if (random >= 2 && random <= 7)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
						animeA1H(E1);	//�U���A�j��
						*H2 -= (*M1*(1 - *D2));
					}
					else if (random >= 8)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
						animeA1H(E1);	//�U���A�j��
						printf("\n��S�̈ꌂ�I�I");
						getch();
						*H2 -= (*M1*(1 - *D2)) * 1.2;
					}
					else
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
						animeA1A(E1);	//����A�j��
						printf("\n%s�͍U����������I", character[select2 - '1'].name);
					}
				}
			}
			else if (*sa1 == 1)	//�X�L������
			{
				printf("\n�X�L�������I�I");
				getch();

				if (strcmp(character[select1 - '1'].skill, "�I�[�V�����Y�A�M�g") == 0)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
					animeA1H(E1);
					textcolor(LIGHTCYAN);
					printf("\n\n<< �I�[�V�����Y�A�M�g >>");
					textcolor(WHITE);
					*H2 -= (*M1*(1 - *D2))*1.5;
					*M2 *= 0.7;
					getch();
					printf("\n����̍U���͂����������I");
				}
				if (strcmp(character[select1 - '1'].skill, "�C�n�I�P�A�m�X") == 0)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
					animeA1H(E1);
					textcolor(LIGHTCYAN);
					printf("\n\n<< �C�n�I�P�A�m�X >>");
					textcolor(WHITE);
					*H2 -= *M1*1.5;
					getch();
					printf("\n����̖h��𖳎���������Ȉꌂ�I�I");
				}
				if (strcmp(character[select1 - '1'].skill, "���Ԑ���") == 0)
				{
					textcolor(LIGHTCYAN);
					printf("\n\n<< ���Ԑ��� >>");
					textcolor(WHITE);
					*counter1 = 1;
					getch();
					printf("\n%s�͏W���͂����߂�c", character[select1 - '1'].name);

				}
				*sa1 = 2;
			}
		}
		else if (*counter1 == 1)
		{
			//�������Ȃ�
		}
		else if (*counter1 == 2)
		{
			if (dmg != 0)	//�J�E���^�[�̐���
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1H(E1);
				printf("\n�J�E���^�[�����I�I");
				*H2 -= (dmg*(1 - *D2)) * 3.8;
				getch();
				*counter1 = 0;
			}
			else
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeWait();
				printf("\n�J�E���^�[���s�c");
				getch();
				*counter1 = 0;
			}
		}


	}


	if (strcmp(E1, "��") == 0)	//�������������̏ꍇ
	{

		if (*sa1 == 0 || *sa1 == 2)//�ʏ�U��
		{
			if (strcmp(E2, "��") == 0 || strcmp(E2, "��") == 0)	//����̑��������������͐_��r�̏ꍇ
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
					animeA1H(E1);
					printf("\n�������L�����I");
					getch();
					*H2 -= (*M1*(1 - *D2))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
					animeA1H(E1);
					printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬���
					animeA1A(E1);
					printf("\n%s�͍U����������I", character[select2 - '1'].name);
				}

			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					*H2 -= (*M1*(1 - *D2));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					printf("\n��S�̈ꌂ�I�I");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1A(E1);
					printf("\n%s�͍U����������I", character[select2 - '1'].name);
				}
			}
		}
		else if (*sa1 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			getch();

			if (strcmp(character[select1 - '1'].skill, "���C�W���O�X�g�[��") == 0)
			{
				textcolor(LIGHTGREEN);
				printf("\n\n<< ���C�W���O�X�g�[�� >>");
				textcolor(WHITE);
				*M1 *= 1.5;
				*D1 *= 1.5;
				*H2 -= (*M1*(1 - *D2))*0.8;
				getch();
				printf("\n�U���Ɩh�䂪�㏸�����I�I");
			}
			if (strcmp(character[select1 - '1'].skill, "�����{��") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
				animeA1H(E1);
				textcolor(LIGHTGREEN);
				printf("\n\n<< �����{�� >>");
				textcolor(WHITE);
				for (int i = 0; i < 4; i++)
				{
					int enemy = *H2;
					srand(timeGetTime());
					random = rand() % 10;
					if (random >= 3 && random <= 7)
					{
						*H2 -= (*M1*(1 - *D2))*0.6;
						enemy -= *H2;
						printf("\n%d�̃_���[�W�I", abs(enemy));
					}
					else if (random >= 8)
					{
						printf("\n��S�̈ꌂ�I�I");
						*H2 -= (*M1*(1 - *D2)) * 0.7;
						enemy -= *H2;
						printf("\n%d�̃_���[�W�I", abs(enemy));
					}
					else
					{

						printf("\n%s�͍U����������I", character[select2 - '1'].name);
					}
					getch();
				}
				printf("\n4��U���I�I");
			}
			if (strcmp(character[select1 - '1'].skill, "�T�C�N�����G�b�W") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
				animeA1H(E1);
				textcolor(LIGHTGREEN);
				printf("\n\n<< �T�C�N�����G�b�W >>");
				textcolor(WHITE);
				*H2 -= ((character[select1 - '1'].speed * 3) + (*M1*1.1))*(1 - *D2);
				getch();
				printf("\n�ڂɂ��~�܂�ʎa���I�I");

			}
			*sa1 = 2;
		}

	}

	if (strcmp(E1, "��") == 0)	//�������̏ꍇ
	{

		if (*sa1 == 0 || *sa1 == 2)	//�ʏ�U��
		{
			if (strcmp(E2, "��") == 0 || strcmp(E2, "��") == 0 || strcmp(E2, "��") == 0)	//����̑��������A���A���̂����ꂩ�ł���ꍇ
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					printf("\n�������L�����I");
					getch();
					*H2 -= (*M1*(1 - *D2))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1A(E1);
					printf("\n%s�͍U����������I", character[select2 - '1'].name);
				}


			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					*H2 -= (*M1*(1 - *D2));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					printf("\n��S�̈ꌂ�I�I");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1A(E1);
					printf("\n%s�͍U����������I", character[select2 - '1'].name);
				}
			}
		}
		else if (*sa1 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			getch();
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
			animeA1H(E1);

			if (strcmp(character[select1 - '1'].skill, "���C�g�j���O�X���b�V��") == 0)
			{
				textcolor(YELLOW);
				printf("\n\n<< ���C�g�j���O�X���b�V�� >>");
				textcolor(WHITE);
				*H2 -= (*M1*(1 - *D2 / 2))*2.2;
				getch();
				printf("\n��_���[�W�I�I");
			}
			if (strcmp(character[select1 - '1'].skill, "�A�[�N�u���X�g") == 0)
			{
				textcolor(YELLOW);
				printf("\n\n<< �A�[�N�u���X�g >>");
				textcolor(WHITE);
				int arc = *H1;
				*H1 /= 2;
				arc -= *H1;
				*H2 -= arc * 3;
				getch();
				printf("\n�̂Đg�̈ꌂ�I");
			}
			if (strcmp(character[select1 - '1'].skill, "�}�}���K��") == 0)
			{
				textcolor(YELLOW);
				printf("\n\n<< �}�}���K�� >>");
				textcolor(WHITE);
				int mm = *M1 + *D1;
				*H2 -= (mm*(1 - *D2))*2.2;
				getch();
				printf("\n��_���[�W�I");

			}

			*sa1 = 2;	//SkillActivated���Q�ɂ���B(�X�L�������ς�)

		}


	}

	if (strcmp(E1, "��") == 0)	//���g���ő����̏ꍇ
	{
		if (*sa1 == 0 || *sa1 == 2)//�ʏ�U��
		{
			if (strcmp(E2, "��") == 0)	//���肪�������̏ꍇ
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					printf("\n�������L�����I");
					getch();
					*H2 -= (*M1*(1 - *D2))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1A(E1);
					printf("\n%s�͍U����������I", character[select2 - '1'].name);
				}

			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					*H2 -= (*M1*(1 - *D2));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					printf("\n��S�̈ꌂ�I�I");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1A(E1);
					printf("\n%s�͍U����������I", character[select2 - '1'].name);
				}
			}
		}
		else if (*sa1 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			getch();

			if (strcmp(character[select1 - '1'].skill, "���̖���") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
				animeA1H(E1);
				textcolor(LIGHTMAGENTA);
				printf("\n\n<< ���̖��� >>");
				textcolor(WHITE);
				int yoi = *M1;
				*M1 *= 0.5;	//�U���͂𔼌�����
				yoi -= *M1;	//�U���͂̌������l�����ϐ��ɑ��
				yoi += *D1;
				*D1 *= 0.5;	//�h��͂𔼌�����
				yoi -= *D1;	//�h��͂̌������l�����ϐ��ɑ��

				*H2 -= (yoi*2.5) * (1 - *D2);
				*H1 += yoi * 1.5;
				getch();
				printf("\n�U���͂Ɩh��͂�㏞�ɁA���͂Ȉꌂ�I�I\n�̗͂��񕜂����I");
			}
			if (strcmp(character[select1 - '1'].skill, "�u���b�f�B�M�A") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
				animeA1H(E1);
				textcolor(LIGHTMAGENTA);
				printf("\n\n<< �u���b�f�B�M�A >>");
				textcolor(WHITE);

				int blood = *H1;	//�ϐ��Ɍ��݂̎����̗̑͂��i�[
				*H1 /= 2;		//�̗͂�����		
				blood /= 2;	//�i�[�����l�𔼌�(�̗͂Ɠ�����������)	

				*M1 += blood * 2;	//�������̗͂�2�{�̒l�U���ɉ��Z
				*D1 += (blood * 2) / 1000;	//�������̗͂�2�{�̒l�h��ɉ��Z
				getch();
				printf("\n�̗͂������������A\n�U���Ɩh�䂪�啝�ɏ㏸�����I�I");
			}
			if (strcmp(character[select1 - '1'].skill, "�u���b�N�A�|�J���v�X") == 0)
			{
				textcolor(LIGHTMAGENTA);
				printf("\n\n<< �u���b�N�A�|�J���v�X >>");
				textcolor(WHITE);
				*M1 += *D2;
				*D2 = 0;
				getch();
				printf("\n����̖h��͂�D�����I�I\n����͖h��͂�0�ɂȂ����I�I");

			}
			*sa1 = 2;
		}
	}

	if (strcmp(E1, "��") == 0)	//������������
	{
		if (*sa1 == 0 || *sa1 == 2)//�ʏ�U��
		{
			if (strcmp(E2, "��") == 0)	//���肪�ő���
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					printf("\n�������L�����I");
					getch();
					*H2 -= (*M1*(1 - *D2))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					printf("\n�������L�����Q�Q�Q\n�@�@�Q�Q��S�̈ꌂ�I�I");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1A(E1);
					printf("\n%s�͍U����������I", character[select2 - '1'].name);
				}

			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					*H2 -= (*M1*(1 - *D2));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1H(E1);
					printf("\n��S�̈ꌂ�I�I");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//�퓬���
					animeA1A(E1);
					printf("\n%s�͍U����������I", character[select2 - '1'].name);
				}
			}
		}
		else if (*sa1 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			getch();

			if (strcmp(character[select1 - '1'].skill, "�����̖���") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
				animeA1H(E1);
				textcolor(YELLOW);
				printf("\n\n<< �����̖��� >>");
				textcolor(WHITE);
				int ake = *M1;
				*M1 *= 0.5;//�U���͂𔼌�����
				ake -= *M1;//�U���͂̌������l�����ϐ��ɑ��
				ake += *D1;
				*D1 *= 0.5;//�h��͂𔼌�����
				ake -= *D1;//�h��͂̌������l�����ϐ��ɑ��

				*H2 -= (ake*2.5) * (1 - *D2);
				*H1 += ake;
				getch();
				printf("\n�U���͂Ɩh��͂�㏞�ɁA���͂Ȉꌂ�I�I\n�̗͂��񕜂����I");
			}
			if (strcmp(character[select1 - '1'].skill, "�V���C�j���O�X�s�A") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
				animeA1H(E1);
				textcolor(YELLOW);
				printf("\n\n<< �V���C�j���O�X�s�A >>");
				textcolor(WHITE);
				*H2 -= *M1*1.5;
				getch();
				printf("\n����̖h��𖳎���������Ȉꌂ�I�I");
			}
			if (strcmp(character[select1 - '1'].skill, "�����̌�") == 0)
			{
				textcolor(YELLOW);
				printf("\n\n<< �����̌� >>");
				textcolor(WHITE);
				*regene = 1;
				*D1 *= 1.5;
				getch();
				printf("\n�����񕜕t�^�I\n�h��͂��㏸�����I");


			}
			*sa1 = 2;
		}

	}

	if (strcmp(E1, "��") == 0)	//���g�̑������������̏ꍇ
	{
		if (*sa1 == 0 || *sa1 == 2)//�ʏ�U��
		{
			if (random >= 2 && random <= 7)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1H(E1);
				*H2 -= (*M1*(1 - *D2));
			}
			else if (random >= 8)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1H(E1);
				printf("\n��S�̈ꌂ�I�I");
				getch();
				*H2 -= (*M1*(1 - *D2)) * 1.2;
			}
			else
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1A(E1);
				printf("\n%s�͍U����������I", character[select2 - '1'].name);
			}
		}
		else if (*sa1 == 1)	//�X�L������
		{
			printf("\n�X�L�������I�I");
			if (strcmp(character[select1 - '1'].skill, "�o��") == 0)
			{
				textcolor(LIGHTGRAY);
				printf("\n<< �o�� >>");
				textcolor(WHITE);

				strcpy(E1, "�o��");
				getch();
				*H1 *= 1.28;
				*regene = 1;
				printf("\n�������ω������I�I\n�����񕜌��ʕt�^�I\n�U�����͂���Ȃ��Ȃ����B");
				return 0;
			}
			if (strcmp(character[select1 - '1'].skill, "�I�[�o�[�N���b�N") == 0)
			{
				textcolor(LIGHTGRAY);
				printf("\n<< �I�[�o�[�N���b�N >>");
				textcolor(WHITE);

				strcpy(E1, "OV-C");
				printf("\n�������ω������B");
				printf("\n�U���񐔂����������I");
				*regene = 1;
				printf("\n�����񕜌��ʕt�^�I");
				return 0;
			}
			if (strcmp(character[select1 - '1'].skill, "�G�������g�u���C�N") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//�퓬�p���
				animeA1H(E1);
				textcolor(LIGHTGRAY);
				printf("\n<< �G�������g�u���C�N >>");
				textcolor(WHITE);
				strcpy(E2, "��");
				*H2 -= (*M1*(1 - *D2))*1.3;
				printf("\n����̑�����j�󂵂��I\n����͎�̉������I");
				printf("\n����̓_���[�W���󂯂��B");
			}
			*sa1 = 2;
		}
	}
	if (strcmp(E1, "�o��") == 0)
	{
		if (random >= 1 && random <= 6)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA1H(E1);
			*H2 -= (*M1*(1 - *D2))*1.4;
		}
		else if (random >= 7)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA1H(E1);
			printf("\n��S�̈ꌂ�I�I");
			getch();
			*H2 -= (*M1*(1 - *D2)) * 1.7;
		}
	}
	if (strcmp(E1, "��") == 0)
	{
		if (random >= 3 && random <= 7)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA1H(E1);
			*H2 -= (*M1*(1 - *D2))*0.9;
		}
		else if (random >= 8)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA1H(E1);
			printf("\n��S�̈ꌂ�I�I");
			getch();
			*H2 -= (*M1*(1 - *D2));
		}
		else
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA1A(E1);
			printf("\n%s�͍U����������I", character[select2 - '1'].name);
		}
	}
	if (strcmp(E1, "OV-C") == 0)
	{
		srand(timeGetTime());
		int ov = rand() % 10;	//�������������_���l�̈ꌅ�ڂ����߂�
		ov /= 2;	//�����_���l�̈ꌅ�ڂ�2�Ŋ���A�ō���4�̒l�ɕω�������B
		ov += 1;	//�Œ�ł��P�̒l�ɂ��邽�߂ɂP��ǉ�����B(�Œ�F1�@�ō��F5)

		for (int i = 0; i < ov; i++)
		{

			srand(timeGetTime());	//�����_���l���V�[�h�ɂ���
			random = rand() % 10;	//�����_���l�̈ꌅ�ڂ�������B

			if (random >= 2 && random <= 7)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1H(E1);
				printf("\n\n�N���b�N%d�I", i + 1);
				int enemy = *H2;
				*H2 -= (*M1*(1 - *D2))*0.7;
				enemy -= *H2;
				printf("\n%d�̃_���[�W�I", enemy);
			}
			else if (random >= 8)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1H(E1);
				printf("\n\n�N���b�N%d�I", i + 1);
				int enemy = *H2;
				printf("\n��S�̈ꌂ�I�I");
				*H2 -= (*M1*(1 - *D2)) * 0.8;
				enemy -= *H2;
				printf("\n%d�̃_���[�W�I", enemy);
			}
			else
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1A(E1);
				printf("\n\n�N���b�N%d�I", i + 1);
				printf("\n%s�͍U����������I", character[select2 - '1'].name);
			}

			getch();
		}

		printf("\n%d��U���I�I", ov);
		getch();
	}

	if (*regene == 1)
	{
		*H1 *= 1.38;
		printf("\n�񕜌��ʔ���");
	}

	return *M1, select1, select2, *H2, *D2;
}