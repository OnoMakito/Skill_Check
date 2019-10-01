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
	g_ScoreTexture = LoadTexture("rom:/number.tga");	//�e�N�X�`���ǂݍ���


	score = -400;	//�X�R�A���������@

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
	unsigned int tmpDigits[4] = {0, 0, 0, 0};	//�ꌅ��~�l����


	tmpDigits[0] = score % 10;	//�ꌅ�ڌv�Z
	tmp = score / 10;
	
	tmpDigits[1] =tmp % 10;	//�񌅖ڌv�Z
	tmp = tmp / 10;

	tmpDigits[2] = tmp % 10;	//�O���ڌv�Z
	tmp = tmp/ 10;

	tmpDigits[3] =tmp % 10;	//�l���ڌv�Z


	SetTexture(g_ScoreTexture);

	DrawSprite(200, 200, 50.0f, 50.0f,			//��̌�
		tmpDigits[3]%5*0.2f, tmpDigits[3]/5*0.2f, 0.2f, 0.2f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	DrawSprite(260, 200, 50.0f, 50.0f,			//�S�̌�
		tmpDigits[2]%5*0.2f, tmpDigits[2]/5*0.2f, 0.2f, 0.2f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	DrawSprite(320, 200, 50.0f, 50.0f,			//�\�̌�
		tmpDigits[1]%5*0.2f, tmpDigits[1]/5*0.2f, 0.2f, 0.2f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	DrawSprite(380, 200, 50.0f, 50.0f,			//��̌�
		tmpDigits[0]%5*0.2f, tmpDigits[0]/5*0.2f, 0.2f, 0.2f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	
}

void UninitScore()
{


}


