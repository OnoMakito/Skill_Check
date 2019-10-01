#include "Effect.h"
#include "MyTex.h"
#include "Sprite.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "common.h"
#include "MyDirect3D.h"

static unsigned int g_Effect_Bullet_Tex;
static unsigned int g_Effect_Burner_Tex;
static Effect g_Effect[EFFECT_MAX];


void Effect_Init()
{
	
	g_Effect_Bullet_Tex = Texture_SetLoadFile("Asset\\effect001.jpg", 80, 20);	//エフェクトのテクスチャ
	g_Effect_Burner_Tex = Texture_SetLoadFile("Asset\\effect001.jpg", 20, 20);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effect[i].Life_Frame = 0;		//存在しない
		g_Effect[i].Create_Frame = 0;	//存在しない
	}


}

void Effect_Update()
{

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].Life_Frame<=0)	//寿命が尽きたエフェクト(または存在しないエフェクト)
		{
			continue;	//何もしない
		}

		int Elapsed_Frame = GetFrame() - g_Effect[i].Create_Frame;	//生存フレーム

		float Effect_Percentage = Elapsed_Frame / (float)g_Effect[i].Life_Frame;	//寿命を何割終えたか

		//弾丸の座標更新

		if (Effect_Percentage >= 1.0f)	//寿命を終える(Destroy)
		{
			Effect_Percentage = 1.0f;
			g_Effect[i].Life_Frame = 0;
		}




		/*α値は加算合成の時、各色彩成分に乗算されて計算される。*/
		D3DXCOLOR X_Color = g_Effect[i].Effect_Color;	//色彩情報の型をそろえる
		X_Color.a = 1.0f - Effect_Percentage;

		g_Effect[i].Effect_Color = X_Color;


	}

	

}

void Effect_Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	/*この設定以降に描かれるポリゴンは既に描画された色彩に加算合成を行う*/
	Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].Life_Frame>0)
		{
			if (g_Effect[i].Mode == EFFECT_BULLET)
			{
				Sprite_SetColor(g_Effect[i].Effect_Color);	//各エフェクト配列のメンバに設定された色彩情報を入れる。
				Sprite_Draw_Effect(g_Effect_Bullet_Tex, g_Effect[i].g_Effect_Position.x, g_Effect[i].g_Effect_Position.y, 0, 0, 80, 20, 0, 0, 0, 1);	//エフェクトの描画
			}
			if (g_Effect[i].Mode == EFFECT_BURNER)
			{
				Sprite_SetColor(g_Effect[i].Effect_Color);
				Sprite_Draw_Effect(g_Effect_Burner_Tex, g_Effect[i].g_Effect_Position.x, g_Effect[i].g_Effect_Position.y, 0, 0, 20, 20, 0, 0, 0, 1);
			}
		}
	}

	Sprite_SetColor(0xFFFFFFFF);

	/*通常のブレンド処理に戻す*/
	Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

void Effect_Uninit()
{
}

void Effect_Create(float x, float y, D3DCOLOR Color, int LifeFrame,int Mode)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].Life_Frame>0)
		{
			continue;
		}




		//i番目の弾が未使用なら、弾丸の生成を開始する。

		g_Effect[i].Life_Frame = LifeFrame;
		g_Effect[i].g_Effect_Position.x = x;
		g_Effect[i].g_Effect_Position.y = y;
		g_Effect[i].Create_Frame = GetFrame();
		g_Effect[i].Effect_Color = Color;
		g_Effect[i].Mode = Mode;

		break;	
	}

}
