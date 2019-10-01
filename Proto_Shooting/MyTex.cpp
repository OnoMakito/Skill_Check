#define _CRT_SECURE_NO_WARNINGS

#include <d3d9.h>
#include <d3dx9.h>
#include "MyDirect3D.h"
#include "MyTex.h"


static TextureData g_TextureData[TEXTUREDATA_MAX] = {};


PDIRECT3DTEXTURE9 g_pTexture = NULL;
static LPDIRECT3DDEVICE9 g_pDevice = NULL;





/////////////////////////////////////////////////////////////////////////グローバル宣言終了


int Texture_SetLoadFile(const char*pFilename, int width, int height)	//第一引数：ファイル名　第二引数：幅　第三引数：高さ
{
	//同じファイル名を探す
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (strcmp(g_TextureData[i].filename, pFilename) == 0)	//文字列の最後には0が入っていて、最後の文字まで同じ場合最後に必ず0が一致する。
		{
			return i;
		}
	}

	//みつからなかった場合新規登録を行う
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		//使用されていない場所を探す
		if (g_TextureData[i].filename[0] != 0)	//ファイルデータ配列内のメンバ名の最初が0であれば、未使用の領域(使用可能)
		{
			continue;	//0になるまで探す（0ではない場合、この行の時点で処理を中断し、forの開始行に戻る）
		}

		//登録開始
		strcpy(g_TextureData[i].filename, pFilename);
		g_TextureData[i].width = width;
		g_TextureData[i].height = height;
		//登録完了
		return i;
	}

	return -1;	//失敗
}

int Texture_Load()
{
	g_pDevice = GetDevice();

	int error_count = 0;

	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (g_TextureData[i].filename[0] == 0)
		{
			continue;
		}

		if (g_TextureData[i].p_Texture != NULL)
		{
			continue;
		}

		//テクスチャ読み込み
		HRESULT hr=D3DXCreateTextureFromFile(g_pDevice, g_TextureData[i].filename, &g_TextureData[i].p_Texture);
		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました。", "警告", MB_OK);
			return false;
		 }
		
	}

	return error_count;
}

void Texture_Destroy(int ids[], int count)
{

	for (int i = 0; i < count; i++)
	{
		if (g_TextureData[ids[i]].p_Texture != NULL)
		{
			g_TextureData[ids[i]].p_Texture->Release();
			g_TextureData[ids[i]].height = 0;
			g_TextureData[ids[i]].width = 0;
			g_TextureData[ids[i]].p_Texture = NULL;
			g_TextureData[ids[i]].filename[0] = 0;
		}
	}


}

void Texture_Destroy(void)
{

	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (g_TextureData[i].p_Texture != NULL)
		{
			g_TextureData[i].p_Texture->Release();
			g_TextureData[i].height = 0;
			g_TextureData[i].width = 0;
			g_TextureData[i].p_Texture = NULL;
			g_TextureData[i].filename[0] = 0;
		}
	}

}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int id)
{
	return g_TextureData[id].p_Texture;

}

int Texture_GetWidth(int id)
{
	return g_TextureData[id].width;
}

int Texture_GetHeight(int id)
{
	return g_TextureData[id].height;
}

