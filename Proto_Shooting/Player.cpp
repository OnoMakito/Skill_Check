#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"
#include "Player.h"
#include "MyTex.h"
#include "Sprite.h"
#include "input.h"
#include "PatternAnimation.h"
#include "Bullet.h"
#include "collision.h"
#include "Debug.h"
#include "Explosion.h"
#include "common.h"
#include "sound.h"
#include "Effect.h"

#define MOVE_SPEED (5)




static int bulletcount;	//弾丸のフレームカウント

static bool GameOver_WaitCountBool;
static int GameOver_WaitCount;

static Player player;	//プレイヤーの宣言

void Player_Init()
{
	player.g_Player_HP = 100;
	player.g_Player_Exist = true;
	player.g_PlayerPosition.x = 10;
	player.g_PlayerPosition.y = SCREEN_HEIGHT / 2;
	player.Player_Circle.radius = 2;
	GameOver_WaitCountBool = false;
	GameOver_WaitCount = 0;
}


void Player_Update()
{

	

	if (player.g_Player_HP >= 100)
	{
		player.g_Player_HP = 100;
	}


	bulletcount++;
	D3DXVECTOR2 dir(0.0f, 0.0f);	//ベクトルを入れる変数
	if (player.g_Player_Exist )
	{
		///////////////////////////////////////////////////////////////////////////キー入力
			//１フレームに一回キーボードの状態を調べる




		
		if (Keyboard_IsPress(DIK_W)||Keyboard_IsPress(DIK_UP))
		{
			dir.y -= 1;
		}

		if (Keyboard_IsPress(DIK_A) || Keyboard_IsPress(DIK_LEFT))
		{
			dir.x -= 1;
		}


		if (Keyboard_IsPress(DIK_S) || Keyboard_IsPress(DIK_DOWN))
		{
			dir.y += 1;
		}

		if (Keyboard_IsPress(DIK_D) || Keyboard_IsPress(DIK_RIGHT))
		{
			dir.x += 1;
			Effect_Create(player.g_PlayerPosition.x - 35, player.g_PlayerPosition.y + 50, 0x000055FF, 15, EFFECT_BURNER);
		}
		////////////////////////////////////////////////////////////////////////////

		D3DXVec2Normalize(&dir, &dir);	//正規化を行う

		player.g_PlayerPosition += dir * MOVE_SPEED;	//ベクトルを求める。







		if (player.g_PlayerPosition.x <= 0)			//移動制限
		{
			player.g_PlayerPosition.x = 0;
		}
		else if (player.g_PlayerPosition.x >= 300)		//移動制限
		{
			player.g_PlayerPosition.x = 300;
		}

		//g_player_position.x=MAX(g_player_position.x,PLAYER_WIDTH*0.5f); 先生のまとめ方
		//#define NOMINMAXを入れておくと、他のソースファイルで定義されたMINとMAXに影響されずに扱うことができる。

		if (player.g_PlayerPosition.y <= 0)	//移動制限
		{
			player.g_PlayerPosition.y = 0;
		}
		else if (player.g_PlayerPosition.y >= 275)	//移動制限
		{
			player.g_PlayerPosition.y = 275;
		}

		player.Player_Circle.position = player.g_PlayerPosition;
		player.Player_Circle.position.x += 20.0f;
		player.Player_Circle.position.y += 52.0f;

		/*if (Keyboard_IsTrigger(DIK_SPACE))
		{
			Bullet_Create(player.g_PlayerPosition.x, player.g_PlayerPosition.y);
		}*/

		if (Keyboard_IsPress(DIK_SPACE) && bulletcount >= 15)
		{
			Bullet_Create(player.g_PlayerPosition.x, player.g_PlayerPosition.y+30);
			bulletcount = 0;
		}

	}


	if (player.g_Player_HP <= 0)
	{
		Player_Destroy();
	}


	if (GameOver_WaitCountBool)
	{
		GameOver_WaitCount++;
	}

	if (GameOver_WaitCount >= 90)
	{
		SetSecene(3);
	}

}

void Player_Draw()
{
	if (player.g_Player_Exist)
	{
		PatternAnimation_Draw_Player(player.g_PlayerPosition.x, player.g_PlayerPosition.y+30, GetFrame());
		Debug_DrawCircle(player.Player_Circle.position.x, player.Player_Circle.position.y, player.Player_Circle.radius);
	}
}

void Player_Uninit()
{

}

bool Player_Exist()
{

	return player.g_Player_Exist;

}

void Player_DMG(int DMG)
{
	player.g_Player_HP -= DMG;
	PlaySound(SOUND_LABEL_SE_DAMAGE);
}

void Player_Destroy()
{
	Explosion_Create(player.g_PlayerPosition.x, player.g_PlayerPosition.y+30);
	player.g_Player_Exist = false;
	GameOver_WaitCountBool = true;
}

D3DXVECTOR2 Get_Player_Position()
{
	return player.g_PlayerPosition;
}

const Circle* Player_GetCollision()
{
	return &player.Player_Circle;
}

int Get_Player_HP(void)
{
	return player.g_Player_HP;
}

void Player_Result_Udate(void)
{

	
	Effect_Create(player.g_PlayerPosition.x - 35, player.g_PlayerPosition.y + 20, 0x000055FF, 15, EFFECT_BURNER);
	player.g_PlayerPosition.x += 5;

	if (player.g_PlayerPosition.x > 1500)
	{
		player.g_Player_Exist = false;
	}
}


