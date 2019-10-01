#include "common.h"
#include "Enemy.h"
#include "MyTex.h"
#include "Sprite.h"
#include "collision.h"
#include "Debug.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "Explosion.h"
#include "common.h"
#include "EnemyGenerate.h"
#include "PatternAnimation.h"
#include "Item.h"
#include "sound.h"
#include "Effect.h"

static unsigned int Flier1_Tex;	//テクスチャ変数
static unsigned int Flier2_Tex;
static unsigned int Dragon_Tex;
static unsigned  int LastEnemy_Pattern_Tex;
static int Enemy_WaitCount;
static bool WaitCountBool;


Enemy flier1[ENEMY_MAX];	//構造体宣言
Enemy2 flier2[ENEMY_MAX];
Dragon dragon[ENEMY_MAX];
Last_Enemy LastEnemy;


void Enemy_Init()
{
	Flier1_Tex = Texture_SetLoadFile("Asset\\Enemy1.png", 194, 239);
	Flier2_Tex = Texture_SetLoadFile("Asset\\Enemy2.png", 112, 130);
	Dragon_Tex = Texture_SetLoadFile("Asset\\Dragon.png", 180, 232);
	LastEnemy_Pattern_Tex = Texture_SetLoadFile("Asset\\LastEnemy_Pattern.png",510, 520);

	for (int i = 0; i < ENEMY_MAX; i++)	//敵状態初期化
	{
		flier1[i].HP = 100;
		flier1[i].EnemyCircle.radius = 50;//当たり判定の半径
		flier1[i].EnemyCircle.position.x = 10000;
		flier1[i].EnemyCircle.position.y = 10000;
		flier1[i].EnemyExist = false;

		flier2[i].EnemyCircle.radius = 28;
		flier2[i].EnemyCircle.position.x = 10000;
		flier2[i].EnemyCircle.position.y = 10000;
		flier2[i].EnemyExist = false;

		dragon[i].EnemyCircle.radius = 50;
		dragon[i].EnemyCircle.position.x = 10000;
		dragon[i].EnemyCircle.position.y = 10000;
		dragon[i].EnemyExist = false;

	}


	//ラスボス判定初期化・状態を初期化
	LastEnemy.EnemyExist = false;

	LastEnemy.LeftWing.PartsExist = false;
	LastEnemy.Right_Wing.PartsExist = false;
	LastEnemy.Center.PartsExist = false;
	
	LastEnemy.LeftWing.Parts_Circle.radius = 50;
	LastEnemy.Right_Wing.Parts_Circle.radius = 50;
	LastEnemy.Center.Parts_Circle.radius = 50;

	LastEnemy.LastEnemy_Bullet_FrameCount = 0;

	Enemy_WaitCount = 0;
	WaitCountBool = false;
}


void Enemy_Update()
{
	for (int i = 0; i < ENEMY_MAX; i++)	//Enemy1の更新処理
	{
		if (!flier1[i].EnemyExist)
		{
			flier1[i].EnemyCircle.position.x = 10000;
			flier1[i].EnemyCircle.position.y = 10000;
			continue;	//これより先の処理はせずに何もしない
		}
		
		//敵の座標更新
		flier1[i].g_EnemyPosition.x -= ENEMY_SPEED-2;
		flier1[i].EnemyCircle.position = flier1[i].g_EnemyPosition;	//当たり判定計測円の座標を更新
		flier1[i].EnemyCircle.position.x += 100;//調整
		flier1[i].EnemyCircle.position.y += 45;//調整
		if (flier1[i].g_EnemyPosition.x <= -180)	//敵の移動制限
		{
			flier1[i].EnemyExist=false;
		}
		if (flier1[i].HP <= 0)
		{
			Flier1_Destroy(i);
		}

		Effect_Create(flier1[i].g_EnemyPosition.x+40, flier1[i].g_EnemyPosition.y+55, D3DCOLOR_RGBA(255, 255, 0, 255), 10, EFFECT_BURNER);

	}


	for (int i = 0; i < ENEMY_MAX; i++)	//Enemy2の更新処理
	{
		if (!flier2[i].EnemyExist)
		{
			flier2[i].EnemyCircle.position.x = 10000;
			flier2[i].EnemyCircle.position.y = 10000;
			continue;
		}

		flier2[i].enemy2_angle += 0.1f;

		//敵の座標更新
		flier2[i].g_EnemyPosition.x -= ENEMY_SPEED;
		flier2[i].g_Enemy_Rotate_Center.x -= ENEMY_SPEED;
		flier2[i].g_EnemyPosition.y = sin(flier2[i].enemy2_angle)*flier2[i].move_radius+flier2[i].g_Enemy_Rotate_Center.y;
		flier2[i].EnemyCircle.position = flier2[i].g_EnemyPosition;	//当たり判定計測円の座標を更新
		flier2[i].EnemyCircle.position.x +=50;//調整
		flier2[i].EnemyCircle.position.y += 40;//調整

		Effect_Create(flier2[i].g_EnemyPosition.x + 10, flier2[i].g_EnemyPosition.y + 28, D3DCOLOR_RGBA(255, 0, 0, 255), 20, EFFECT_BURNER);

		if (flier2[i].g_EnemyPosition.x <= -180)	//敵の移動制限
		{
			flier2[i].EnemyExist = false;
		}
	}

	for (int i = 0; i < ENEMY_MAX; i++)	//Enemy3の更新処理
	{

		
			if (dragon[i].HP <= 0&&dragon[i].EnemyExist)	//体力がなくなった場合関数で消滅
			{
				Dragon_Destroy(i);
			}
		
			if (Get_EnemyGenerateFrameCount() < 2400)	//ラスボスが来るまで戦闘
			{
				if (!dragon[i].EnemyExist)
				{
					dragon[i].EnemyCircle.position.x = 10000;
					dragon[i].EnemyCircle.position.x = 10000;
					continue;	//ここから先の処理は行わない。
				}

				dragon[i].enemy2_angle += 0.05;

				//敵の座標更新
				if (dragon[i].g_EnemyPosition.x >= 500)
				{
					dragon[i].g_EnemyPosition.x -= ENEMY_SPEED;
					dragon[i].g_Enemy_Rotate_Center.x -= ENEMY_SPEED - 2;
				}

				dragon[i].g_EnemyPosition.y = sin(dragon[i].enemy2_angle)*dragon[i].move_radius + dragon[i].g_Enemy_Rotate_Center.y;	//上下移動
				dragon[i].EnemyCircle.position = dragon[i].g_EnemyPosition;	//判定座標更新
				dragon[i].EnemyCircle.position.x += 100;	//判定座標調整
				dragon[i].EnemyCircle.position.y += 50;	//判定座標調整

			

				if (dragon[i].Bullet_FrameCount % 30 == 0)
				{
					Dragon_Bullet_Create(dragon[i].g_EnemyPosition);	//弾丸発射
				}
			
			}
			else				//ラスボス出現時のドラゴンの退避
			{						
				dragon[i].g_EnemyPosition.x += 2;
				if (dragon[i].g_EnemyPosition.x > 2000)
				{
					dragon[i].EnemyExist = false;
				}
			}

		if (dragon[i].g_EnemyPosition.x <= -180)	//敵の移動制限
		{
			dragon[i].EnemyExist = false;
		}


		dragon[i].Bullet_FrameCount++;

	}





	if (LastEnemy.EnemyExist)	//ラスボスの更新処理
	{
		if (LastEnemy.LeftWing.PartsExist || LastEnemy.Right_Wing.PartsExist || LastEnemy.Center.PartsExist)
		{
			LastEnemy.LastEnemy_Bullet_FrameCount++;


			if (LastEnemy.LastEnemy_position.x > 380)	//一定のx座標でy座標更新(上下運動)
			{
				LastEnemy.LastEnemy_position.x -= ENEMY_SPEED - 5;
				LastEnemy.LastEnemy_Rotate_Center.x -= ENEMY_SPEED - 7;
			}
			else
			{
				LastEnemy.LastEnemy_position.y = sin(LastEnemy.LastEnemy_angle)*LastEnemy.LastEnemyMove_radius + LastEnemy.LastEnemy_Rotate_Center.y;
				LastEnemy.LastEnemy_angle += 0.02;
			}

			//ラスボス　当たり判定座標調整
			//右翼
			LastEnemy.Right_Wing.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 120;
			LastEnemy.Right_Wing.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 50;
			//本体
			LastEnemy.Center.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 150;
			LastEnemy.Center.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 130;
			//左翼
			LastEnemy.LeftWing.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 150;
			LastEnemy.LeftWing.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 240;


			//損傷処理
			if (LastEnemy.LeftWing.HP <= 0)
			{
				if (LastEnemy.LeftWing.PartsExist)
				{
					EnergyCupsule_Create(LastEnemy.LeftWing.Parts_Circle.position);	//回復アイテム生成
				}
				LastEnemy.LeftWing.PartsExist = false;	//左翼損傷
			}
			if (LastEnemy.Right_Wing.HP <= 0)
			{
				if (LastEnemy.Right_Wing.PartsExist)
				{
					EnergyCupsule_Create(LastEnemy.Right_Wing.Parts_Circle.position);	//回復アイテム生成
				}
				LastEnemy.Right_Wing.PartsExist = false;	//右翼損傷
			}
			if (LastEnemy.Center.HP <= 0)
			{
				if (LastEnemy.Center.PartsExist)
				{
					EnergyCupsule_Create(LastEnemy.Center.Parts_Circle.position);	//回復アイテム生成
				}
				LastEnemy.Center.PartsExist = false;	//センター部損傷
			}

			if (LastEnemy.LastEnemy_Bullet_FrameCount % 90 == 0)	//弾丸の生成
			{
				TwinBullet_Create(LastEnemy.LastEnemy_position);
			}

			if (LastEnemy.LastEnemy_Bullet_FrameCount % 180 == 0)	//弾丸の生成
			{
				EnergyBullet_Create(LastEnemy.LastEnemy_position);
			}
			if (LastEnemy.LastEnemy_Bullet_FrameCount % 150==0)	//弾丸の生成
			{
				Dragon_Bullet_Create(LastEnemy.LastEnemy_position);
			}

		}
		else if (!LastEnemy.LeftWing.PartsExist && !LastEnemy.Right_Wing.PartsExist && !LastEnemy.Center.PartsExist)	//全損傷演出
		{
			LastEnemy.LastEnemy_position.x++;	//後退しつつ落下する
			LastEnemy.LastEnemy_position.y += 2;

			if (LastEnemy.LastEnemy_position.y+100 >= 400)	//爆発して消滅
			{
				Explosion_Create(LastEnemy.LastEnemy_position.x+100, LastEnemy.LastEnemy_position.y+100);
				Explosion_Create(LastEnemy.LastEnemy_position.x+200, LastEnemy.LastEnemy_position.y+100);
				Explosion_Create(LastEnemy.LastEnemy_position.x+150, LastEnemy.LastEnemy_position.y+100);
				Explosion_Create(LastEnemy.LastEnemy_position.x+130, LastEnemy.LastEnemy_position.y+100);
				Explosion_Create(LastEnemy.LastEnemy_position.x+180, LastEnemy.LastEnemy_position.y+100);
				LastEnemy.EnemyExist = false;
				WaitCountBool=true;
			}

		}

	}

	if (WaitCountBool)
	{
		Enemy_WaitCount++;
	}

	if (Enemy_WaitCount > 60)
	{
		SetSecene(2);
	}

}

void Enemy_Draw()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (flier1[i].EnemyExist)	//Flire1描画
		{
			Sprite_Draw(Flier1_Tex, flier1[i].g_EnemyPosition.x, flier1[i].g_EnemyPosition.y, 0, 0, 194, 239, 0, 0, 0, 1);
			Debug_DrawCircle(flier1[i].EnemyCircle.position.x, flier1[i].EnemyCircle.position.y, flier1[i].EnemyCircle.radius);
		}
	
		if (flier2[i].EnemyExist)	//Flier2描画
		{
			Sprite_Draw(Flier2_Tex, flier2[i].g_EnemyPosition.x, flier2[i].g_EnemyPosition.y, 0, 0, 112, 130, 0, 0, 0, 1);
			Debug_DrawCircle(flier2[i].EnemyCircle.position.x, flier2[i].EnemyCircle.position.y, flier2[i].EnemyCircle.radius);
		}
		if (dragon[i].EnemyExist)	//Dragon描画
		{
			Sprite_Draw(Dragon_Tex, dragon[i].g_EnemyPosition.x, dragon[i].g_EnemyPosition.y, 0, 0, 180, 232, 0, 0, 0, 1);
			Debug_DrawCircle(dragon[i].EnemyCircle.position.x, dragon[i].EnemyCircle.position.y, dragon[i].EnemyCircle.radius);
		}
	}

	if (LastEnemy.EnemyExist)	//ラスボス描画
	{
		if (!LastEnemy.LeftWing.PartsExist|| !LastEnemy.Right_Wing.PartsExist|| !LastEnemy.Center.PartsExist)//損傷あり
		{
			if (!LastEnemy.LeftWing.PartsExist&&LastEnemy.Right_Wing.PartsExist&&LastEnemy.Center.PartsExist)	//左翼のみ損傷
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 0, 352, 161, 166, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.Right_Wing.Parts_Circle.position.x, LastEnemy.Right_Wing.Parts_Circle.position.y, LastEnemy.Right_Wing.Parts_Circle.radius);
				Debug_DrawCircle(LastEnemy.Center.Parts_Circle.position.x, LastEnemy.Center.Parts_Circle.position.y, LastEnemy.Center.Parts_Circle.radius);

			}
			if (LastEnemy.LeftWing.PartsExist && !LastEnemy.Right_Wing.PartsExist&&LastEnemy.Center.PartsExist)	//右翼のみ損傷
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 0, 184, 161, 166, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.LeftWing.Parts_Circle.position.x, LastEnemy.LeftWing.Parts_Circle.position.y, LastEnemy.LeftWing.Parts_Circle.radius);
				Debug_DrawCircle(LastEnemy.Center.Parts_Circle.position.x, LastEnemy.Center.Parts_Circle.position.y, LastEnemy.Center.Parts_Circle.radius);
			}
			if (!LastEnemy.Center.PartsExist&&LastEnemy.LeftWing.PartsExist&&LastEnemy.Right_Wing.PartsExist)	//本体のみ損傷
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 320, 0, 161, 182, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.Right_Wing.Parts_Circle.position.x, LastEnemy.Right_Wing.Parts_Circle.position.y, LastEnemy.Right_Wing.Parts_Circle.radius);
				Debug_DrawCircle(LastEnemy.LeftWing.Parts_Circle.position.x, LastEnemy.LeftWing.Parts_Circle.position.y, LastEnemy.LeftWing.Parts_Circle.radius);
			}
			if (!LastEnemy.LeftWing.PartsExist&&!LastEnemy.Center.PartsExist&&LastEnemy.Right_Wing.PartsExist)	//左翼・本体損傷
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 343, 354, 161, 166, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.Right_Wing.Parts_Circle.position.x, LastEnemy.Right_Wing.Parts_Circle.position.y, LastEnemy.Right_Wing.Parts_Circle.radius);
			}
			if (!LastEnemy.LeftWing.PartsExist && !LastEnemy.Right_Wing.PartsExist&&LastEnemy.Center.PartsExist)	//左翼・右翼損傷
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 343, 185, 153, 159, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.Center.Parts_Circle.position.x, LastEnemy.Center.Parts_Circle.position.y, LastEnemy.Center.Parts_Circle.radius);
			}
			if (!LastEnemy.Center.PartsExist && !LastEnemy.Right_Wing.PartsExist&&LastEnemy.LeftWing.PartsExist)	//右翼・本体損傷
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 161, 184, 161, 166, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.LeftWing.Parts_Circle.position.x, LastEnemy.LeftWing.Parts_Circle.position.y, LastEnemy.LeftWing.Parts_Circle.radius);
			}
			if (!LastEnemy.LeftWing.PartsExist && !LastEnemy.Right_Wing.PartsExist && !LastEnemy.Center.PartsExist)	//全壊
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 162, 0, 161, 166, 0, 0, 0, 1);
			}
		}
		else
		{
			Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 0, 0, 161, 182, 0, 0, 0, 1);	//初期状態(損傷なし)
			Debug_DrawCircle(LastEnemy.Right_Wing.Parts_Circle.position.x, LastEnemy.Right_Wing.Parts_Circle.position.y, LastEnemy.Right_Wing.Parts_Circle.radius);
			Debug_DrawCircle(LastEnemy.LeftWing.Parts_Circle.position.x, LastEnemy.LeftWing.Parts_Circle.position.y, LastEnemy.LeftWing.Parts_Circle.radius);
			Debug_DrawCircle(LastEnemy.Center.Parts_Circle.position.x, LastEnemy.Center.Parts_Circle.position.y, LastEnemy.Center.Parts_Circle.radius);
		}

		if (Get_EnemyBulletEffectExist())//ラスボスによる一部弾丸生成時呼び動作としてエフェクトを入れる
		{
			PatternAnimation_Effect(LastEnemy.LastEnemy_position.x-30 , LastEnemy.LastEnemy_position.y + 66, GetFrame());
			PatternAnimation_Effect(LastEnemy.LastEnemy_position.x-30 , LastEnemy.LastEnemy_position.y + 153, GetFrame());
		}

	}

}

void Enemy_Uninit()
{


}



void Flier1_Create(float x, float y)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (flier1[i].EnemyExist)
		{
			continue;
		}




		//存在しない敵の生成を開始する。

		flier1[i].EnemyExist = true;
		flier1[i].HP = 100;
		flier1[i].g_EnemyPosition.x = x;
		flier1[i].g_EnemyPosition.y = y;

		flier1[i].EnemyCircle.position.x = x + 130;
		flier1[i].EnemyCircle.position.y = y + 116;
		break;
	}
}

void Flier2_Create(float x, float y)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (flier2[i].EnemyExist)
		{
			continue;
		}




		//存在しない敵の生成を開始する。

		flier2[i].EnemyExist = true;

		flier2[i].enemy2_angle = 0;

		flier2[i].g_EnemyPosition.x = x;
		flier2[i].g_EnemyPosition.y = y;

		flier2[i].g_Enemy_Rotate_Center.x = x - 20.0f;
		flier2[i].g_Enemy_Rotate_Center.y = y;

		flier2[i].EnemyCircle.position.x = x + 130;
		flier2[i].EnemyCircle.position.y = y + 116;
		break;
	}
}

void Dragon_Create(float x, float y,int index)
{
	
		if (dragon[index].EnemyExist)
		{
			return;
		}

		//存在しない敵を生成する

		dragon[index].EnemyExist = true;
		dragon[index].HP = 100;
		dragon[index].enemy2_angle = 0;
		dragon[index].g_EnemyPosition.x = x;
		dragon[index].g_EnemyPosition.y = y;
		dragon[index].g_Enemy_Rotate_Center.x = x - 20.0f;
		dragon[index].g_Enemy_Rotate_Center.y = y;
		dragon[index].EnemyCircle.position.x = x + 130;
		dragon[index].EnemyCircle.position.y = y + 116;

		

	

}

void LastEnemy_Create()
{
	if (!LastEnemy.EnemyExist)
	{
		LastEnemy.EnemyExist = true;	//状態：真

		LastEnemy.LeftWing.PartsExist = true;	//左翼状態：初期
		LastEnemy.Right_Wing.PartsExist = true;	//右翼状態：初期
		LastEnemy.Center.PartsExist = true;		//本体状態：初期
		
		LastEnemy.LeftWing.HP = 200;	//左翼耐久力設定	
		LastEnemy.Right_Wing.HP = 200;	//右翼耐久力設定
		LastEnemy.Center.HP = 250;		//本体耐久力設定


		LastEnemy.LastEnemy_position.x = 800;	//ラスボス座標設定
		LastEnemy.LastEnemy_position.y = 70;		//ラスボス座標設定

		LastEnemy.LastEnemy_Rotate_Center.y = LastEnemy.LastEnemy_position.y;

		LastEnemy.LeftWing.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 150;	//左翼当たり判定座標
		LastEnemy.LeftWing.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 50;

		LastEnemy.Center.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 120;	//右翼当たり判定座標
		LastEnemy.Center.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 150;

		LastEnemy.Right_Wing.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 150;	//本体当たり判定座標
		LastEnemy.Center.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 250;

		LastEnemy.LastEnemy_angle = 0;	//移動値初期化
		//各パーツの初期座標設定
		//各パーツの回転軸、角度、半径を初期化

	}
}


bool Flier1_Exist(int index)//存在するかどうか
{
	return flier1[index].EnemyExist;
}

bool Flier2_Exist(int index)//存在するかどうか
{
	return  flier2[index].EnemyExist;
}

bool Dragon_Exist(int index)//存在するかどうか
{
	return dragon[index].EnemyExist;
}

bool LastEnemy_Parts_Exist(int index)//存在するかどうか
{
	switch (index)
	{
	case 0:
		return LastEnemy.LeftWing.PartsExist;
		break;

	case 1:
		return LastEnemy.Right_Wing.PartsExist;
		break;

	case 2:
		return LastEnemy.Center.PartsExist;
		break;
	
	}

}

bool LastEnemy_Exist()//存在するかどうか
{
	return LastEnemy.EnemyExist;
}

void Flier1_Destroy(int index)//消滅処理
{
	flier1[index].EnemyExist = false;
	flier1[index].EnemyCircle.position.x = 10000;
	flier1[index].EnemyCircle.position.y = 10000;
}

void Flier2_Destroy(int index)//消滅処理
{
	flier2[index].EnemyExist = false;
	flier2[index].EnemyCircle.position.x = 10000;
	flier2[index].EnemyCircle.position.y = 10000;
	PlaySound(SOUND_LABEL_SE_DAMAGE);
}

void Dragon_Destroy(int index)//消滅処理
{
	srand(timeGetTime());
	int Item_Create=rand()%10;

	if (Item_Create<=4)
	{
		EnergyCupsule_Create(dragon[index].g_EnemyPosition);	//40％の確率で回復アイテム生成
	}

	dragon[index].EnemyExist = false;
	dragon[index].EnemyCircle.position.x = 10000;
	dragon[index].EnemyCircle.position.y = 10000;
}

void Last_Enemy_Parts_Destroy(int index)	//ラスボスパーツの破壊
{
	switch (index)
	{
	case 0:
		LastEnemy.LeftWing.PartsExist = false;
		break;
	
	case 1:
		LastEnemy.Right_Wing.PartsExist = false;
		break;

	case 2:
		LastEnemy.Center.PartsExist = false;
		break;
	
	
	
	}

	
}


const Circle* Flier1_GetCollision(int index)	//当たり判定
{
	return &flier1[index].EnemyCircle;
}
const Circle* Flier2_GetCollision(int index)//当たり判定
{
	return &flier2[index].EnemyCircle;
}

const Circle* Dragon_GetCollision(int index)//当たり判定
{
	return &dragon[index].EnemyCircle;
}

const Circle* LastEnemy_Parts_Collision(int index)//当たり判定
{


	switch (index)
	{
	case 0:
		return &LastEnemy.LeftWing.Parts_Circle;
		break;
	
	case 1:
		return &LastEnemy.Right_Wing.Parts_Circle;
		break;

	case 2:
		return &LastEnemy.Center.Parts_Circle;
		break;

	}

}

int Flier1_DMG(int index)//敵ダメージ
{
	flier1[index].HP -= 50;

	PlaySound(SOUND_LABEL_SE_DAMAGE);

	if (flier1[index].HP <= 0)
	{
		Flier1_Destroy(index);

		return 20;
	}

	return 0;
}

int Dragon_DMG(int index)//敵ダメージ
{
	dragon[index].HP -= 15;	//ダメージ

	PlaySound(SOUND_LABEL_SE_DAMAGE);

	if (dragon[index].HP <= 0)
	{
		return 100;	//スコア返却
	}

	return 0;
}

int LastEnemy_Parts_DMG(int index)//敵ダメージ
{

	PlaySound(SOUND_LABEL_SE_DAMAGE);

	switch (index)
	{
	case 0:
		LastEnemy.LeftWing.HP -= 10;	//ダメージ
		if (LastEnemy.LeftWing.HP <= 0)
		{
			return 200;	//スコア加算
		}
		return 0;
		break;

	case 1:
		LastEnemy.Right_Wing.HP -= 10;//ダメージ
		if (LastEnemy.Right_Wing.HP <= 0)
		{
			return 200;//スコア加算
		}
		return 0;
		break;

	case 2:
		LastEnemy.Center.HP -= 10;	//ダメージ
		if (LastEnemy.Center.HP <= 0)
		{
			return 200;	//スコア加算
		}
		return 0;
		break;

	
	}




}

D3DXVECTOR2 Get_LastEnemy_Position(void)//座標取得
{
	return LastEnemy.LastEnemy_position;
}

D3DXVECTOR2 Get_Dragon_Position(int index)//座標取得
{
	return dragon[index].g_EnemyPosition;
}


