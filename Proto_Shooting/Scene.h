#pragma once



#ifndef NOT_READ	//�ǂݍ��܂Ȃ��B
#define NOT_READ

#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "GameOver.h"


enum SCENE
{
	SCENE_TITLE,	//�^�C�g��
	SCENE_GAME,	//�Q�[��
	SCENE_RESULT,	//���U���g
	SCENE_GAMEOVER,	//�Q�[���I�[�o�[
	SCENE_RANKING,	//�����L���O
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