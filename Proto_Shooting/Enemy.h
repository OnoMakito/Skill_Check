#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "collision.h"

#define ENEMY_MAX (8)
#define ENEMY_SPEED (8)

typedef struct Enemy_tag	//構造体定義
{
	int HP=100;
	D3DXVECTOR2 g_EnemyPosition;
	bool EnemyExist;
	Circle EnemyCircle;	//敵キャラの当たり判定の円
}Enemy;

typedef struct  Enemy2_tag	//波線軌道を描く敵
{
	D3DXVECTOR2 g_EnemyPosition;
	bool EnemyExist;
	Circle EnemyCircle;	//敵キャラの当たり判定の円
	float enemy2_angle = 0;	//Enemy2のy軸移動頻度
	D3DXVECTOR2 g_Enemy_Rotate_Center;	//回転軸
	int move_radius=60;	//回転軸からの幅
}Enemy2;

typedef struct  Enemy3_tag	//ドラゴン
{
	int HP=100;
	D3DXVECTOR2 g_EnemyPosition;
	bool EnemyExist;
	Circle EnemyCircle;	//敵キャラの当たり判定の円
	float enemy2_angle = 0;	//Enemy2のy軸移動頻度
	D3DXVECTOR2 g_Enemy_Rotate_Center;	//回転軸
	int move_radius = 60;	//回転軸からの幅
	int Bullet_FrameCount;
}Dragon;


typedef struct LastEnemy_Parts_tag
{
	int HP = 100;
	bool PartsExist;	//true:初期 false：損傷
	Circle Parts_Circle;
}Last_Enemy_Parts;

typedef struct Last_Enemy_tag //ラスボス(でっかい敵)
{
	D3DXVECTOR2 LastEnemy_position;	//座標
	float LastEnemy_angle = 0;	//移動値
	D3DXVECTOR2 LastEnemy_Rotate_Center;	//回転軸
	int LastEnemyMove_radius = 60;	//回転軸からの半径
	bool EnemyExist;	//状態
	Last_Enemy_Parts LeftWing;	//左翼
	Last_Enemy_Parts Right_Wing;	//右翼
	Last_Enemy_Parts Center;	//本体

	int LastEnemy_Bullet_FrameCount;

}Last_Enemy;


void Enemy_Init(void);
void Enemy_Update(void);
void Enemy_Draw(void);
void Enemy_Uninit(void);


void Flier1_Create(float x,float y);
void Flier2_Create(float x, float y);
void Dragon_Create(float x, float y,int index);
void LastEnemy_Create();

bool Flier1_Exist(int index);
bool Flier2_Exist(int index);
bool Dragon_Exist(int index);
bool LastEnemy_Parts_Exist(int index);	//0左翼　1右翼　2本体
bool LastEnemy_Exist();

void Flier1_Destroy(int index);
void Flier2_Destroy(int index);
void Dragon_Destroy(int index);
void Last_Enemy_Parts_Destroy(int index);//0左翼　1右翼　2本体

const Circle* Flier1_GetCollision(int index);
const Circle* Flier2_GetCollision(int index);
const Circle* Dragon_GetCollision(int index);
const Circle* LastEnemy_Parts_Collision(int index);

int Flier1_DMG(int index);
int Dragon_DMG(int index);
int LastEnemy_Parts_DMG(int index);	//0左翼　1右翼　2本体
D3DXVECTOR2 Get_LastEnemy_Position(void);
D3DXVECTOR2 Get_Dragon_Position(int index);

#endif
