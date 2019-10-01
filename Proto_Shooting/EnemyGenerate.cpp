#include "EnemyGenerate.h"
#include "Enemy.h"
#include "common.h"
#include "Judgement.h"
#include "Fade.h"
#include "MyTex.h"
#include "Sprite.h"
#include "sound.h"
#include "EnemyBullet.h"

static unsigned int Warning_Tex;

static int frameCount = 0;	//一定フレームに一回敵を呼び出す計測変数
static int Generate_Framecount=0;	//敵呼び出しタイミングを計るカウント変数

static bool Last_CreateControll;	//ラスボスの呼び出し制御

static bool Warning_Bool;	//false:フェードアウト　true：フェードイン
static bool Wawrning_Exist;
static float Warning_Tex_Count;
static int Warning_Alpha_Count;
static bool Warning_Se_Bool;


void EnemyGenerate_Init()	//初期化
{
	Warning_Tex = Texture_SetLoadFile("Asset\\Warning_PopUp_proto1.png", 1440, 150);	//テクスチャの読み込み

	frameCount = 0;
	Generate_Framecount = 0;

	Last_CreateControll = false;	//ラスボスはまだ出現していない。
		
	Warning_Bool = false;

	Wawrning_Exist = false;
	Warning_Tex_Count = 0;	//テクスチャの開始位置を0に合わせる。
	Warning_Alpha_Count = 0;//透過値を最大にする
	Warning_Se_Bool = false;
}




void EnemyGenerate_Update()
{
	Generate_Framecount++;//毎フレーム計測変数を加算
	srand(timeGetTime());

	if (800 > Generate_Framecount)	//一定フレーム以上たつと次の敵が出現する。
	{

		if (frameCount % 40 == 0)	//40Fに一回呼び出される。
		{
			//敵の生成
			
			switch (rand() % 8)
			{

			case 0:
				Flier1_Create(700.0f, 10.0f);
				break;

			case 1:
				Flier1_Create(700.0f, 100.0f);
				break;

			case 2:
				Flier1_Create(700.0f, 200.0f);
				break;
			case 3:
				Flier1_Create(700.0f, 220.0f);
				break;
			case 4:
				Flier1_Create(700.0f, 50.0f);
				break;
			case 5:
				Flier1_Create(700.0f, 150.0f);
				break;

			case 6:
				Flier1_Create(700.0f, 250.0f);
				break;

			case 7:
				Flier1_Create(700.0f, 180.0f);
				break;

			case 8:
				break;

			default:
				break;
			}

		}
	}
	else if (1600 > Generate_Framecount)	//800フレーム経過後
	{
		if (frameCount % 40 == 0)	//40Fに一回呼び出される。
		{
			//敵の生成
			switch (rand() % 8)
			{

			case 0:
				Flier2_Create(700.0f, 80.0f);
				break;

			case 1:
				Flier2_Create(700.0f, 110.0f);
				break;

			case 2:
				Flier2_Create(700.0f, 140.0f);
				break;
			case 3:
				Flier2_Create(700.0f, 170.0f);
				break;
			case 4:
				Flier2_Create(700.0f, 210.0f);
				break;
			case 5:
				Flier2_Create(700.0f, 250.0f);
				break;

			case 6:
				Flier2_Create(700.0f, 290.0f);
				break;

			case 7:
				Flier2_Create(700.0f, 40.0f);
				break;

			default:

					break;


			}

		}
	}
	else if (2400 >= Generate_Framecount)//1600フレーム経過後
	{
		if (frameCount % 80== 0)	//80フレームに一回呼び出される
		{

				Dragon_Create(700.0f, 50.0f,0);
				Dragon_Create(700.0f, 200.0f,1);
				
		}
	}
	else if(2406>=Generate_Framecount)//2400フレーム経過後
	{

		for (int i = 0; i < ENEMY_BULLET_MAX; i++)
		{
			Dragon_Bullet_Destroy(i);
		}


			//ワーニング演出
		if (!Warning_Bool)	//フェードアウト
		{
			Fade_Start(30, D3DCOLOR_RGBA(255,0,0,0),true);
			Warning_Bool = true;
		}
		else	//フェードイン
		{
			Fade_Start(30, D3DCOLOR_RGBA(255, 0, 0, 255), false);
			Warning_Bool = false;
		}

		
		Wawrning_Exist = true;
		

	}
	else//2640フレーム経過後
	{
		Wawrning_Exist = false;

		if (!Last_CreateControll)	//ラスボスが呼び出されてなかったら作成する。
		{
			LastEnemy_Create();
			Last_CreateControll = true;
		}

	}

	frameCount++;

}




void EnemyGenerate_Uninit()
{




}

void EnemyGenerate_Draw(void)
{
	if (Wawrning_Exist)
	{
		Warning_Tex_Count += 1;
		Sprite_Draw(Warning_Tex, 0, 50, Warning_Tex_Count, 0, 1440+Warning_Tex_Count, 150,0,0,0,1);
		Sprite_Draw(Warning_Tex, 0, 220, -Warning_Tex_Count, 0, 1440-Warning_Tex_Count, 150,0,0,0,1);
		Warning_Alpha_Count = 255;


		if (!Warning_Se_Bool)
		{
		PlaySound(SOUND_LABEL_SE_WARNING);
	
			Warning_Se_Bool = true;
		}
		
	}
	else
	{
		if (Warning_Alpha_Count>0)
		{
			Warning_Alpha_Count -= 20;
		}
		
		if(Warning_Alpha_Count<=0)
		{
			Warning_Alpha_Count = 0;
		}
		Sprite_Draw_Alpha(Warning_Tex, 0, 50, Warning_Tex_Count, 0, 1440 + Warning_Tex_Count, 150, 0, 0, 0, 1,Warning_Alpha_Count);
		Sprite_Draw_Alpha(Warning_Tex, 0, 220, -Warning_Tex_Count, 0, 1440 - Warning_Tex_Count, 150, 0, 0, 0, 1, Warning_Alpha_Count);
	}
}
int Get_EnemyGenerateFrameCount(void)
{
	return Generate_Framecount;
}



