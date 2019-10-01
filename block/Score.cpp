#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "Block.h"
#include "AccessorsHit.h"
#include "Effect.h"
#include "ball.h"

static unsigned int g_ScoreTexture;
static  Float2 g_ScorePosition;

static int score;

static bool hit[3];


void InitScore()
{
	g_ScoreTexture = LoadTexture("rom:/number.tga");	//テクスチャ読み込み


	score = -400;	//スコアを初期化　

}


void UpdateScore()
{
	for (int i = 0; i < 3; i++)
	{
		hit[i] = GetHit(i);

		if (hit[i])
		{
			score += 100;
			hit[i] = false;
		}
	}


}


void DrawScore()
{
	unsigned int tmp = 0;
	unsigned int tmpDigits[4] = {0, 0, 0, 0};	//一桁目~四桁目


	tmpDigits[0] = score % 10;	//一桁目計算
	tmp = score / 10;
	
	tmpDigits[1] =tmp % 10;	//二桁目計算
	tmp = tmp / 10;

	tmpDigits[2] = tmp % 10;	//三桁目計算
	tmp = tmp/ 10;

	tmpDigits[3] =tmp % 10;	//四桁目計算


	SetTexture(g_ScoreTexture);

	DrawSprite(200, 200, 50.0f, 50.0f,			//千の桁
		tmpDigits[3]%5*0.2f, tmpDigits[3]/5*0.2f, 0.2f, 0.2f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	DrawSprite(260, 200, 50.0f, 50.0f,			//百の桁
		tmpDigits[2]%5*0.2f, tmpDigits[2]/5*0.2f, 0.2f, 0.2f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	DrawSprite(320, 200, 50.0f, 50.0f,			//十の桁
		tmpDigits[1]%5*0.2f, tmpDigits[1]/5*0.2f, 0.2f, 0.2f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	DrawSprite(380, 200, 50.0f, 50.0f,			//一の桁
		tmpDigits[0]%5*0.2f, tmpDigits[0]/5*0.2f, 0.2f, 0.2f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	
}

void UninitScore()
{


}


