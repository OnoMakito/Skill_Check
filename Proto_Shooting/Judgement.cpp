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
		Player_Hit = 120;	//プレイヤーの無敵経過時間を初期化(最初から無敵にはならない。) 
		score = 0;
		Draw_for_Score = 0;
	}

void UpdateJudge()
 {
	Player_Hit++;

	for (int i = 0; i < BULLTE_MAX; i++)	//弾丸配列総当たり
	{
		for (int j = 0; j < ENEMY_MAX; j++)	//敵配列総当たり(弾と敵の判定・プレイヤーと敵の判定)
		{
			if (Bullet_Exist(i) && Flier1_Exist(j))	//敵と弾丸が互いに存在するか。
			{
				if (Circle_Collision(Bullet_GetCollision(i), Flier1_GetCollision(j)))
				{
					score += Flier1_DMG(j);	//ライフ制にするのもあり
					Bullet_Destroy(i);	//ここで消すかどうかで弾に貫通などの特性を持たせることができる。

					//ここでスコア加算などを行える。
				}

			}

			if (Bullet_Exist(i) && Flier2_Exist(j))
			{
				if (Circle_Collision(Bullet_GetCollision(i), Flier2_GetCollision(j)))
				{
					Flier2_Destroy(j);	//ライフ制にするのもあり
					Bullet_Destroy(i);	//ここで消すかどうかで弾に貫通などの特性を持たせることができる。


					score += 15;
					//ここでスコア加算などを行える。
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



			if (Player_Exist() && Flier1_Exist(j)&&Player_Hit>PLAYER_INVISIBLE)	//プレイヤーが敵にぶつかったとき、一定時間無敵を与えるとともにダメージを与える。
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




		for (int j = 0; j < 3; j++)	//ラスボス当たり判定
		{
			if (Bullet_Exist(i) && LastEnemy_Parts_Exist(j))	//ラスボスのパーツ
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
			if (Player_Exist() && TwinBullet_RightExist(j) && Player_Hit > PLAYER_INVISIBLE)	//プレイヤーとツインバレット(右側)の判定
			{
				if (Circle_Collision(Player_GetCollision(), TwinBullet_Right_GetCollision(j)))
				{
					Player_DMG(30);
					Player_Hit = 0;
					TwinBullet_Right_Destroy(j);
				}
			}
			if (Player_Exist() && TwinBullet_LeftExist(j) && Player_Hit > PLAYER_INVISIBLE)	//プレイヤーとツインバレット(左側)の判定
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

	for (int i = 0; i < 4; i++)	//回復アイテムとプレイヤーの判定
	{
		if (Player_Exist() && EnergyCupsule_GetExist(i))
		{
			if (Circle_Collision(Player_GetCollision(), EnemyCupsule_GetCollision(i)))
			{
				Player_DMG(-20);	//回復
				EnergyCupsule_Destroy(i);
				PlaySound(SOUND_LABEL_SE_HEAL02);
			}
		}
	}

	if (score > Draw_for_Score)	//描画スコア加算演出
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