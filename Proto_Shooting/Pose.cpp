#include <Windows.h>
#include "Game.h"
#include "PatternAnimation.h"
#include "common.h"
#include "Sprite.h"
#include "input.h"
#include "MyDirect3D.h"
#include "Fade.h"

void Pose_Update()
{

	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		SetPose(1);
	}

}

void Pose_Draw()
{


	LPDIRECT3DDEVICE9 Device = GetDevice();


	GameDraw();

	Fade_Vertex  v[] = {
		{ D3DXVECTOR4(0,0,0.0f,1.0f), D3DXCOLOR(0,0,0,0.5f) },//0¶ã
	{ D3DXVECTOR4(SCREEN_WIDTH,0,0.0f,1.0f),D3DXCOLOR(0,0,0,0.5f) },//1‰Eã
	{ D3DXVECTOR4(0 ,SCREEN_HEIGHT ,0.0f,1.0f) , D3DXCOLOR(0,0,0,0.5f) },//2¶‰º
	{ D3DXVECTOR4(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f,1.0f) , D3DXCOLOR(0,0,0,0.5f) }//3‰E‰º
	};

	Device->SetFVF(FVF_FADE_VERTEX);
	Device->SetTexture(0, NULL);
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Fade_Vertex));

	PatternAnimation_Pose(150, 100, GetFrame());
}



