#include "main.h"
#include "Item.h"
#include "texture.h"
#include "sprite.h"
#include "AccessorsHit.h"
#include <time.h>
#include <stdlib.h>
#include "Block.h"
#include "ball.h"

static unsigned int g_Tex_Twin;

Item Twin_Item[2];	//アイテムの実体宣言

void Item_Init()
{
	/**テクスチャ登録*/
	g_Tex_Twin = LoadTexture("rom:/Item.tga");

	for (int i = 0; i < 2; i++)
	{
		Twin_Item[i].Exist = true;

		nn::time::PosixTime RandTime;
		srand(RandTime.value);
		
		int index;
		
		Twin_Item[i].position_x = GetBlock_Position_x(index=(rand() % 30));
		Twin_Item[i].position_y = GetBlock_Position_y(index);

		
	}

}

void Item_Update()
{
	

	for (int i = 0; i < 2; i++)	//アイテム
	{
		for (int j = 0; j < 3; j++)	//ボール
		{
			Float2 Ball_Position = GetBallPosition(j);
			if (GetBall_Exist(j)&&Twin_Item[i].Exist&&Twin_Item[i].position_x+25 >= Ball_Position.x&&Twin_Item[i].position_x-25<=Ball_Position.x&&Twin_Item[i].position_y+12>=Ball_Position.y&&Twin_Item[i].position_y-12<=Ball_Position.y)
			{
				Twin_Item[i].Exist = false;
				Ball_Create();
			}
		}
	}
}

void Item_Draw()
{
	SetTexture(g_Tex_Twin);
	for (int i = 0; i < 2; i++)
	{
		if (Twin_Item[i].Exist)
		{
			SetTexture(g_Tex_Twin);

			DrawSprite(Twin_Item[i].position_x, Twin_Item[i].position_y, 50, 50, 0, 0, 1, 1, MakeFloat4(1, 1, 1, 1));
		}
	}
}

void Item_UnInit()
{



}
