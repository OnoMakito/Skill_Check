#include "main.h"
#include "Result.h"
#include "Score.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"

static unsigned int g_tex_Result;

void Result_Init()
{
	g_tex_Result = LoadTexture("rom:/GAME_CLEAR.tga");
}

void Result_Update()
{

	
}

void Result_Draw()
{
	SetTexture(g_tex_Result);
	DrawSprite(0.0f, 0 , SCREEN_WIDTH, 200 , 0.0f, 0.0f, 1, 1, MakeFloat4(1, 1, 1, 1));
}

void Result_UnInit()
{

}


