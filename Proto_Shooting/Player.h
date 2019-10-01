#pragma once

#ifndef PLAYER_H
#define PALYER_H

#include "collision.h"

#define PLAYER_INVISIBLE (30)


typedef struct PLAYER_TAG	//プレイヤーの構造体
{
	int g_Player_HP;

	D3DXVECTOR2 g_PlayerPosition;
	Circle Player_Circle;
	bool g_Player_Exist;
}Player;

void Player_Init(void);	//初期座標・テクスチャの準備

void Player_Update(void);	//キー入力で移動・

void Player_Draw(void);	//プレイヤーの状態を監視して描画(生存・死亡・爆発など)

void Player_Uninit(void);	//テクスチャ解放(シーン終了時に開放するなら、ここに書く必要はない。)

bool Player_Exist(void);

void Player_DMG(int DMG);

void Player_Destroy(void);

D3DXVECTOR2 Get_Player_Position(void);

const Circle* Player_GetCollision(void);

int Get_Player_HP(void);

void Player_Result_Udate(void);

#endif
