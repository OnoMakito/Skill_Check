#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "GameOver.h"
#include "MyTex.h"
#include "Sprite.h"
#include "input.h"
#include "common.h"
#include "BG.h"
#include "score.h"
#include "Judgement.h"
#include "PatternAnimation.h"
#include "Enemy.h"

static unsigned int GameOver_Tex;
static int GameOver_WaitCount;

static unsigned int Result_Score_Tex;
static int Result_WaitCount;

static bool NewScore_o;

void GameOver_Init()
{

	Result_Score_Tex = Texture_SetLoadFile("Asset\\Score_Result.png", 418, 81);
	GameOver_Tex = Texture_SetLoadFile("Asset\\GAMEOVER.png", 1270, 820);
	GameOver_WaitCount = 0;
	NewScore_o = false;

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
				NewScore_o = true;
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

void GameOver_Update()
{
	GameOver_WaitCount ++ ;

	if (Keyboard_IsPress(DIK_SPACE) && GameOver_WaitCount > 30)
	{
		SetSecene(4);
	}

	Bg_Update();
	Enemy_Update();
	
}

void GameOver_Draw(void)
{
	Bg_Draw();

	Enemy_Draw();

	Sprite_Draw(GameOver_Tex, 0, 0, 0, 0, 1270, 820, 0, 0, 0, 1);


	Sprite_Draw(Result_Score_Tex, 0, 0, 0, 0, 418, 81, 0, 0, 0, 1);
	Score_Draw(Get_Score(), 0, 50, 4, true, false);
	PatternAnimation_Draw_TitleEnter(150, 200, GetFrame());
	
	if (NewScore_o)
	{
		PatternAnimation_NewScore(0, 70, GetFrame());
	}
}


void GameOver_UnInit()
{

}