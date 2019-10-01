#pragma once

#ifndef SPRITE_H

#define SPRITE_H

#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//XYZとRHWを持つ頂点データを表す。	RHW:頂点座標変更完了を示すやつ

#include <d3d9.h>
#include <d3dx9.h>

typedef struct vertex2d_tag		//タグをつけることもできる。(任意)
{
	D3DXVECTOR4 position;	//頂点座標
	D3DCOLOR color;			//色情報
	D3DXVECTOR2 uv;			//画像のUV座標


}vertex1;


void Sprite_Init();	

void Sprite_Draw(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom);	//拡大、縮小。
void Sprite_Draw_Alpha(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom,int alpha);	//拡大、縮小。

//id:テクスチャのId　 d:画面座標 　cut:切り取るUV座標　c:回転の中心座標

void Sprite_SetColor(D3DCOLOR Color);

void Sprite_Uninit();

void Sprite_Draw_HP_Bule(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom,float HP);	//HPバー（青）
void Sprite_Draw_HP_Green(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom,float HP);	//HPバー（青）
void Sprite_Draw_HP_Yellow(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom,float HP);	//HPバー（青）
void Sprite_Draw_HP_Red(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom, float HP);	//HPバー（青）



void Sprite_Draw_Mirror(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h);	//反転させる。

void Sprite_Draw_Effect(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom);	//拡大、縮小。

#endif
