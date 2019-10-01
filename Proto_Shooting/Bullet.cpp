#include "common.h"
#include "Bullet.h"
#include "MyTex.h"
#include "Sprite.h"
#include "collision.h"
#include "Explosion.h"
#include "Sound.h"
#include "Effect.h"





static unsigned int Bullet_Tex;

static Bullet g_Bullets[BULLTE_MAX];

void Bullet_Init()
{
	Bullet_Tex = Texture_SetLoadFile("Asset\\弾丸.png", 326, 35);
	for (int i = 0; i < BULLTE_MAX; i++)
	{
		g_Bullets[i].BulletCircle.radius = 10;
		g_Bullets[i].BulletExist = false;
	}
	
}

void Bullet_Update()
{
	for (int i = 0; i < BULLTE_MAX; i++)
	{
		if (g_Bullets[i].BulletExist == false)
		{
			continue;	//何もしない
		}

		//弾丸の座標更新
		g_Bullets[i].g_BulletPosition.x += BULLET_SPEED;
		g_Bullets[i]. BulletCircle.position = g_Bullets[i].g_BulletPosition;
		g_Bullets[i].BulletCircle.position.x += 20;


			Effect_Create(g_Bullets[i].g_BulletPosition.x + 10.0f, g_Bullets[i].g_BulletPosition.y+5 , D3DCOLOR_RGBA(255, 100, 100, 255), 5,EFFECT_BULLET);
		
			
		if (g_Bullets[i].g_BulletPosition.x >= SCREEN_WIDTH)	//弾丸の移動制限
		{
			g_Bullets[i].BulletExist = false;
		}

	}
}

void Bullet_Draw()
{
	for (int i = 0; i < BULLTE_MAX; i++)
	{
		if (g_Bullets[i].BulletExist)
		{
			Sprite_Draw(Bullet_Tex, g_Bullets[i].g_BulletPosition.x, g_Bullets[i].g_BulletPosition.y, 0, 0, 326, 35, 0, 0, 0, 1.0f);
		}
	}
}


void Bullet_Uninit()
{

}


void Bullet_Create(float x, float y)	//弾丸の生成
{
	for (int i = 0; i < BULLTE_MAX; i++)
	{
		if (g_Bullets[i].BulletExist == true)
		{
			continue;
		}




		//i番目の弾が未使用なら、弾丸の生成を開始する。

		g_Bullets[i].BulletExist = true;

		g_Bullets[i].g_BulletPosition.x = x;
		g_Bullets[i].g_BulletPosition.y = y+20;

		g_Bullets[i].BulletCircle.position.x = x+326;
		g_Bullets[i].BulletCircle.position.y = y+20;
	
		PlaySound(SOUND_LABEL_SE_SHOT);

		break;	//ここでブレイクしないと、1024発の弾が重なって発射される。
	}

}

bool Bullet_Exist(int index)
{
	return g_Bullets[index].BulletExist;
}

void Bullet_Destroy(int index)
{
	Explosion_Create(g_Bullets[index].g_BulletPosition.x+150, g_Bullets[index].g_BulletPosition.y+17.5f);
	g_Bullets[index].BulletExist = false;
}



const Circle* Bullet_GetCollision(int index)
{
	return &g_Bullets[index].BulletCircle;
}



