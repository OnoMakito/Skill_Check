#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "Block.h"
#include "AccessorsHit.h"
#include "Effect.h"
#include "controller.h"
#include "Item.h"
#include "ball.h"

unsigned int g_BlockTexutre1;
unsigned int g_BlockTexutre2;
unsigned int g_BlockTexutre3;
Float2 ballposition;
Block block[30];
int number[3];
static bool Scene_Judge;
static int BreakBlock;
void InitBlock()
{
	g_BlockTexutre1 = LoadTexture("rom:/block1.tga");
	g_BlockTexutre2 = LoadTexture("rom:/block2.tga");
	g_BlockTexutre3 = LoadTexture("rom:/block3.tga");

	for (int i = 0; i < 30; i++)
	{
		block[i].BlockExist = true;
	}

	for (int i = 1; i < 8; i++)	//初期座標設定	0~8
	{

		block[i].BlockPosition = MakeFloat2(-400.0f + i * 110.0f, -450.0f);
	}
	for (int i = 0; i < 8; i++)	//初期座標設定	9~17
	{

		block[i + 9].BlockPosition = MakeFloat2(-400.0f + i * 110.0f, -400.0f);
	}
	for (int i = 0; i < 8; i++)	//初期座標設定	18~26
	{

		block[i + 18].BlockPosition = MakeFloat2(-400.0f + i * 110.0f, -350.0f);
	}
	for (int i = 0; i < 4; i++)	//初期座標設定	27~31
	{

		block[i + 27].BlockPosition = MakeFloat2(-400.0f + i * 110.0f, -300.0f);
	}

	Scene_Judge = false;
	BreakBlock = 0;

}

void UninitBlock()
{
	UnloadTexture(g_BlockTexutre1);
	UnloadTexture(g_BlockTexutre2);
	UnloadTexture(g_BlockTexutre3);
}

void UpdateBlock()
{

	for (int j = 0; j < 3; j++)
	{
		ballposition = GetBallPosition(j);

		BreakBlock = 0;
		for (int i = 0; i < 3; i++)
		{
			number[i] = getnumber(i);

			if (block[number[i]].BlockExist)
			{
				block[number[i]].BlockExist = false;	//ブロックの消滅



			}
	}
	}
	if (Scene_Judge)
	{
		SetScene(SCENE_RESULT);
	}

	for (int i = 0; i < 30; i++)
	{
		if (!block[i].BlockExist)
		{
			BreakBlock++;
		}
	}

	if (BreakBlock >= 30)
	{
		Scene_Judge = true;
	}

}

Float2 GetBlockPosition(int i)
{
	return block[i].BlockPosition;
}

void DrawBlock()
{
	for (int i = 0; i < 30; i++)
	{
		SetTexture(g_BlockTexutre1);

		if (block[i].BlockExist == true)
		{
			DrawSprite(block[i].BlockPosition.x, block[i].BlockPosition.y, 110.0f, 50.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

}

bool GetBlockExist(int i)
{

	return block[i].BlockExist;
}

Float2 getblockposition(int i)
{
	return block[i].BlockPosition;
}


float GetBlock_Position_x(int index)
{
	return block[index].BlockPosition.x;
}
float GetBlock_Position_y(int index)
{
	return block[index].BlockPosition.y;
}


