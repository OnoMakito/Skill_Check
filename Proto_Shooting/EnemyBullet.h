#pragma once
#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include "collision.h"

#define ENEMY_BULLET_MAX (80)
#define ENEMY_BULLET_SPEED (10)

typedef struct Enemy_Bullet_tag
{
	D3DXVECTOR2 Bullet_position;
	D3DXVECTOR2 Target_position;
	float Target_Angle;
	Circle Enemy_Bullet_Circle;
	D3DXVECTOR2 Dir;
	bool Exist;
}Dragon_Bullet;

typedef struct TwinBullet_tag
{
	bool Exist;

	Dragon_Bullet Right_Bullet[4];
	Dragon_Bullet Left_Bullet[4];

}Twin_Bullet;

typedef struct Energy_Bullet_tag
{
	bool Exist;

	Dragon_Bullet Right_Bullet[4];
	Dragon_Bullet Left_Bullet[4];

	bool EffectExist;

	int EffectCount;
	int BulletWaitCount;

}Energy_Bullet;


//Dragon_Bulletèàóù
void Dragon_Bullet_Init(void);
void Dragon_Bullet_Update(void);
void Dragon_Bullet_Draw(void);
void Dragon_Bullet_Uninit(void);

bool Dragon_Bullet_Exist(int index);

Circle* Dragon_Bullet_GetCollision(int index);
void Dragon_Bullet_Create(D3DXVECTOR2 shotposition);	//ìGéÀåÇÅ@Createñ
void Dragon_Bullet_Destroy(int index);





//LastEnemy_Bulletèàóù
void TwinBullet_Init(void);
void TwinBullet_Update(void);
void TwinBullet_Draw(void);
void TwinBullet_UnInit(void);

bool TwinBullet_RightExist(int index);
bool TwinBullet_LeftExist(int index);

void TwinBullet_Create(D3DXVECTOR2 shotposition);
void TwinBullet_Right_Destroy(int index);
void TwinBullet_Left_Destroy(int index);
Circle* TwinBullet_Right_GetCollision(int index);
Circle* TwinBullet_Left_GetCollision(int index);




//LastEnemy_Bulletèàóù
void EnergyBullet_Init(void);
void EnergyBullet_Update(void);
void EnergyBullet_Draw(void);
void EnergyBullet_UnInit(void);

void EnergyBullet_Create(D3DXVECTOR2 shotposition);
void  Energy_Bullet_Right_Destroy(int index);
void  Energy_Bullet_Left_Destroy(int index);

bool EnergyBullet_Right_Exist(int index);
bool EnergyBullet_Left_Exist(int index);

bool Get_EnemyBulletEffectExist();

Circle* EnergyBullet_Right_GetCollision(int index);
Circle* EnergyBullet_Left_GetCollision(int index);
#endif 
