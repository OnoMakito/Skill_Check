#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"
#include "MyDirect3D.h"
#include "debug_font.h"
#include "system_timer.h"
#include "Player.h"
#include "BG.h"
#include "MyTex.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyGenerate.h"
#include "EnemyBullet.h" 
#include "Judgement.h"
#include "Explosion.h"
#include "number.h"
#include "score.h"
#include "sound.h"
#include "HP_Bar.h"
#include "Item.h"
#include "Fade.h"
#include "Effect.h"
#include "input.h"

static bool BgmPlay;
static bool LastBGM_Play;

void GameInit()
{
	Bg_Init();
	Bullet_Init();
	Player_Init();
	EnergyCupsule_Init();
	Enemy_Init();
	EnemyGenerate_Init();
	EnemyGenerate_Init();
	Dragon_Bullet_Init();
	TwinBullet_Init();
	EnergyBullet_Init();
	Explosion_Init();
	Number_Init();
	Score_Init();
	Judge_Init();
	HP_Bar_Init();
	Effect_Init();

	BgmPlay = false;
	LastBGM_Play = false;

	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "テクスチャエラーGAME", "エラー", MB_OK);
	}


}


void GameUpdate()
{
	if (!BgmPlay&&Get_EnemyGenerateFrameCount()<2400)	//通常戦闘曲
	{
		PlaySound(SOUND_LABEL_BGM000);	//BGM再生
		BgmPlay = true;
	}
	if (!LastBGM_Play&&Get_EnemyGenerateFrameCount()>2406)	//ラスボス戦闘曲を再生
	{
		StopSound(SOUND_LABEL_BGM000);
		PlaySound(SOUD_LABEL_BGM001);
		LastBGM_Play = true;
	}

	srand(timeGetTime());


	Player_Update();
	HP_Bar_Update();
	Bullet_Update();
	Enemy_Update();
	EnergyCupsule_Update();
	Dragon_Bullet_Update();
	TwinBullet_Update();
	EnergyBullet_Update();
	EnemyGenerate_Update();
	UpdateJudge();
	Explosion_Update();
	Effect_Update();
	Bg_Update();


	if (Keyboard_IsTrigger(DIK_P))
	{
		SetPose(5);
	}

}

void GameDraw()
{
	Bg_Draw();
	Player_Draw();
	Enemy_Draw();
	EnergyCupsule_Draw();
	Bullet_Draw();
	Dragon_Bullet_Draw();
	TwinBullet_Draw();
	EnergyBullet_Draw();
	Effect_Draw();
	Explosion_Draw();
	JudgeDraw();
	HP_Bar_Draw();
	EnemyGenerate_Draw();
}


void GameUninit()
{
	Player_Uninit();
	HP_Bar_UnInit();
	EnergyCupsule_UnInit();
	Bullet_Draw();
	Bg_Uninit();
	Enemy_Uninit();
	Dragon_Bullet_Uninit();
	TwinBullet_UnInit();
	Explosion_Uninit();
	EnemyGenerate_Uninit();
	Effect_Uninit();
}




