#include "Debug.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "collision.h"
#include "MyDirect3D.h"
#include "Sprite.h"

#define DEBUG_CIRCLE_VERTEX (8)	//デバッグの際に表示する図形の角の数
#define DEBUG_CIRCLE_MAX (1000)	//デバッグの際に表示する図形の最大数



static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static Circle g_Circles[DEBUG_CIRCLE_MAX];	//サークルを格納、管理する配列
static int g_CircleCount = 0;	//描画するサークルの数
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static LPDIRECT3DDEVICE9 g_pDevice;	//デバイス
static D3DCOLOR g_Color = 0xFFFFFFFF;	//円の色
static D3DCOLOR g_Colors[DEBUG_CIRCLE_MAX];

static const float RadiusNum = D3DX_PI * 2.0f / DEBUG_CIRCLE_VERTEX;	//RADIANを求める

typedef struct Debug_circle_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
}Debug_Circle;


void Debug_Init()	//起動時初期化
{
#if defined(_DEBUG) || defined(DEBUG)
	g_pDevice = GetDevice();	//デバイスも取得
	g_pDevice-> CreateVertexBuffer(DEBUG_CIRCLE_VERTEX*DEBUG_CIRCLE_MAX * sizeof(Debug_Circle), D3DUSAGE_WRITEONLY,	FVF_VERTEX2D,D3DPOOL_MANAGED,&g_pVertexBuffer,NULL);	//頂点情報
	
	g_pDevice->CreateIndexBuffer(DEBUG_CIRCLE_VERTEX * 2 * DEBUG_CIRCLE_MAX * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
#endif
}

void Debug_Uninit()	//終了処理　(各変数の開放)
{
#if defined(_DEBUG) || defined(DEBUG)
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;

	}
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
#endif
}

void Debug_Begin()	//毎フレーム初期化
{
#if defined(_DEBUG) || defined(DEBUG)
	g_CircleCount = 0;	//描きたい円の数をリセットする
#endif
}

void Debug_End()	//Endだけど描画している。
{
#if defined(_DEBUG) || defined(DEBUG)


	Debug_Circle* pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);

	for (int i = 0; i < g_CircleCount; i++)	//描画する円の数
	{
		int  startIndex = i * DEBUG_CIRCLE_VERTEX;	//開始するインデックス番号を決める

		for (int j = 0; j < DEBUG_CIRCLE_VERTEX; j++)	//円を描画する
		{
			pv[startIndex+j].position.x = cos(RadiusNum*j)*g_Circles[i].radius+g_Circles[i].position.x;
			pv[startIndex+j].position.y = sin(RadiusNum*j)*g_Circles[i].radius+g_Circles[i].position.y;
			pv[startIndex+j].position.z = 0.0f;
			pv[startIndex+j].position.w = 1.0f;
			pv[startIndex+j].color = g_Colors[i];
		}
	}


	g_pVertexBuffer->Unlock();





	WORD* pI;
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, D3DLOCK_DISCARD);

	for (int i = 0; i < g_CircleCount; i++)			//描画する円の数だけインデックスの計算
	{
		int StartIndex = DEBUG_CIRCLE_VERTEX*2*i;

		for (int j = 0; j < DEBUG_CIRCLE_VERTEX; j++)
		{
		
			pI[StartIndex + j * 2 + 0] = i * DEBUG_CIRCLE_VERTEX + j;
			pI[StartIndex + j * 2 + 1] = i * DEBUG_CIRCLE_VERTEX + ((j + 1) % DEBUG_CIRCLE_VERTEX);
		}
	}

	g_pIndexBuffer->Unlock();



	///////////////////////////////////////////////////////////////////////////////////////////////描画
	g_pDevice -> SetFVF(FVF_DEBUG_CIRCLE_VERTEX);
	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(FVF_DEBUG_CIRCLE_VERTEX));
	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetTexture(0, NULL);


	g_pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, g_CircleCount*DEBUG_CIRCLE_VERTEX, 0, DEBUG_CIRCLE_VERTEX*g_CircleCount);


#endif
}

void Debug_DrawCircle(float x, float y, float radius)	//描画する円のメンバ情報を設定
{
#if defined(_DEBUG) || defined(DEBUG)
	g_Colors[g_CircleCount] = g_Color;

	g_Circles[g_CircleCount].position.x = x;
	g_Circles[g_CircleCount].position.y = y;
	g_Circles[g_CircleCount].radius = radius;

	g_CircleCount++;	//一つ数える


#endif

}

void Debug_SetColor(D3DCOLOR color)
{
#if defined(_DEBUG) || defined(DEBUG)
	g_Color = color;
#endif
}
