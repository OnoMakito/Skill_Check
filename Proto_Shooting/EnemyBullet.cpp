#include "EnemyBullet.h"
#include "Player.h"
#include "MyTex.h"
#include "PatternAnimation.h"
#include "common.h"
#include "Sprite.h"
#include "Enemy.h"
#include "sound.h"
#include "Effect.h"


static Dragon_Bullet dragon_bullet[ENEMY_BULLET_MAX];	//構造体宣言
static Twin_Bullet twin_bullet;
static Energy_Bullet energy_bullet;
static unsigned int Twin_Bullet_Tex;
static unsigned int Energy_Bullet_Tex;
static int Firing_Count;	//発射カウント

static bool Twin_Bullet_Sound;

void Dragon_Bullet_Init()
{
	//敵弾丸初期化
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		dragon_bullet[i].Exist = false;
		dragon_bullet[i].Enemy_Bullet_Circle.radius = 5;
	}

	twin_bullet.Exist = false;
	energy_bullet.Exist = false;
	for (int i = 0; i < 4; i++)
	{
		twin_bullet.Left_Bullet[i].Exist = false;
		twin_bullet.Right_Bullet[i].Exist = false;
	
		energy_bullet.Left_Bullet[i].Exist = false;
		energy_bullet.Right_Bullet[i].Exist = false;
	}
	energy_bullet.Right_Bullet[0].Enemy_Bullet_Circle.radius;
	Twin_Bullet_Sound = false;
}

void Dragon_Bullet_Update()
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (!dragon_bullet[i].Exist)
		{
			continue;
		}


		//存在している弾丸のフレーム処理
		dragon_bullet[i].Bullet_position += dragon_bullet[i].Dir;
		dragon_bullet[i].Enemy_Bullet_Circle.position = dragon_bullet[i].Bullet_position;
		dragon_bullet[i].Enemy_Bullet_Circle.position.x += 10;
		dragon_bullet[i].Enemy_Bullet_Circle.position.y += 7;

		Effect_Create(dragon_bullet[i].Bullet_position.x, dragon_bullet[i].Bullet_position.y+4, D3DCOLOR_RGBA(255, 0, 0, 255), 15, EFFECT_BULLET);


		if (dragon_bullet[i].Bullet_position.x <= -50)
		{
			Dragon_Bullet_Destroy(i);
		}
		if (dragon_bullet[i].Bullet_position.y <= -50)
		{
			Dragon_Bullet_Destroy(i);
		}
	}
}

void Dragon_Bullet_Draw()
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (!dragon_bullet[i].Exist)
		{
			continue;
		}

		PatternAnimation_Draw_EnemyBullet(dragon_bullet[i].Bullet_position.x, dragon_bullet[i].Bullet_position.y, GetFrame());
	}
}

void Dragon_Bullet_Uninit()
{

}

void Dragon_Bullet_Create(D3DXVECTOR2 shotposition)
{

	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (dragon_bullet[i].Exist)
		{
			continue;
		}


		dragon_bullet[i].Dir = Get_Player_Position()-shotposition;
		D3DXVec2Normalize(&dragon_bullet[i].Dir, &dragon_bullet[i].Dir);	//ベクトルをノーマライズ

		dragon_bullet[i].Dir *= ENEMY_BULLET_SPEED - 6;

		dragon_bullet[i].Exist = true;	//敵弾丸作成
		dragon_bullet[i].Enemy_Bullet_Circle.position = dragon_bullet[i].Bullet_position = shotposition;	//射出座標、判定座標をそろえる。
		dragon_bullet[i].Bullet_position.y += 50;
		dragon_bullet[i].Target_position = Get_Player_Position();	//ターゲットとなるプレイヤーの座標を入手
		dragon_bullet[i].Target_Angle = atan2(dragon_bullet[i].Bullet_position.y - dragon_bullet[i].Target_position.y, dragon_bullet[i].Bullet_position.x - dragon_bullet[i].Target_position.x);	//ターゲットへの射角を求める。

		dragon_bullet[i].Enemy_Bullet_Circle.position.x += 10;	//判定座標の調整
		dragon_bullet[i].Enemy_Bullet_Circle.position.y += 7;



		break;
	}

}

bool Dragon_Bullet_Exist(int index)
{
	return dragon_bullet[index].Exist;
}

Circle* Dragon_Bullet_GetCollision(int index)
{
	return &dragon_bullet[index].Enemy_Bullet_Circle;
}

void Dragon_Bullet_Destroy(int index)
{
	dragon_bullet[index].Exist = false;
}










void TwinBullet_Init()
{
	Twin_Bullet_Tex = Texture_SetLoadFile("Asset\\LastEnemy_Bullet.png", 25, 25);

	for (int i = 0; i < 4; i++)
	{
		twin_bullet.Exist = false;

		twin_bullet.Right_Bullet[i].Enemy_Bullet_Circle.radius = 7;
		twin_bullet.Right_Bullet[i].Exist = false;

		twin_bullet.Left_Bullet[i].Enemy_Bullet_Circle.radius = 7;
		twin_bullet.Left_Bullet[i].Exist = false;
	}


}

void TwinBullet_Update()
{

	if (twin_bullet.Right_Bullet[4].Exist)
	{
		for (int i = 0; i < 3; i++)
		{


			if (twin_bullet.Right_Bullet[i + 1].Bullet_position.x - twin_bullet.Right_Bullet[i].Bullet_position.x < 20)	//右側の弾丸の整列
			{
				twin_bullet.Right_Bullet[i + 1].Bullet_position.x += 1;
			}
			if (twin_bullet.Right_Bullet[i].Bullet_position.y - twin_bullet.Right_Bullet[i + 1].Bullet_position.y < 20)	//右側の弾丸の整列
			{
				twin_bullet.Right_Bullet[i + 1].Bullet_position.y -= 1;
			}

			if (twin_bullet.Left_Bullet[i + 1].Bullet_position.x - twin_bullet.Left_Bullet[i].Bullet_position.x < 20)	//左側の弾丸の整列
			{
				twin_bullet.Left_Bullet[i + 1].Bullet_position.x += 1;
			}
			if (twin_bullet.Left_Bullet[i + 1].Bullet_position.y - twin_bullet.Left_Bullet[i].Bullet_position.y < 20)	//左側の弾丸の整列
			{
				twin_bullet.Left_Bullet[i + 1].Bullet_position.y += 1;
			}

		}
	}

	if (Firing_Count >= 30)
	{
		if (!Twin_Bullet_Sound)
		{
			PlaySound(SOUND_LABEL_SE_LASTSHOT1);
			Twin_Bullet_Sound = true;
		}
		for (int i = 0; i < 4; i++)
		{
			twin_bullet.Right_Bullet[i].Bullet_position.x -= ENEMY_BULLET_SPEED;
			twin_bullet.Left_Bullet[i].Bullet_position.x -= ENEMY_BULLET_SPEED;
			Effect_Create(twin_bullet.Right_Bullet[i].Bullet_position.x, twin_bullet.Right_Bullet[i].Bullet_position.y, D3DCOLOR_RGBA(2550,0,0,255),15, EFFECT_BURNER);
			Effect_Create(twin_bullet.Left_Bullet[i].Bullet_position.x, twin_bullet.Left_Bullet[i].Bullet_position.y, D3DCOLOR_RGBA(2550,0,0,255),15, EFFECT_BURNER);
		}
	}

	if (twin_bullet.Right_Bullet[3].Bullet_position.x - twin_bullet.Right_Bullet[0].Bullet_position.x >= 60)
	{
		Firing_Count++;
	}

	if (twin_bullet.Right_Bullet[3].Bullet_position.x <= -20 && twin_bullet.Left_Bullet[3].Bullet_position.x <= -60)
	{
		Firing_Count = 0;

		for (int i = 0; i < 4; i++)
		{
			twin_bullet.Right_Bullet[i].Exist = false;
			twin_bullet.Left_Bullet[i].Exist = false;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		twin_bullet.Right_Bullet[i].Enemy_Bullet_Circle.position.x = twin_bullet.Right_Bullet[i].Bullet_position.x + 5;
		twin_bullet.Right_Bullet[i].Enemy_Bullet_Circle.position.y = twin_bullet.Right_Bullet[i].Bullet_position.y + 5;

		twin_bullet.Left_Bullet[i].Enemy_Bullet_Circle.position.x = twin_bullet.Left_Bullet[i].Bullet_position.x + 5;
		twin_bullet.Left_Bullet[i].Enemy_Bullet_Circle.position.y = twin_bullet.Left_Bullet[i].Bullet_position.y + 5;
	}


}

void TwinBullet_Draw()
{
	for (int i = 0; i < 4; i++)	//右側の弾丸の描画
	{
		if (!twin_bullet.Right_Bullet[i].Exist)
		{
			continue;
		}

		Sprite_Draw(Twin_Bullet_Tex, twin_bullet.Right_Bullet[i].Bullet_position.x, twin_bullet.Right_Bullet[i].Bullet_position.y, 0, 0, 25, 25, 0, 0, 0, 1);

	}

	for (int i = 0; i < 4; i++)	//左側の弾丸の描画
	{
		if (!twin_bullet.Left_Bullet[i].Exist)
		{
			continue;
		}

		Sprite_Draw(Twin_Bullet_Tex, twin_bullet.Left_Bullet[i].Bullet_position.x, twin_bullet.Left_Bullet[i].Bullet_position.y, 0, 0, 25, 25, 0, 0, 0, 1);

	}
}

void TwinBullet_Create(D3DXVECTOR2 shotposition)
{

	for (int i = 0; i < 4; i++)	//右側の弾丸の生成　全弾生成
	{
		if (twin_bullet.Right_Bullet[i].Exist)
		{
			continue;
		}

		twin_bullet.Right_Bullet[i].Exist = true;

		twin_bullet.Right_Bullet[i].Bullet_position.x = shotposition.x + 20;
		twin_bullet.Right_Bullet[i].Bullet_position.y = shotposition.y + 90;

		twin_bullet.Right_Bullet[i].Enemy_Bullet_Circle.position.x = shotposition.x + 1;
		twin_bullet.Right_Bullet[i].Enemy_Bullet_Circle.position.y = shotposition.y + 1;


	}

	for (int i = 0; i < 4; i++)	//左側の弾丸生成　全弾生成
	{
		if (twin_bullet.Left_Bullet[i].Exist)
		{
			continue;
		}

		twin_bullet.Left_Bullet[i].Exist = true;

		twin_bullet.Left_Bullet[i].Bullet_position.x = shotposition.x + 20;
		twin_bullet.Left_Bullet[i].Bullet_position.y = shotposition.y + 140;

		twin_bullet.Left_Bullet[i].Enemy_Bullet_Circle.position.x = shotposition.x + 1;
		twin_bullet.Left_Bullet[i].Enemy_Bullet_Circle.position.y = shotposition.y + 1;

	}
	Twin_Bullet_Sound = false;
}

void TwinBullet_UnInit()
{

}

bool TwinBullet_RightExist(int index)
{
	return twin_bullet.Right_Bullet[index].Exist;
}

bool TwinBullet_LeftExist(int index)
{
	return twin_bullet.Left_Bullet[index].Exist;
}

void TwinBullet_Right_Destroy(int index)
{
	twin_bullet.Right_Bullet[index].Exist = false;
}

void TwinBullet_Left_Destroy(int index)
{
	twin_bullet.Left_Bullet[index].Exist = false;
}

Circle* TwinBullet_Right_GetCollision(int index)
{
	return &twin_bullet.Right_Bullet[index].Enemy_Bullet_Circle;
}

Circle* TwinBullet_Left_GetCollision(int index)
{
	return &twin_bullet.Left_Bullet[index].Enemy_Bullet_Circle;
}







void EnergyBullet_Init()
{

	Energy_Bullet_Tex = Texture_SetLoadFile("Asset\\Enemy_BlueBullet.png", 60, 30);

	energy_bullet.Exist = false;
	energy_bullet.Left_Bullet->Exist = false;
	energy_bullet.Right_Bullet->Exist = false;

	energy_bullet.Right_Bullet->Enemy_Bullet_Circle.radius = 15;
	energy_bullet.Left_Bullet->Enemy_Bullet_Circle.radius = 15;

	energy_bullet.BulletWaitCount = 0;

}

void EnergyBullet_Update()
{


	if (energy_bullet.EffectExist)
	{
		energy_bullet.EffectCount++;	//エフェクトカウント


		for (int i = 0; i < 4; i++)
		{
			energy_bullet.Right_Bullet[i].Bullet_position = Get_LastEnemy_Position();
			energy_bullet.Left_Bullet[i].Bullet_position = Get_LastEnemy_Position();

			energy_bullet.Right_Bullet[i].Bullet_position.x += 25;
			energy_bullet.Right_Bullet[i].Bullet_position.y += 80;

			energy_bullet.Left_Bullet[i].Bullet_position.x += 25;
			energy_bullet.Left_Bullet[i].Bullet_position.y += 163;
		}

	}

	if (energy_bullet.EffectExist&&energy_bullet.EffectCount >= 30)	//弾丸の生成
	{
		energy_bullet.EffectExist = false;
		energy_bullet.Exist = true;
	}


	if (energy_bullet.Exist)
	{

		if (GetFrame() % 4 == 0)
		{
			if (!energy_bullet.Right_Bullet[energy_bullet.BulletWaitCount].Exist)
			{
				PlaySound(SOUND_LABEL_SE_LASTSHOT);
			}

			energy_bullet.Right_Bullet[energy_bullet.BulletWaitCount].Exist = true;	//各弾丸の処理を開始
			energy_bullet.Left_Bullet[energy_bullet.BulletWaitCount].Exist = true;	//各弾丸の処理を開始

			energy_bullet.BulletWaitCount++;

			
		}


		for (int i = 0; i < 4; i++)
		{
			if (energy_bullet.Right_Bullet[i].Exist)	//右側の弾丸の処理
			{
				energy_bullet.Right_Bullet[i].Bullet_position.x -= ENEMY_BULLET_SPEED + 8;
				energy_bullet.Right_Bullet[i].Enemy_Bullet_Circle.position.x = energy_bullet.Right_Bullet[i].Bullet_position.x + 8;
				energy_bullet.Right_Bullet[i].Enemy_Bullet_Circle.position.y = energy_bullet.Right_Bullet[i].Bullet_position.y + 5;


				if (energy_bullet.Right_Bullet[3].Bullet_position.x <= -50)
				{
					energy_bullet.Exist = false;	//最後の弾丸が画面端まで行ったら全弾消滅
					for (int i = 0; i < 4; i++)
					{
						Energy_Bullet_Right_Destroy(i);
						Energy_Bullet_Left_Destroy(i);
					}
				}

				if (energy_bullet.Right_Bullet[i].Bullet_position.x <= -50)
				{
					Energy_Bullet_Right_Destroy(i);
				}
				Effect_Create(energy_bullet.Right_Bullet[i].Bullet_position.x, energy_bullet.Right_Bullet[i].Bullet_position.y+2, D3DCOLOR_RGBA(255, 255, 255, 255), 15, EFFECT_BURNER);
			}

			if (energy_bullet.Left_Bullet[i].Exist)	//左側の弾丸の処理
			{
				energy_bullet.Left_Bullet[i].Bullet_position.x -= ENEMY_BULLET_SPEED + 8;
				energy_bullet.Left_Bullet[i].Enemy_Bullet_Circle.position.x = energy_bullet.Left_Bullet[i].Bullet_position.x + 8;
				energy_bullet.Left_Bullet[i].Enemy_Bullet_Circle.position.y = energy_bullet.Left_Bullet[i].Bullet_position.y + 5;

				if (energy_bullet.Left_Bullet[i].Bullet_position.x <= -50)
				{
					Energy_Bullet_Left_Destroy(i);
				}
				Effect_Create(energy_bullet.Left_Bullet[i].Bullet_position.x, energy_bullet.Left_Bullet[i].Bullet_position.y+2, D3DCOLOR_RGBA(255, 255, 255, 255), 30, EFFECT_BURNER);

			}
		}



	}


	if (energy_bullet.BulletWaitCount >= 4)
	{
		energy_bullet.BulletWaitCount = 0;
	}

}

void EnergyBullet_Draw()
{
	if (energy_bullet.Exist)
	{
		for (int i = 0; i < 4; i++)
		{
			if (energy_bullet.Right_Bullet[i].Exist)	//右側の弾丸の描画
			{
				Sprite_Draw(Energy_Bullet_Tex, energy_bullet.Right_Bullet[i].Bullet_position.x, energy_bullet.Right_Bullet[i].Bullet_position.y, 0, 0, 60, 30, 0, 0, 0, 1);
			}
			if (energy_bullet.Left_Bullet[i].Exist)	//右側の弾丸の描画
			{
				Sprite_Draw(Energy_Bullet_Tex, energy_bullet.Left_Bullet[i].Bullet_position.x, energy_bullet.Left_Bullet->Bullet_position.y, 0, 0, 60, 30, 0, 0, 0, 1);
			}
		}
	}

}

void EnergyBullet_UnInit()
{
}

void EnergyBullet_Create(D3DXVECTOR2 shotposition)
{

	if (energy_bullet.Exist)
	{
		return;
	}

	energy_bullet.EffectExist = true;	//エフェクト処理開始
	energy_bullet.EffectCount = 0;

	for (int i = 0; i < 4; i++)
	{
		energy_bullet.Right_Bullet[i].Bullet_position = shotposition;
		energy_bullet.Left_Bullet[i].Bullet_position = shotposition;

		energy_bullet.Right_Bullet[i].Bullet_position.x += 25;
		energy_bullet.Right_Bullet[i].Bullet_position.y += 80;

		energy_bullet.Left_Bullet[i].Bullet_position.x += 25;
		energy_bullet.Left_Bullet[i].Bullet_position.y += 153;
	}
}

void Energy_Bullet_Right_Destroy(int index)
{
	energy_bullet.Right_Bullet[index].Exist = false;

	energy_bullet.Right_Bullet[index].Enemy_Bullet_Circle.position.x = 10000;
	energy_bullet.Right_Bullet[index].Enemy_Bullet_Circle.position.y = 10000;
}

void Energy_Bullet_Left_Destroy(int index)
{
	energy_bullet.Left_Bullet[index].Exist = false;
	energy_bullet.Left_Bullet[index].Enemy_Bullet_Circle.position.x = 10000;
	energy_bullet.Left_Bullet[index].Enemy_Bullet_Circle.position.y = 10000;
}

bool EnergyBullet_Right_Exist(int index)
{
	return energy_bullet.Right_Bullet[index].Exist;
}

bool EnergyBullet_Left_Exist(int index)
{
	return energy_bullet.Left_Bullet[index].Exist;
}

bool Get_EnemyBulletEffectExist()
{
	return energy_bullet.EffectExist;
}

Circle * EnergyBullet_Right_GetCollision(int index)
{
	return &energy_bullet.Right_Bullet[index].Enemy_Bullet_Circle;
}

Circle * EnergyBullet_Left_GetCollision(int index)
{
	return &energy_bullet.Left_Bullet[index].Enemy_Bullet_Circle;
}
