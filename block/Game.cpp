
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
#include "sound.h"
#include "Item.h"


void GameInit()
{

	ExplosionInit();
	InitBG();
	InitPlayer();
	InitBall();
	InitBlock();
	InitScore();
	Item_Init();

}


void GameUninut()
{
	UninitBG();
	UninitPlayer();
	ExplosionUninit();
	UninitController();
	UninitSystem();
	UninitBall();
	UninitBlock();
	UninitScore();
	Item_UnInit();
}


void GameUpdate()
{

	UpdateBG();
	UpdatePlayer();
	UpdateBall();
	UpdateBlock();
	Item_Update();
	ExplosionUpdate;
	UpdateScore();
}



void GameDraw()
{


	DrawBG();
	DrawPlayer();
	DrawBall();
	Item_Draw();
	DrawBlock();
	ExplosionDraw();
	DrawScore();




}
