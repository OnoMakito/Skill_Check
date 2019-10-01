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

static int frameCount = 0;	//���t���[���Ɉ��G���Ăяo���v���ϐ�
static int Generate_Framecount=0;	//�G�Ăяo���^�C�~���O���v��J�E���g�ϐ�

static bool Last_CreateControll;	//���X�{�X�̌Ăяo������

static bool Warning_Bool;	//false:�t�F�[�h�A�E�g�@true�F�t�F�[�h�C��
static bool Wawrning_Exist;
static float Warning_Tex_Count;
static int Warning_Alpha_Count;
static bool Warning_Se_Bool;


void EnemyGenerate_Init()	//������
{
	Warning_Tex = Texture_SetLoadFile("Asset\\Warning_PopUp_proto1.png", 1440, 150);	//�e�N�X�`���̓ǂݍ���

	frameCount = 0;
	Generate_Framecount = 0;

	Last_CreateControll = false;	//���X�{�X�͂܂��o�����Ă��Ȃ��B
		
	Warning_Bool = false;

	Wawrning_Exist = false;
	Warning_Tex_Count = 0;	//�e�N�X�`���̊J�n�ʒu��0�ɍ��킹��B
	Warning_Alpha_Count = 0;//���ߒl���ő�ɂ���
	Warning_Se_Bool = false;
}




void EnemyGenerate_Update()
{
	Generate_Framecount++;//���t���[���v���ϐ������Z
	srand(timeGetTime());

	if (800 > Generate_Framecount)	//���t���[���ȏソ�Ǝ��̓G���o������B
	{

		if (frameCount % 40 == 0)	//40F�Ɉ��Ăяo�����B
		{
			//�G�̐���
			
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
	else if (1600 > Generate_Framecount)	//800�t���[���o�ߌ�
	{
		if (frameCount % 40 == 0)	//40F�Ɉ��Ăяo�����B
		{
			//�G�̐���
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
	else if (2400 >= Generate_Framecount)//1600�t���[���o�ߌ�
	{
		if (frameCount % 80== 0)	//80�t���[���Ɉ��Ăяo�����
		{

				Dragon_Create(700.0f, 50.0f,0);
				Dragon_Create(700.0f, 200.0f,1);
				
		}
	}
	else if(2406>=Generate_Framecount)//2400�t���[���o�ߌ�
	{

		for (int i = 0; i < ENEMY_BULLET_MAX; i++)
		{
			Dragon_Bullet_Destroy(i);
		}


			//���[�j���O���o
		if (!Warning_Bool)	//�t�F�[�h�A�E�g
		{
			Fade_Start(30, D3DCOLOR_RGBA(255,0,0,0),true);
			Warning_Bool = true;
		}
		else	//�t�F�[�h�C��
		{
			Fade_Start(30, D3DCOLOR_RGBA(255, 0, 0, 255), false);
			Warning_Bool = false;
		}

		
		Wawrning_Exist = true;
		

	}
	else//2640�t���[���o�ߌ�
	{
		Wawrning_Exist = false;

		if (!Last_CreateControll)	//���X�{�X���Ăяo����ĂȂ�������쐬����B
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



