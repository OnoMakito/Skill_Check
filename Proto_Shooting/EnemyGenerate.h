#pragma once

#ifndef GENE_H
#define GENE_H

#include "common.h"

/*typedef struct	//敵の出現制御を構造体で行う。
{
	int frame;
	D3DXVECTOR2 Generate_Position;

}Enemy_Generater;*/

void EnemyGenerate_Init(void);
void EnemyGenerate_Update(void);
void EnemyGenerate_Uninit(void);
void EnemyGenerate_Draw(void);


int Get_EnemyGenerateFrameCount(void);

#endif
