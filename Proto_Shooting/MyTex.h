#pragma once


#ifndef MT_H	//インクルードガード

#define MT_H


#include <d3d9.h>
#include <d3dx9.h>

#define TEX_FILENAME_MAX (128)	//ファイル名の最大文字
#define TEXTUREDATA_MAX (100)	//使うテクスチャの最大枚数

typedef struct TextureData_tag
{
	char filename[TEX_FILENAME_MAX];
	int width;
	int height;
	LPDIRECT3DTEXTURE9 p_Texture;
}TextureData;

int Texture_SetLoadFile(const char*pFilename, int width, int height);	//第一引数：ファイル名　第二引数：幅　第三引数：高さ
//↑予約番号：id

int Texture_Load(void);	//ファイルの読み込み	エラー件数が返り値になる。

void Texture_Destroy(int ids[], int count);	//テクスチャの解放	第一引数：解放するテクスチャ(id)の先頭アドレス　第二引数：配列数

LPDIRECT3DTEXTURE9 Texture_GetTexture(int id);	//SetLoadFileの予約値

void Texture_Destroy(void);	//オーバーロード使用

int Texture_GetWidth(int id);
int Texture_GetHeight(int id);





#endif
