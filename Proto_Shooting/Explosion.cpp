#include <d3dx9.h>
#include "common.h"
#include "Explosion.h"
#include "PatternAnimation.h"


typedef struct {
	 bool Explosion_Exist;
	 D3DXVECTOR2 g_Explosion_Position;
	 float animcount;

}Explosion;

Explosion explosion[10];

void Explosion_Init(void)
{
	for (int i = 0; i < 10; i++)
	{
		explosion[i].Explosion_Exist = false;
		explosion[i].g_Explosion_Position.x = -50;
		explosion[i].g_Explosion_Position.y = -50;
	}
}

void Explosion_Update(void)
{
	for (int i= 0; i < 10; i++)
	{
		if (explosion[i].Explosion_Exist == true)
		{
			if (explosion[i].animcount >= 8)	//フラグオフ//
			{
				explosion[i].Explosion_Exist = false;
				explosion[i].animcount = 0;
			}
		}
	}
}

void Explosion_Draw(void)
{
	for (int i = 0; i < 10; i++)
	{
		if (explosion[i].Explosion_Exist)//フラグがオンの場合描画
		{
			PatternAnimation_Draw_Explosion(explosion[i].g_Explosion_Position.x, explosion[i].g_Explosion_Position.y, GetFrame());
			explosion[i].animcount += 0.25;
		}
	}
}

void Explosion_Uninit(void)
{

}

void Explosion_Create(float x, float y)
{
	for (int i = 0; i < 10; i++)
	{
		if (explosion[i].Explosion_Exist == true)
		{
			continue;
		}

		//エフェクトの生成を開始する。
		explosion[i].Explosion_Exist = true;

		explosion[i].g_Explosion_Position.x = x + 50;
		explosion[i].g_Explosion_Position.y = y - 10;
		break;
	}


}