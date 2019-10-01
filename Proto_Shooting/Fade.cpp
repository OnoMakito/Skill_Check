#include <d3dx9.h>
#include "Fade.h"
#include "common.h"
#include "MyTex.h"
#include "Sprite.h"
#include "MyDirect3D.h"

static bool g_InOut = false;	//In or Out
static bool g_IsFade = false;	//フェード中か否か

static int g_FadeFrame = 0;	//フェードにかける時間
static int g_FadeFrameCount = 0;	//現在の経過フェード時間(毎フレーム増加)
static int g_FadeStartFrame = 0; //スタートしたときのフレーム数を記録する変数

static D3DCOLOR g_FadeColor=0;	//ポリゴン色

static float Alpha=0;

void Fade_Init()
{
	g_InOut = false;
	g_IsFade = false;

	g_FadeFrame = 0;
	g_FadeFrameCount = 0;
	g_FadeStartFrame = 0;

	g_FadeColor = 0;	//黒・透明

	Alpha = 0;

}

void Fade_Update()
{

	if (g_IsFade)	//フェード処理
	{

		int ElapsedFrame = g_FadeFrameCount - g_FadeStartFrame;	//経過時間
		float Fade_FramePercentage = ElapsedFrame / (float)g_FadeFrame;	//全体の何割終わったか
		 Alpha = 0;


		Alpha = g_InOut ? Fade_FramePercentage : 1 - Fade_FramePercentage;	//三項演算子　
		//フェードインならFade_FramePercentageを代入
		//フェードアウトなら1-Fade_FramePercentageを代入

		D3DXCOLOR color = g_FadeColor;
		color.a = Alpha;
		g_FadeColor = color;
		



		if (g_FadeFrame <= ElapsedFrame)
		{
			g_IsFade = false;
		}


	}

	g_FadeFrameCount++;

}


void Fade_Draw()
{

	
		LPDIRECT3DDEVICE9 Device=GetDevice();



		D3DXCOLOR color = g_FadeColor;


		if (color.a < 0.0001f)
		{
			return;
		}

		Fade_Vertex  v[] = {
			{ D3DXVECTOR4(0,0,0.0f,1.0f), g_FadeColor },//0左上
		{ D3DXVECTOR4(SCREEN_WIDTH,0,0.0f,1.0f),g_FadeColor },//1右上
		{ D3DXVECTOR4(0 ,SCREEN_HEIGHT ,0.0f,1.0f) , g_FadeColor },//2左下
		{ D3DXVECTOR4(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f,1.0f) , g_FadeColor }//3右下
		};
		
		Device->SetFVF(FVF_FADE_VERTEX);
		Device->SetTexture(0, NULL);
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Fade_Vertex));

}




void Fade_UnInit()
{

}




void Fade_Start(int frame, D3DCOLOR color, bool Fade_InOut)	//開始関数
{
	g_FadeColor = color;	//色の設定
	g_FadeFrame = frame;	//フレーム数の設定
	g_InOut = Fade_InOut;	//InかOutかを設定 true:フェードアウト(暗転)・false:フェードイン(明転)

	//g_FadeStartFrame = g_FadeFrameCount;	//現在のフレーム数
	g_FadeStartFrame = GetFrame(); 

	g_IsFade = true;	//true(trueの間フェードを行う)



}



bool Fade_IsFade(void)
{
	return g_IsFade;
}
