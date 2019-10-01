#include "main.h"
#include "ball.h"
#include "sprite.h"
#include "texture.h"
#include "AccessorsHit.h"
#include "Block.h"
#include "Effect.h"
#include "controller.h"

#define BALL_SPEED (10)

	unsigned int g_balltexture;




BALL ball[3];

void InitBall() 
{
	
	g_balltexture = LoadTexture("rom:/ball.tga");

	ball[0].Exist = true;
	ball[0].g_ballposition.x = 0.0f;
	ball[0].g_ballposition.y = 0.0f;

	for (int i = 1; i < 3; i++)
	{
		ball[i].Exist = false;
		ball[i].g_ballposition.x = 0.0f;
		ball[i].g_ballposition.y = 0.0f;
	}

}

void UninitBall()
{

	UnloadTexture(g_balltexture);


}

Float2 GetBallPosition(int index)
{
	return ball[index].g_ballposition;

}


void UpdateBall()
{
	for (int j = 0; j < 3; j++)
	{
		ball[j].hit = false;
		ball[j].g_playerposition = GetPlayerPosition();

		for (int i = 0; i < 30; i++)
		{
			ball[j].blockposition = GetBlockPosition(i);	//ÉuÉçÉbÉNÇÃç¿ïWéÊìæ
			bool exist = GetBlockExist(i);

			if (((ball[j].blockposition.x + 55.0f > ball[j].g_ballposition.x - 25.0f&&ball[j].blockposition.x - 55.0f < ball[j].g_ballposition.x + 25.0f) && (ball[j].blockposition.y + 25.0f > ball[j].g_ballposition.y - 25.0f&&ball[j].blockposition.y - 25.0f < ball[j].g_ballposition.y + 25.0f)) && exist == true)
			{
				ball[j].blockhit = true;
				ball[j].hit = true;
				ball[j].number = i;
				SetControllerRightVibration(7);	//âEêUìÆ
				SetControllerLeftVibration(7);	//ç∂êUìÆ

			}//110,50
		}

		if (ball[j].g_ballposition.x < -480)	//Xé≤â°à⁄ìÆÇÃêßå‰	ï«Ç∆ÇÃê⁄êG
		{
			ball[j].horizon = true;
		}
		if (ball[j].g_ballposition.x > 480)	//ï«Ç∆ÇÃê⁄êG
		{
			ball[j].horizon = false;
		}
		//////////////////////////////////


			//Yé≤à⁄ìÆÇÃêßå‰

		if (ball[j].blockhit == true && ball[j].vertical == false)
		{
			ball[j].vertical = true;
			ball[j].blockhit = false;
		}


		if (ball[j].blockhit == true && ball[j].vertical == true)
		{
			ball[j].vertical = false;
			ball[j].blockhit = true;
		}

		if (ball[j].g_ballposition.y < -480)	//ï«Ç∆ÇÃê⁄êG
		{
			ball[j].vertical = true;
			ball[j].blockhit = false;
		}
		if ((ball[j].g_playerposition.x + 100.0f > ball[j].g_ballposition.x - 25.0f&& ball[j].g_playerposition.x - 100.0f < ball[j].g_ballposition.x + 25.0f) && (ball[j].g_playerposition.y + 15.0f >= ball[j].g_ballposition.y - 25.0f&&ball[j].g_playerposition.y - 15.0f <= ball[j].g_ballposition.y + 25.0f))	//ÉqÉbÉg
		{
			ball[j].vertical = false;
			ball[j].blockhit = false;
		}
		//////////////////////////////////////


		if (ball[j].horizon == true)
		{
			ball[j].g_ballposition.x += BALL_SPEED;
		}
		else
		{
			ball[j].g_ballposition.x -= BALL_SPEED;
		}

		if (ball[j].vertical == false)
		{
			ball[j].g_ballposition.y -= BALL_SPEED;

		}
		if (ball[j].vertical == true)
		{
			ball[j].g_ballposition.y += BALL_SPEED;
		}



		if (ball[j].g_ballposition.y >= SCREEN_HEIGHT / 2)
		{
			ball[j].Exist = false;
		}

	}

	if (!ball[0].Exist&& !ball[1].Exist&& !ball[2].Exist)
	{
		SetScene(SCENE_GameOver);
	}
}



void  DrawBall()
{
	SetTexture(g_balltexture);

	for (int i = 0; i < 3; i++)
	{
		DrawSprite(ball[i].g_ballposition.x, ball[i].g_ballposition.y, 50.0f, 50.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}


bool GetHit(int index)
{
	return ball[index].hit;
}

int getnumber(int index)
{
	return ball[index].number;
}

void Ball_Create()
{
	for (int i = 0; i < 3; i++)
	{
		if (ball[i].Exist)
		{
			continue;
		}


		ball[i].Exist = true;
		ball[i].g_ballposition.x = 0;
		ball[i].g_ballposition.y = 0;

		if (i == 2)
		{
			ball[i].horizon = true;
		}
		else
		{
			ball[i].horizon = false;
		}

		ball[i].vertical = false;
		
		i = 10;
	}
}


bool GetBall_Exist(int index)
{
	return ball[index].Exist;
}