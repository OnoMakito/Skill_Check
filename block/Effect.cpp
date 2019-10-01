#include "main.h"
#include "texture.h"
#include "Effect.h"
#include "Block.h"
#include "Sprite.h"
#include "ball.h"


Explosion g_Explosion[EXPLOSION_MAX];

static int g_ExplosionTexuture;
static Float2 g_ExplosionPosition;
static bool hit;
static int blocknumber;
static Float2 blockposition;
static int frame = 0;

static int speed=60;

void ExplosionInit()	//任意のタイミングで初期化
{
	g_ExplosionTexuture = LoadTexture("rom:/explosion.tga");

}

void ExplosionUpdate()	//爆発描写
{
	if (hit == false)
	{
		//hit = GetHit();	//true or false
	}
	else
	{
		speed--;	//再生中次の番号に移るまでのカウントをする。
	}

	//blocknumber = getnumber();	//最後に当たったブロック
	blockposition = getblockposition(blocknumber);

	
}

void ExplosionDraw()	//描画
{
	if (frame > EXPLOSION_MAX)	//番号が全枚数を超えていたら初期化し、描画を終了
	{
		frame =0;
		hit = false;
	}

	
	
	if (hit == true)
	{
		if (speed <= 0)	//カウントが0以下になったら次に遷移
		{
			SetTexture(g_ExplosionTexuture);	//テクスチャ設定

			DrawSprite(blockposition.x, blockposition.y, 50.0f, 50.0f,
				frame % 4 * 0.25, frame / 4 * 0.25, 0.25, 0.25,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

			frame++;	//次の番号へ
			speed = 60;
		}
	}
}

void ExplosionUninit()	//終了関数
{
	UnloadTexture(g_ExplosionTexuture);
}
