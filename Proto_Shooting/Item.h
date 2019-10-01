#pragma once



#ifndef ITEM_H
#define ITEM_H

#include "collision.h"

typedef struct EnergyCupsule_tag
{
	bool Item_Exist;
	D3DXVECTOR2 Item_Position;
	Circle Item_Circle;
}Energy_Cupsule;



void EnergyCupsule_Init(void);
void EnergyCupsule_Update(void);
void EnergyCupsule_Draw(void);
void EnergyCupsule_UnInit(void);

void EnergyCupsule_Destroy(int index);
void EnergyCupsule_Create(D3DXVECTOR2 Dragon_Position);

bool EnergyCupsule_GetExist(int index);
const Circle* EnemyCupsule_GetCollision(int index);









#endif