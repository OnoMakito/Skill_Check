#include "BG.h"
#include "MyTex.h"
#include "Sprite.h"
#include "common.h"
unsigned int BG_Tex ;	//背景テクスチャ
unsigned int Building_tex;	//建物テクスチャ変数
unsigned int BG_Ranking_tex;
unsigned int Ranking_Manual_tex;

static int BG_Position=0;
static int Building_Position;

static unsigned int Ranking_Tex;

void Bg_Init()
{
BG_Tex = Texture_SetLoadFile("Asset\\BG.jpg",474,237);
Building_tex = Texture_SetLoadFile("Asset\\BG_2.png", SCREEN_WIDTH, SCREEN_HEIGHT);
Ranking_Tex = Texture_SetLoadFile("Asset\\ranking.png", 331, 81);
BG_Ranking_tex = Texture_SetLoadFile("Asset\\Rnking_BG.jpg", SCREEN_WIDTH, SCREEN_HEIGHT);
Ranking_Manual_tex = Texture_SetLoadFile("Asset\\Ranking_Manual.png",772, 106);
}

void Bg_Update()
{
	BG_Position +=3;	//背景スクロール
	Building_Position += 30;	//背景スクロール

}

void Bg_Draw()
{
	Sprite_Draw(BG_Tex, 0, 0, BG_Position, 0, 474, 237,0,0,0,3.1);
	Sprite_Draw(Building_tex, 0, 0, Building_Position, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 1);

}

void Bg_Draw_Title()
{
	Sprite_Draw(BG_Tex, 0, 0, BG_Position, 0, 474, 237, 0, 0, 0, 3.1);

}

void Bg_Draw_Ranking()
{
	BG_Position ++;	//背景スクロール
	Sprite_Draw(BG_Ranking_tex, 0, 0, BG_Position, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 1);
	Sprite_Draw(Ranking_Tex, 0, 0, 0, 0, 331, 81, 0, 0, 0, 1);//ランキング表示
	Sprite_Draw(Ranking_Manual_tex, 200, 300, 0, 0, 772, 106, 0, 0, 0, 0.7f);
}

void Bg_Uninit()
{

}






