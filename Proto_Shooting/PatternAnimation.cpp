#include <d3d9.h>
#include <d3dx9.h>
#include "MyDirect3D.h"
#include "MyTex.h"
#include "common.h"
#include "PatternAnimation.h"
#include "Sprite.h"
#include "input.h"



static unsigned int tex_player;			//プレイヤーアニメーション
static unsigned int tex_explosion;		//爆発エフェクト
static unsigned int tex_explosion2;
static unsigned int Dragon_Bullet_Tex;	//敵弾丸テクスチャ
static unsigned int Title_Enter_Tex;	//タイトル点滅
static unsigned int Effect_Tex;	//ラスボス弾丸発射直前エフェクト
static unsigned int NewScore_Tex;	//新記録テクスチャ
static unsigned int Pose_Tex;

void PatternAnimation_Init()
{
	tex_player = Texture_SetLoadFile("Asset\\戦闘機アニメーションproto.png", 106, 88);
	tex_explosion = Texture_SetLoadFile("Asset\\爆発.png", 1023, 682);
	tex_explosion2 = Texture_SetLoadFile("Asset\\exp01.png", 512, 512);
	Dragon_Bullet_Tex = Texture_SetLoadFile("Asset\\Enemy_Bullet.png", 60, 38);
	Title_Enter_Tex = Texture_SetLoadFile("Asset\\Title_Enter.png", 709, 314);
	Effect_Tex = Texture_SetLoadFile("Asset\\Effect_Bullet1.png", 300, 66);
	NewScore_Tex = Texture_SetLoadFile("Asset\\NewScore.png", 640, 290);
	Pose_Tex = Texture_SetLoadFile("Asset\\Pose.png", 749, 301);
}


void PatternAnimation_Draw_Player(float dx, float dy, int FrameCount)
{
	
	int pattern_p = FrameCount/5%FIGHTER_PATTERN_MAX;	//フレームカウンタ/待ちフレーム/パターン数
	
	
	Sprite_Draw(tex_player, dx, dy, 0, pattern_p%2*45.0f, 106, 44.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

void PatternAnimation_Draw_Explosion(float dx, float dy, int FrameCount)
{
	
	int pattern_e = FrameCount/8%EXPLOSION_PATTERN_MAX;	//フレームカウンタ/待ちフレーム/パターン数
	
	Sprite_Draw(tex_explosion, dx, dy, pattern_e%4*255, pattern_e/4*341, 255, 341, 0.0f, 0.0f, 0.0f, 0.25f);
	
}


void PatternAnimation_Draw_EnemyBullet(float dx, float dy, int FrameCount)
{
	int pattern_eb = FrameCount / 5 % ENEMY_BULLET_PATTERN_MAX;
	
	Sprite_Draw(Dragon_Bullet_Tex, dx, dy, pattern_eb % 2 * 29.5f, 38, 28.5, 38, 0, 0, 0, 1);
}

void PatternAnimation_Draw_TitleEnter(float dx, float dy, int FrameCount)
{
	int pattern_title_enter = FrameCount / 30 % TITLE_ENTER_PATTERN_MAX;

	Sprite_Draw(Title_Enter_Tex, dx, dy, 0, pattern_title_enter % 2 * 157, 709, 157, 0, 0, 0, 1);

}

void PatternAnimation_Effect(float dx, float dy, int FrameCount)
{
	int pattern_effect = FrameCount /6  % EFFECT_PATTERN_MAX;

	Sprite_Draw(Effect_Tex, dx, dy, 3+(pattern_effect % 11 *27), 0, 24.0f, 66, 0, 0, 0, 1);
}

void PatternAnimation_NewScore(float dx, float dy, int FrameCount)
{
	int Pattern_NewScore = FrameCount / 20 % 2;

	Sprite_Draw(NewScore_Tex, dx, dy, 0, 0, 640, Pattern_NewScore % 2 * 145, 0, 0, 0, 1);

}

void PatternAnimation_Pose(float dx, float dy, int FrameCount)
{
	int Pattern_Pose = FrameCount / 20 % 2;

	Sprite_Draw(Pose_Tex, dx, dy, 0, 0, 749, Pattern_Pose % 2 * 150, 0, 0, 0, 1);

}



/*void PatternAnimation_DrawProto(float dx, float dy, int FrameCount)
{
	int pattern = FrameCount / 3 % RUNNINGMAN_PATTERN_MAX;

		Sprite_Draw_Mirror(tex_anim, dx, dy, pattern % 5 * 140, pattern / 5 * 200, 140, 200);
	
}
*/




