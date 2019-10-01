#include <d3dx9.h>
#include "Fade.h"
#include "common.h"
#include "MyTex.h"
#include "Sprite.h"
#include "MyDirect3D.h"

static bool g_InOut = false;	//In or Out
static bool g_IsFade = false;	//�t�F�[�h�����ۂ�

static int g_FadeFrame = 0;	//�t�F�[�h�ɂ����鎞��
static int g_FadeFrameCount = 0;	//���݂̌o�߃t�F�[�h����(���t���[������)
static int g_FadeStartFrame = 0; //�X�^�[�g�����Ƃ��̃t���[�������L�^����ϐ�

static D3DCOLOR g_FadeColor=0;	//�|���S���F

static float Alpha=0;

void Fade_Init()
{
	g_InOut = false;
	g_IsFade = false;

	g_FadeFrame = 0;
	g_FadeFrameCount = 0;
	g_FadeStartFrame = 0;

	g_FadeColor = 0;	//���E����

	Alpha = 0;

}

void Fade_Update()
{

	if (g_IsFade)	//�t�F�[�h����
	{

		int ElapsedFrame = g_FadeFrameCount - g_FadeStartFrame;	//�o�ߎ���
		float Fade_FramePercentage = ElapsedFrame / (float)g_FadeFrame;	//�S�̂̉����I�������
		 Alpha = 0;


		Alpha = g_InOut ? Fade_FramePercentage : 1 - Fade_FramePercentage;	//�O�����Z�q�@
		//�t�F�[�h�C���Ȃ�Fade_FramePercentage����
		//�t�F�[�h�A�E�g�Ȃ�1-Fade_FramePercentage����

		D3DXCOLOR color = g_FadeColor;
		color.a = Alpha;
		g_FadeColor = color;
		



		if (g_FadeFrame <= ElapsedFrame)
		{
			g_IsFade = false;
		}


	}

	g_FadeFrameCount++;

}


void Fade_Draw()
{

	
		LPDIRECT3DDEVICE9 Device=GetDevice();



		D3DXCOLOR color = g_FadeColor;


		if (color.a < 0.0001f)
		{
			return;
		}

		Fade_Vertex  v[] = {
			{ D3DXVECTOR4(0,0,0.0f,1.0f), g_FadeColor },//0����
		{ D3DXVECTOR4(SCREEN_WIDTH,0,0.0f,1.0f),g_FadeColor },//1�E��
		{ D3DXVECTOR4(0 ,SCREEN_HEIGHT ,0.0f,1.0f) , g_FadeColor },//2����
		{ D3DXVECTOR4(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f,1.0f) , g_FadeColor }//3�E��
		};
		
		Device->SetFVF(FVF_FADE_VERTEX);
		Device->SetTexture(0, NULL);
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Fade_Vertex));

}




void Fade_UnInit()
{

}




void Fade_Start(int frame, D3DCOLOR color, bool Fade_InOut)	//�J�n�֐�
{
	g_FadeColor = color;	//�F�̐ݒ�
	g_FadeFrame = frame;	//�t���[�����̐ݒ�
	g_InOut = Fade_InOut;	//In��Out����ݒ� true:�t�F�[�h�A�E�g(�Ó])�Efalse:�t�F�[�h�C��(���])

	//g_FadeStartFrame = g_FadeFrameCount;	//���݂̃t���[����
	g_FadeStartFrame = GetFrame(); 

	g_IsFade = true;	//true(true�̊ԃt�F�[�h���s��)



}



bool Fade_IsFade(void)
{
	return g_IsFade;
}
