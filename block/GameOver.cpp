#include "main.h"
#include "GameOver.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"

int g_tex_GAMEOVER;

void GameOver_Init()
{
	g_tex_GAMEOVER = LoadTexture("rom:/GAMEOVER.tga");
}

void GameOver_Update()
{
	/*if (GetControllerTrigger(NpadButton::A::Index))
	{
		SetScene(SCENE_TITLE);
	}*/
}

void GameOver_Draw()
{
	SetTexture(g_tex_GAMEOVER);

	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f,1.0f,1.0f, MakeFloat4(1.0f,1.0f, 1.0f, 1.0f));
}

void GameOver_Uninit()
{

}