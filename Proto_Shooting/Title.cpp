#include "Title.h"
#include "common.h"
#include "MyTex.h"
#include "input.h"
#include "BG.h"
#include "PatternAnimation.h"
#include "Sprite.h"


static unsigned int Title_Tex;
static unsigned int Title_Manual_Tex;

void Title_Init()
{

	Title_Tex = Texture_SetLoadFile("Asset\\Title.png", 1280, 720);	//タイトルテクスチャ
	Title_Manual_Tex = Texture_SetLoadFile("Asset\\Manual_Tex.png", 1280, 720);	//操作説明テクスチャ
}

void Title_Update()
{
	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		SetSecene(1);
	}
	if (Keyboard_IsTrigger(DIK_R))
	{
		SetSecene(4);
	}
}

void Title_Draw()
{

	Bg_Draw_Title();
	Sprite_Draw(Title_Tex, 0, -30, 0, 0, 1280, 720, 0, 0, 0, 1);
	PatternAnimation_Draw_TitleEnter(150, 100, GetFrame());
	Sprite_Draw(Title_Manual_Tex, 0, 0, 0, 0, 1280, 720, 0, 0, 0, 1);
	
}

void Title_UnInit()
{
}
