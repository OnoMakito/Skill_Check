#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "collision.h"

#define ENEMY_MAX (8)
#define ENEMY_SPEED (8)

typedef struct Enemy_tag	//\‘¢‘Ì’è‹`
{
	int HP=100;
	D3DXVECTOR2 g_EnemyPosition;
	bool EnemyExist;
	Circle EnemyCircle;	//“GƒLƒƒƒ‰‚Ì“–‚½‚è”»’è‚Ì‰~
}Enemy;

typedef struct  Enemy2_tag	//”gü‹O“¹‚ğ•`‚­“G
{
	D3DXVECTOR2 g_EnemyPosition;
	bool EnemyExist;
	Circle EnemyCircle;	//“GƒLƒƒƒ‰‚Ì“–‚½‚è”»’è‚Ì‰~
	float enemy2_angle = 0;	//Enemy2‚Ìy²ˆÚ“®•p“x
	D3DXVECTOR2 g_Enemy_Rotate_Center;	//‰ñ“]²
	int move_radius=60;	//‰ñ“]²‚©‚ç‚Ì•
}Enemy2;

typedef struct  Enemy3_tag	//ƒhƒ‰ƒSƒ“
{
	int HP=100;
	D3DXVECTOR2 g_EnemyPosition;
	bool EnemyExist;
	Circle EnemyCircle;	//“GƒLƒƒƒ‰‚Ì“–‚½‚è”»’è‚Ì‰~
	float enemy2_angle = 0;	//Enemy2‚Ìy²ˆÚ“®•p“x
	D3DXVECTOR2 g_Enemy_Rotate_Center;	//‰ñ“]²
	int move_radius = 60;	//‰ñ“]²‚©‚ç‚Ì•
	int Bullet_FrameCount;
}Dragon;


typedef struct LastEnemy_Parts_tag
{
	int HP = 100;
	bool PartsExist;	//true:‰Šú falseF‘¹
	Circle Parts_Circle;
}Last_Enemy_Parts;

typedef struct Last_Enemy_tag //ƒ‰ƒXƒ{ƒX(‚Å‚Á‚©‚¢“G)
{
	D3DXVECTOR2 LastEnemy_position;	//À•W
	float LastEnemy_angle = 0;	//ˆÚ“®’l
	D3DXVECTOR2 LastEnemy_Rotate_Center;	//‰ñ“]²
	int LastEnemyMove_radius = 60;	//‰ñ“]²‚©‚ç‚Ì”¼Œa
	bool EnemyExist;	//ó‘Ô
	Last_Enemy_Parts LeftWing;	//¶—ƒ
	Last_Enemy_Parts Right_Wing;	//‰E—ƒ
	Last_Enemy_Parts Center;	//–{‘Ì

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
bool LastEnemy_Parts_Exist(int index);	//0¶—ƒ@1‰E—ƒ@2–{‘Ì
bool LastEnemy_Exist();

void Flier1_Destroy(int index);
void Flier2_Destroy(int index);
void Dragon_Destroy(int index);
void Last_Enemy_Parts_Destroy(int index);//0¶—ƒ@1‰E—ƒ@2–{‘Ì

const Circle* Flier1_GetCollision(int index);
const Circle* Flier2_GetCollision(int index);
const Circle* Dragon_GetCollision(int index);
const Circle* LastEnemy_Parts_Collision(int index);

int Flier1_DMG(int index);
int Dragon_DMG(int index);
int LastEnemy_Parts_DMG(int index);	//0¶—ƒ@1‰E—ƒ@2–{‘Ì
D3DXVECTOR2 Get_LastEnemy_Position(void);
D3DXVECTOR2 Get_Dragon_Position(int index);

#endif
