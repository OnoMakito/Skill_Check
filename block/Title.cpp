#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "Title.h"
#include "controller.h"


unsigned int g_texture;
bool g_Push;


void Title_Init()
{
	g_texture = LoadTexture("rom:/Title.tga");
	g_Push = false;
}

void Title_Update()
{
	

}

void Title_Draw()
{
	SetTexture(g_texture);
	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
}


void Title_Uninit()
{
	UnloadTexture(g_texture);
}


bool Get_TitleButton()
{
	return g_Push;
}





