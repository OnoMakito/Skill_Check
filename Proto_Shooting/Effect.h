#pragma once


#ifndef EFFECT_H
#define EFFECT_H

#include "collision.h"


#define EFFECT_MAX (5000)

#define EFFECT_BULLET (0)
#define EFFECT_BURNER (1)

typedef struct Effect_tag
{
	D3DXVECTOR2 g_Effect_Position;
	int Life_Frame;	//消えるまでのフレーム(寿命)
	int Create_Frame;	//作成時のフレーム
	D3DCOLOR Effect_Color;	//ポリゴンの色
	int Mode;	//用途認識

}Effect;


void Effect_Init(void);	//弾丸の初期化

void Effect_Update(void);	//弾丸の更新

void Effect_Draw(void);	//弾丸の描画

void Effect_Uninit(void);	//弾丸解放処理


void Effect_Create(float x, float y,D3DCOLOR Color,int LifeFrame,int Mode);	//弾丸の生成座標設定



#endif