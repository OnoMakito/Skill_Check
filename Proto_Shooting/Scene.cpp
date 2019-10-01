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
main分のすべてのシーン関数をScene.cppで定義した関数に置き換えることで実装が完了する。

if(Scene_Change())	//mainのUpdate/Drawの下に記述する。
{
break;
}

（先に別の方法で実装していたため、余裕がある場合改造する。多分この関数どこかミスっている)

------------------------------------------------------------------------------------------------

関数に割り振られるアドレスを応用した裏技

typedef void (*型名)(void);	//関数ポインタの型を定義
この場合引数の型をvoidにしているためvoid 型のものしかできない。
もしもboolを使うときはtype bool (*型名)(void);にする必要がある。


static const Func INITS[]={
	
	enumで定義した順にInit関数を記述する。

	｝;

	static const UPDATES[]=
	{
	enumで定義した順にUpdate関数を記述する。
	};

	以下略





Init、Udate内のswitch分をすべて消し、INITS[g_Scene]();やUpdate[g_Scene]();に置き換える。
アドレスを直接指定してそのアドレスに格納された関数を実行するためswitch分をすべて1行に省略することができる。



--------------------------------------------------------------------------------------------------*/

