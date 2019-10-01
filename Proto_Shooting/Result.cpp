#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Result.h"
#include "MyTex.h"
#include "input.h"
#include "common.h"
#include "Sprite.h"
#include "score.h"
#include "Judgement.h"
#include "BG.h"
#include "Player.h"
#include "PatternAnimation.h"

unsigned int Result_Score_Tex;

static int Result_WaitCount;
static bool NewScore_r;


void Result_Init()
{

	Result_Score_Tex = Texture_SetLoadFile("Asset\\Score_Result.png", 418, 81);

	Result_WaitCount = 0;
	NewScore_r = false;


	FILE *fp;

	fp = fopen("Asset\\Score.txt", "r");	//ファイルの読み込み展開

	int Score[5];

	fread(&Score, sizeof(int), 5, fp);

	fclose(fp);

	int score = Get_Score();

	bool Sort = false;

	for (int i = 0; i < 5 && !Sort; i++)
	{
		if (Score[i] <= score)
		{
			for (int j = 4; i < j; j--)
			{

				Score[j] = Score[j - 1];

			}

			Score[i] = score;

			if (i == 0)
			{
				NewScore_r = true;
			}


			Sort = true;
		}
	}

	fp = fopen("Asset\\Score.txt", "w");	//ファイルの追加書き込み展開

	if (fp == NULL)
	{
		PostQuitMessage(0);
	}

	fwrite(Score, sizeof(int), 5, fp);	//セーブ

	
	fclose(fp);


}

void Result_Update()
{

	Result_WaitCount++;

	

	if (Keyboard_IsTrigger(DIK_SPACE)&&Result_WaitCount>30)
	{
		SetSecene(4);//シーン切り替え	
	}
	Bg_Update();

	Player_Result_Udate();

}

void Result_Draw()
{
	Bg_Draw();
	Player_Draw();
	Sprite_Draw(Result_Score_Tex, 0, 0, 0, 0, 418, 81, 0, 0, 0, 1);
	Score_Draw(Get_Score(), 0, 50, 4, true, false);
	PatternAnimation_Draw_TitleEnter(150, 180, GetFrame());

	if (NewScore_r)
	{
		PatternAnimation_NewScore(0, 70, GetFrame());
	}
}

void Result_UnInit()
{



}
