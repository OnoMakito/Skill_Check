#pragma once



#ifndef NOT_READ	//読み込まない。
#define NOT_READ

#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "GameOver.h"


enum SCENE
{
	SCENE_TITLE,	//タイトル
	SCENE_GAME,	//ゲーム
	SCENE_RESULT,	//リザルト
	SCENE_GAMEOVER,	//ゲームオーバー
	SCENE_RANKING,	//ランキング
	SCENE_END,
	SCENE_MAX
};


void Scene_Init(void);
void Scene_Update(void);
void Scene_Draw(void);
void Scene_UnInit(void);
void Scene_SetNextScene(SCENE nextscene);
bool Scene_Check(void);
#endif