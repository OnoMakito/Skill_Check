#include "Scene.h"


static SCENE g_Scene = SCENE_TITLE;
static SCENE g_NextScene = SCENE_TITLE;


void Scene_Init()
{
	switch (g_NextScene)
	{
	case SCENE_TITLE:
		Title_Init();
		break;

	case SCENE_GAME:
		GameInit();
		break;

	case SCENE_RESULT:
		Result_Init();
		break;
	case SCENE_GAMEOVER:
		GameOver_Init();
		break;
		
	/*case SCENE_RANKING:
		Ranking_Init();
		break;*/

	default:
		break;
	}
}



void Scene_Update()
{
	switch (g_NextScene)
	{
	case SCENE_TITLE:
		Title_Update();
		break;

	case SCENE_GAME:
		GameUpdate();
		break;

	case SCENE_RESULT:
		Result_Update();
		break;
	case SCENE_GAMEOVER:
		GameOver_Update();
		break;

		/*case SCENE_RANKING:
		Ranking_Update();
		break;*/

	default:
		break;
	}
}


void Scene_Draw()
{
	switch (g_NextScene)
	{
	case SCENE_TITLE:
		Title_Draw();
		break;

	case SCENE_GAME:
		GameDraw();
		break;

	case SCENE_RESULT:
		Result_Draw();
		break;
	case SCENE_GAMEOVER:
		GameOver_Draw();
		break;

		/*case SCENE_RANKING:
		Ranking_Draw();
		break;*/

	default:
		break;
	}
}


void Scene_UnInit()
{
	



	switch (g_NextScene)
	{
	case SCENE_TITLE:
		Title_UnInit();
		break;

	case SCENE_GAME:
		GameUninit();
		break;

	case SCENE_RESULT:
		Result_UnInit();
		break;
	case SCENE_GAMEOVER:
		GameOver_UnInit();
		break;

		/*case SCENE_RANKING:
		Ranking_UnInit();
		break;*/

	default:
		break;
	}
}

void Scene_SetNextScene(SCENE nextscene)
{
	g_Scene = nextscene;

}

bool Scene_Check()
{
	if (g_NextScene == SCENE_END)
	{
		return true;
	}
	Scene_Init();
	return false;
}




/*-----------------------------------------------------------------------------------------------
main���̂��ׂẴV�[���֐���Scene.cpp�Œ�`�����֐��ɒu�������邱�ƂŎ�������������B

if(Scene_Change())	//main��Update/Draw�̉��ɋL�q����B
{
break;
}

�i��ɕʂ̕��@�Ŏ������Ă������߁A�]�T������ꍇ��������B�������̊֐��ǂ����~�X���Ă���)

------------------------------------------------------------------------------------------------

�֐��Ɋ���U����A�h���X�����p�������Z

typedef void (*�^��)(void);	//�֐��|�C���^�̌^���`
���̏ꍇ�����̌^��void�ɂ��Ă��邽��void �^�̂��̂����ł��Ȃ��B
������bool���g���Ƃ���type bool (*�^��)(void);�ɂ���K�v������B


static const Func INITS[]={
	
	enum�Œ�`��������Init�֐����L�q����B

	�p;

	static const UPDATES[]=
	{
	enum�Œ�`��������Update�֐����L�q����B
	};

	�ȉ���





Init�AUdate����switch�������ׂď����AINITS[g_Scene]();��Update[g_Scene]();�ɒu��������B
�A�h���X�𒼐ڎw�肵�Ă��̃A�h���X�Ɋi�[���ꂽ�֐������s���邽��switch�������ׂ�1�s�ɏȗ����邱�Ƃ��ł���B



--------------------------------------------------------------------------------------------------*/

