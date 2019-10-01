#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "collision.h"

#define ENEMY_MAX (8)
#define ENEMY_SPEED (8)

typedef struct Enemy_tag	//�\���̒�`
{
	int HP=100;
	D3DXVECTOR2 g_EnemyPosition;
	bool EnemyExist;
	Circle EnemyCircle;	//�G�L�����̓����蔻��̉~
}Enemy;

typedef struct  Enemy2_tag	//�g���O����`���G
{
	D3DXVECTOR2 g_EnemyPosition;
	bool EnemyExist;
	Circle EnemyCircle;	//�G�L�����̓����蔻��̉~
	float enemy2_angle = 0;	//Enemy2��y���ړ��p�x
	D3DXVECTOR2 g_Enemy_Rotate_Center;	//��]��
	int move_radius=60;	//��]������̕�
}Enemy2;

typedef struct  Enemy3_tag	//�h���S��
{
	int HP=100;
	D3DXVECTOR2 g_EnemyPosition;
	bool EnemyExist;
	Circle EnemyCircle;	//�G�L�����̓����蔻��̉~
	float enemy2_angle = 0;	//Enemy2��y���ړ��p�x
	D3DXVECTOR2 g_Enemy_Rotate_Center;	//��]��
	int move_radius = 60;	//��]������̕�
	int Bullet_FrameCount;
}Dragon;


typedef struct LastEnemy_Parts_tag
{
	int HP = 100;
	bool PartsExist;	//true:���� false�F����
	Circle Parts_Circle;
}Last_Enemy_Parts;

typedef struct Last_Enemy_tag //���X�{�X(�ł������G)
{
	D3DXVECTOR2 LastEnemy_position;	//���W
	float LastEnemy_angle = 0;	//�ړ��l
	D3DXVECTOR2 LastEnemy_Rotate_Center;	//��]��
	int LastEnemyMove_radius = 60;	//��]������̔��a
	bool EnemyExist;	//���
	Last_Enemy_Parts LeftWing;	//����
	Last_Enemy_Parts Right_Wing;	//�E��
	Last_Enemy_Parts Center;	//�{��

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
bool LastEnemy_Parts_Exist(int index);	//0�����@1�E���@2�{��
bool LastEnemy_Exist();

void Flier1_Destroy(int index);
void Flier2_Destroy(int index);
void Dragon_Destroy(int index);
void Last_Enemy_Parts_Destroy(int index);//0�����@1�E���@2�{��

const Circle* Flier1_GetCollision(int index);
const Circle* Flier2_GetCollision(int index);
const Circle* Dragon_GetCollision(int index);
const Circle* LastEnemy_Parts_Collision(int index);

int Flier1_DMG(int index);
int Dragon_DMG(int index);
int LastEnemy_Parts_DMG(int index);	//0�����@1�E���@2�{��
D3DXVECTOR2 Get_LastEnemy_Position(void);
D3DXVECTOR2 Get_Dragon_Position(int index);

#endif
