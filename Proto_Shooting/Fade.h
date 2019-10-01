#pragma once


#ifndef FADE_H
#define FADE_H

#include <d3d9.h>

typedef struct Fade_Vertex_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;

}Fade_Vertex;
#define FVF_FADE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)


void Fade_Init(void);
void Fade_UnInit(void);
void Fade_Update(void);
void Fade_Draw(void);

void Fade_Start(int frame,D3DCOLOR color,bool Fade_InOut);	//フェードの開始  フェードにかけるフレーム数・ポリゴンカラー・フェードインかフェードアウトか

bool Fade_IsFade(void);	//フェード中かどうかを返す

#endif