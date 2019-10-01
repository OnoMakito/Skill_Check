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
	
	g_Effect_Bullet_Tex = Texture_SetLoadFile("Asset\\effect001.jpg", 80, 20);	//�G�t�F�N�g�̃e�N�X�`��
	g_Effect_Burner_Tex = Texture_SetLoadFile("Asset\\effect001.jpg", 20, 20);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effect[i].Life_Frame = 0;		//���݂��Ȃ�
		g_Effect[i].Create_Frame = 0;	//���݂��Ȃ�
	}


}

void Effect_Update()
{

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].Life_Frame<=0)	//�������s�����G�t�F�N�g(�܂��͑��݂��Ȃ��G�t�F�N�g)
		{
			continue;	//�������Ȃ�
		}

		int Elapsed_Frame = GetFrame() - g_Effect[i].Create_Frame;	//�����t���[��

		float Effect_Percentage = Elapsed_Frame / (float)g_Effect[i].Life_Frame;	//�����������I������

		//�e�ۂ̍��W�X�V

		if (Effect_Percentage >= 1.0f)	//�������I����(Destroy)
		{
			Effect_Percentage = 1.0f;
			g_Effect[i].Life_Frame = 0;
		}




		/*���l�͉��Z�����̎��A�e�F�ʐ����ɏ�Z����Čv�Z�����B*/
		D3DXCOLOR X_Color = g_Effect[i].Effect_Color;	//�F�ʏ��̌^�����낦��
		X_Color.a = 1.0f - Effect_Percentage;

		g_Effect[i].Effect_Color = X_Color;


	}

	

}

void Effect_Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	/*���̐ݒ�ȍ~�ɕ`�����|���S���͊��ɕ`�悳�ꂽ�F�ʂɉ��Z�������s��*/
	Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].Life_Frame>0)
		{
			if (g_Effect[i].Mode == EFFECT_BULLET)
			{
				Sprite_SetColor(g_Effect[i].Effect_Color);	//�e�G�t�F�N�g�z��̃����o�ɐݒ肳�ꂽ�F�ʏ�������B
				Sprite_Draw_Effect(g_Effect_Bullet_Tex, g_Effect[i].g_Effect_Position.x, g_Effect[i].g_Effect_Position.y, 0, 0, 80, 20, 0, 0, 0, 1);	//�G�t�F�N�g�̕`��
			}
			if (g_Effect[i].Mode == EFFECT_BURNER)
			{
				Sprite_SetColor(g_Effect[i].Effect_Color);
				Sprite_Draw_Effect(g_Effect_Burner_Tex, g_Effect[i].g_Effect_Position.x, g_Effect[i].g_Effect_Position.y, 0, 0, 20, 20, 0, 0, 0, 1);
			}
		}
	}

	Sprite_SetColor(0xFFFFFFFF);

	/*�ʏ�̃u�����h�����ɖ߂�*/
	Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
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




		//i�Ԗڂ̒e�����g�p�Ȃ�A�e�ۂ̐������J�n����B

		g_Effect[i].Life_Frame = LifeFrame;
		g_Effect[i].g_Effect_Position.x = x;
		g_Effect[i].g_Effect_Position.y = y;
		g_Effect[i].Create_Frame = GetFrame();
		g_Effect[i].Effect_Color = Color;
		g_Effect[i].Mode = Mode;

		break;	
	}

}
