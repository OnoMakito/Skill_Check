
/*最終更新日　2019/09/03　18：10

シーン遷移・フェード実装完了


*/






#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "bg.h"
#include "player.h"
#include "ball.h"
#include "Block.h"
#include "AccessorsHit.h"
#include "Effect.h"
#include "Score.h"
#include "Scene.h"
#include "Game.h"
#include "Title.h"
#include "Fade.h"
#include "GameOver.h"
#include "sound.h"
#include "Result.h"
#include "Item.h"

#define FadeFrame (60)

void Init();
void Update();
void Draw();
void Uninit();

bool InitCount=false;	//false：未実行　true：実行済み

int g_Scene = SCENE_TITLE;

int framefade = 0;
bool frameflag = false;
float frameAlpha = 0.0f;

extern "C" void nnMain()
{

Init();
	while (true)
	{
		Update();
		Draw();			

	}
	Uninit();
}



void Init()
{
	InitSound();
	InitSystem();
	InitController();

	Title_Init();
	GameInit();
	GameOver_Init();
	Result_Init();
}

void Update()
{
	UpdateController();


	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Update();
		break;

	case SCENE_GAME:
		if (!InitCount)
		{
			GameInit();
			InitCount = true;
		}
		GameUpdate();
		break;

		InitCount = false;

	case SCENE_GameOver:
		GameOver_Update();
		break;

	case SCENE_RESULT:
		Result_Update();
		break;
	}

	if ((g_Scene == SCENE_TITLE || g_Scene == SCENE_RESULT) && GetControllerTrigger(NpadButton::A::Index))
	{
		frameflag = true;
	}
	if (g_Scene == SCENE_GameOver)
	{
		frameflag = true;
	}

	FadeUpdate();
	UpdateSound();
}

void Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Draw();
		break;

	case SCENE_GAME:
		GameDraw();
		break;

	case SCENE_GameOver:
		GameDraw();
	//	GameOver_Draw();
		break;

	case SCENE_RESULT:
		GameDraw();
		Result_Draw();
		break;
	}

	if (frameflag)
	{

		SetTexture(NULL);
		DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, MakeFloat4(0.0f, 0.0f, 0.0f, frameAlpha));
		frameAlpha += 1.0f / FadeFrame;
		if (frameAlpha >= 1)
		{
			frameAlpha = 0;

			frameflag = false;

			switch (g_Scene)
			{
			case SCENE_TITLE:
				SetScene(SCENE_GAME);
				
				break;

			case SCENE_GameOver:
				SetScene(SCENE_TITLE);
				break;

			case SCENE_RESULT:
				SetScene(SCENE_TITLE);
				break;
				
			}
		}
	}
	

	

	FadeDraw();

	SwapBuffers();
}

void Uninit()
{
	UninitSystem();

	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Uninit();
		break;

	case SCENE_GAME:
		GameUninut();
		break;
	case SCENE_GameOver:
		GameOver_Uninit();
		break;
	case SCENE_RESULT:
		Result_UnInit();
		break;

	}

	UninitSound(); 
}


void SetScene(SCENE scene)
{
	g_Scene = scene;
	InitCount = false;
}






