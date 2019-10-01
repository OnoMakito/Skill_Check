#include "Judgement.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "collision.h"
#include "number.h"
#include "score.h"
#include "EnemyBullet.h"
#include "Item.h"
#include "sound.h"

	//static void HitCheck_Bullet_Enemy(void);	
	static int score = 0;
	static int Draw_for_Score = 0;

	static int Player_Hit=120;


	void Judge_Init()
	{
		Player_Hit = 120;	//�v���C���[�̖��G�o�ߎ��Ԃ�������(�ŏ����疳�G�ɂ͂Ȃ�Ȃ��B) 
		score = 0;
		Draw_for_Score = 0;
	}

void UpdateJudge()
 {
	Player_Hit++;

	for (int i = 0; i < BULLTE_MAX; i++)	//�e�۔z�񑍓�����
	{
		for (int j = 0; j < ENEMY_MAX; j++)	//�G�z�񑍓�����(�e�ƓG�̔���E�v���C���[�ƓG�̔���)
		{
			if (Bullet_Exist(i) && Flier1_Exist(j))	//�G�ƒe�ۂ��݂��ɑ��݂��邩�B
			{
				if (Circle_Collision(Bullet_GetCollision(i), Flier1_GetCollision(j)))
				{
					score += Flier1_DMG(j);	//���C�t���ɂ���̂�����
					Bullet_Destroy(i);	//�����ŏ������ǂ����Œe�ɊђʂȂǂ̓������������邱�Ƃ��ł���B

					//�����ŃX�R�A���Z�Ȃǂ��s����B
				}

			}

			if (Bullet_Exist(i) && Flier2_Exist(j))
			{
				if (Circle_Collision(Bullet_GetCollision(i), Flier2_GetCollision(j)))
				{
					Flier2_Destroy(j);	//���C�t���ɂ���̂�����
					Bullet_Destroy(i);	//�����ŏ������ǂ����Œe�ɊђʂȂǂ̓������������邱�Ƃ��ł���B


					score += 15;
					//�����ŃX�R�A���Z�Ȃǂ��s����B
				}
			}

			if (Bullet_Exist(i) && Dragon_Exist(j))
			{
				if (Circle_Collision(Bullet_GetCollision(i), Dragon_GetCollision(j)))
				{
					score+=Dragon_DMG(j);
					Bullet_Destroy(i);
				}
			}



			if (Player_Exist() && Flier1_Exist(j)&&Player_Hit>PLAYER_INVISIBLE)	//�v���C���[���G�ɂԂ������Ƃ��A��莞�Ԗ��G��^����ƂƂ��Ƀ_���[�W��^����B
			{
				if (Circle_Collision(Player_GetCollision(), Flier1_GetCollision(j)))
				{
					Player_DMG(20);
					Player_Hit = 0;
				}
			}
			if (Player_Exist() && Flier2_Exist(j) && Player_Hit > PLAYER_INVISIBLE)
			{
				if (Circle_Collision(Player_GetCollision(), Flier2_GetCollision(j)))
				{
					Player_DMG(25);
					Player_Hit = 0;
				}
			}

			if (Player_Exist() && Dragon_Bullet_Exist(j) && Player_Hit > PLAYER_INVISIBLE)
			{
				if (Circle_Collision(Player_GetCollision(), Dragon_Bullet_GetCollision(j)))
				{
					Player_DMG(20);
					Player_Hit = 0;
					Dragon_Bullet_Destroy(j);
				}
			}


		}




		for (int j = 0; j < 3; j++)	//���X�{�X�����蔻��
		{
			if (Bullet_Exist(i) && LastEnemy_Parts_Exist(j))	//���X�{�X�̃p�[�c
			{
				if (Circle_Collision(Bullet_GetCollision(i), LastEnemy_Parts_Collision(j)))
				{
					score+=LastEnemy_Parts_DMG(j);
					Bullet_Destroy(i);
				}
			}
		}

		for (int j = 0; j < 4; j++)
		{
			if (Player_Exist() && TwinBullet_RightExist(j) && Player_Hit > PLAYER_INVISIBLE)	//�v���C���[�ƃc�C���o���b�g(�E��)�̔���
			{
				if (Circle_Collision(Player_GetCollision(), TwinBullet_Right_GetCollision(j)))
				{
					Player_DMG(30);
					Player_Hit = 0;
					TwinBullet_Right_Destroy(j);
				}
			}
			if (Player_Exist() && TwinBullet_LeftExist(j) && Player_Hit > PLAYER_INVISIBLE)	//�v���C���[�ƃc�C���o���b�g(����)�̔���
			{
				if (Circle_Collision(Player_GetCollision(), TwinBullet_Left_GetCollision(j)))
				{
					Player_DMG(30);
					Player_Hit = 0;
					TwinBullet_Left_Destroy(j);
				}
			}


			if (Player_Exist() && EnergyBullet_Right_Exist(j) && Player_Hit > PLAYER_INVISIBLE)
			{
				if (Circle_Collision(Player_GetCollision(), EnergyBullet_Right_GetCollision(j)))
				{
					Player_DMG(20);
					Player_Hit = 0;
					Energy_Bullet_Right_Destroy(j);
				}
			}
			if (Player_Exist() && EnergyBullet_Left_Exist(j) && Player_Hit > PLAYER_INVISIBLE)
			{
				if (Circle_Collision(Player_GetCollision(), EnergyBullet_Left_GetCollision(j)))
				{
					Player_DMG(20);
					Player_Hit = 0;
					Energy_Bullet_Left_Destroy(j);
				}
			}


		}
		

	}

	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (Player_Exist() && Dragon_Bullet_Exist(i))
		{
			if (Circle_Collision(Player_GetCollision(), Dragon_Bullet_GetCollision(i)))
			{
				Player_DMG(10);
				Bullet_Destroy(i);
			}
		}
	}

	for (int i = 0; i < 4; i++)	//�񕜃A�C�e���ƃv���C���[�̔���
	{
		if (Player_Exist() && EnergyCupsule_GetExist(i))
		{
			if (Circle_Collision(Player_GetCollision(), EnemyCupsule_GetCollision(i)))
			{
				Player_DMG(-20);	//��
				EnergyCupsule_Destroy(i);
				PlaySound(SOUND_LABEL_SE_HEAL02);
			}
		}
	}

	if (score > Draw_for_Score)	//�`��X�R�A���Z���o
	{
		Draw_for_Score+=5;
	}
	else if (score != Draw_for_Score)
	{
		Draw_for_Score = score;
	}

}

void JudgeDraw()
{
	Score_Draw(Draw_for_Score, 300, 0, 4, true, false);
}
int Get_Score()
{
	return score;
}