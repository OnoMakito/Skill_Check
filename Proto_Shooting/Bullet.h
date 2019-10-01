#pragma once

#ifndef BULLET_H
#define BULLET_H
#define BULLTE_MAX (50)		//�e�ۂ̓����`��ő吔

#include "collision.h"


typedef struct Bullet_tag
{
	D3DXVECTOR2 g_BulletPosition;
	bool BulletExist;
	Circle  BulletCircle;

}Bullet;

#define BULLET_SPEED (40)	//�e�ۂ̑��x



void Bullet_Init(void);	//�e�ۂ̏�����

void Bullet_Update(void);	//�e�ۂ̍X�V

void Bullet_Draw(void);	//�e�ۂ̕`��

void Bullet_Uninit(void);	//�e�ۉ������


void Bullet_Create(float x,float y);	//�e�ۂ̐������W�ݒ�


bool Bullet_Exist(int index);

void Bullet_Destroy(int index);


const Circle* Bullet_GetCollision(int index);
#endif
