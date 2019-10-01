#pragma once

#ifndef BULLET_H
#define BULLET_H
#define BULLTE_MAX (50)		//’eŠÛ‚Ì“¯•`‰æÅ‘å”

#include "collision.h"


typedef struct Bullet_tag
{
	D3DXVECTOR2 g_BulletPosition;
	bool BulletExist;
	Circle  BulletCircle;

}Bullet;

#define BULLET_SPEED (40)	//’eŠÛ‚Ì‘¬“x



void Bullet_Init(void);	//’eŠÛ‚Ì‰Šú‰»

void Bullet_Update(void);	//’eŠÛ‚ÌXV

void Bullet_Draw(void);	//’eŠÛ‚Ì•`‰æ

void Bullet_Uninit(void);	//’eŠÛ‰ğ•úˆ—


void Bullet_Create(float x,float y);	//’eŠÛ‚Ì¶¬À•Wİ’è


bool Bullet_Exist(int index);

void Bullet_Destroy(int index);


const Circle* Bullet_GetCollision(int index);
#endif
