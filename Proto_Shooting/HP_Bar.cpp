#include "HP_Bar.h"
#include "Player.h"
#include "MyTex.h"
#include "Sprite.h"



static unsigned int HP_Bar_Tex;	//テクスチャ格納変数
static unsigned int HP_Text_Tex;

static int Player_HP;	//HP格納変数
static float Player_HPforDraw;	//描画用格納変数


void HP_Bar_Init()
{
	HP_Bar_Tex = Texture_SetLoadFile("Asset\\HP_Bar.png", 500, 50);	//テクスチャの読み込み
	HP_Text_Tex = Texture_SetLoadFile("Asset\\HP_Text.png", 100, 50);
	Player_HP = Player_HPforDraw=Get_Player_HP();	//各HP変数を初期化
}

void HP_Bar_Update()
{

	Player_HP = Get_Player_HP();	//毎フレーム　体力を更新

	if (Player_HP < Player_HPforDraw)
	{
		Player_HPforDraw--;
	}
	else if(Player_HP>Player_HPforDraw)
	{
		Player_HPforDraw++;
	}

	if (Player_HPforDraw <= 0)
	{
		Player_HPforDraw = 0;
	}

}

void HP_Bar_Draw()
{

	Sprite_Draw(HP_Text_Tex, 0, 0, 0, 0, 100, 50, 0, 0, 0, 1);


	if (Player_HP > 75)	//青表示
	{
		Sprite_Draw_HP_Bule(HP_Bar_Tex, 53, 0, 0, 0, (float)500 * (Player_HPforDraw /100), 50, 0, 0, 0, 1, (Player_HPforDraw / 100));
	}
	else if (Player_HP > 50 && Player_HP <= 75)	//緑表示
	{
		Sprite_Draw_HP_Green(HP_Bar_Tex, 53, 0, 0, 0, (float)500 * (Player_HPforDraw / 100), 50, 0, 0, 0, 1, (Player_HPforDraw / 100));
	}
	else if (Player_HP > 25 && Player_HP <= 50)	//黄色表示
	{
		Sprite_Draw_HP_Yellow(HP_Bar_Tex, 53, 0, 0, 0, (float)500 * (Player_HPforDraw / 100), 50, 0, 0, 0, 1, (Player_HPforDraw / 100));
	}
	else if (Player_HP <= 25)	//赤表示
	{
		Sprite_Draw_HP_Red(HP_Bar_Tex, 53, 0, 0, 0, (float)500 * (Player_HPforDraw / 100), 50, 0, 0, 0, 1, (Player_HPforDraw / 100));
	}

}

void HP_Bar_UnInit()
{
}



