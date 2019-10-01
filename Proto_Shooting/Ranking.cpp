#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include "common.h"
#include "Ranking.h"
#include "score.h"
#include "BG.h"
#include "MyTex.h"
#include "Sprite.h"
#include "input.h"

static int Ranking_Score[5];//ì«Ç›çûÇÒÇæÉXÉRÉAÇÃäiî[ïœêî

static int Position_x[5];



void Ranking_Init()
{

	for (int i = 0; i < 5; i++)
	{
		Ranking_Score[i] = 0;
	Position_x[i] = 700;
	}

	FILE *fp;
	fp = fopen("Asset\\Score.txt", "r");

	if (fp == NULL)
	{
		PostQuitMessage(0);
	}

	
	fread(&Ranking_Score, sizeof(int), 5, fp);

	fclose(fp);


	/*for (int i = 0; i<5; ++i) {
		for (int j = i + 1; j<5; ++j) {
			if (Ranking_Score[i] < Ranking_Score[j]) {
				int tmp = Ranking_Score[i];
				Ranking_Score[i] = Ranking_Score[j];
				Ranking_Score[j] = tmp;
			}
		}
	}
	*/

}

void Ranking_Update()
{

	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		SetSecene(0);
	}

	for (int i = 0; i < 5; i++)
	{
		if (i >= 1 && Position_x[i - 1] >= 50)
		{
			Position_x[i] -= 30;
		}
		else {
			Position_x[0] -= 30;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (Position_x[i] <= 100)
		{
			Position_x[i] = 100;
		}
	}


}

void Ranking_Draw()
{
	

	Bg_Draw_Ranking();	//îwåiï`âÊ

	

	for (int i = 0; i < 5; i++)	//ÉXÉRÉAï\é¶
	{
		Score_Draw(Ranking_Score[i], Position_x[i], 50 + i * 30, 4 ,true, false);
	}
}

void Ranking_UnInit()
{

}