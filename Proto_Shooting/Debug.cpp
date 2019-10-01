#include "Debug.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "collision.h"
#include "MyDirect3D.h"
#include "Sprite.h"

#define DEBUG_CIRCLE_VERTEX (8)	//�f�o�b�O�̍ۂɕ\������}�`�̊p�̐�
#define DEBUG_CIRCLE_MAX (1000)	//�f�o�b�O�̍ۂɕ\������}�`�̍ő吔



static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static Circle g_Circles[DEBUG_CIRCLE_MAX];	//�T�[�N�����i�[�A�Ǘ�����z��
static int g_CircleCount = 0;	//�`�悷��T�[�N���̐�
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static LPDIRECT3DDEVICE9 g_pDevice;	//�f�o�C�X
static D3DCOLOR g_Color = 0xFFFFFFFF;	//�~�̐F
static D3DCOLOR g_Colors[DEBUG_CIRCLE_MAX];

static const float RadiusNum = D3DX_PI * 2.0f / DEBUG_CIRCLE_VERTEX;	//RADIAN�����߂�

typedef struct Debug_circle_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
}Debug_Circle;


void Debug_Init()	//�N����������
{
#if defined(_DEBUG) || defined(DEBUG)
	g_pDevice = GetDevice();	//�f�o�C�X���擾
	g_pDevice-> CreateVertexBuffer(DEBUG_CIRCLE_VERTEX*DEBUG_CIRCLE_MAX * sizeof(Debug_Circle), D3DUSAGE_WRITEONLY,	FVF_VERTEX2D,D3DPOOL_MANAGED,&g_pVertexBuffer,NULL);	//���_���
	
	g_pDevice->CreateIndexBuffer(DEBUG_CIRCLE_VERTEX * 2 * DEBUG_CIRCLE_MAX * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
#endif
}

void Debug_Uninit()	//�I�������@(�e�ϐ��̊J��)
{
#if defined(_DEBUG) || defined(DEBUG)
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;

	}
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
#endif
}

void Debug_Begin()	//���t���[��������
{
#if defined(_DEBUG) || defined(DEBUG)
	g_CircleCount = 0;	//�`�������~�̐������Z�b�g����
#endif
}

void Debug_End()	//End�����Ǖ`�悵�Ă���B
{
#if defined(_DEBUG) || defined(DEBUG)


	Debug_Circle* pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);

	for (int i = 0; i < g_CircleCount; i++)	//�`�悷��~�̐�
	{
		int  startIndex = i * DEBUG_CIRCLE_VERTEX;	//�J�n����C���f�b�N�X�ԍ������߂�

		for (int j = 0; j < DEBUG_CIRCLE_VERTEX; j++)	//�~��`�悷��
		{
			pv[startIndex+j].position.x = cos(RadiusNum*j)*g_Circles[i].radius+g_Circles[i].position.x;
			pv[startIndex+j].position.y = sin(RadiusNum*j)*g_Circles[i].radius+g_Circles[i].position.y;
			pv[startIndex+j].position.z = 0.0f;
			pv[startIndex+j].position.w = 1.0f;
			pv[startIndex+j].color = g_Colors[i];
		}
	}


	g_pVertexBuffer->Unlock();





	WORD* pI;
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, D3DLOCK_DISCARD);

	for (int i = 0; i < g_CircleCount; i++)			//�`�悷��~�̐������C���f�b�N�X�̌v�Z
	{
		int StartIndex = DEBUG_CIRCLE_VERTEX*2*i;

		for (int j = 0; j < DEBUG_CIRCLE_VERTEX; j++)
		{
		
			pI[StartIndex + j * 2 + 0] = i * DEBUG_CIRCLE_VERTEX + j;
			pI[StartIndex + j * 2 + 1] = i * DEBUG_CIRCLE_VERTEX + ((j + 1) % DEBUG_CIRCLE_VERTEX);
		}
	}

	g_pIndexBuffer->Unlock();



	///////////////////////////////////////////////////////////////////////////////////////////////�`��
	g_pDevice -> SetFVF(FVF_DEBUG_CIRCLE_VERTEX);
	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(FVF_DEBUG_CIRCLE_VERTEX));
	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetTexture(0, NULL);


	g_pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, g_CircleCount*DEBUG_CIRCLE_VERTEX, 0, DEBUG_CIRCLE_VERTEX*g_CircleCount);


#endif
}

void Debug_DrawCircle(float x, float y, float radius)	//�`�悷��~�̃����o����ݒ�
{
#if defined(_DEBUG) || defined(DEBUG)
	g_Colors[g_CircleCount] = g_Color;

	g_Circles[g_CircleCount].position.x = x;
	g_Circles[g_CircleCount].position.y = y;
	g_Circles[g_CircleCount].radius = radius;

	g_CircleCount++;	//�������


#endif

}

void Debug_SetColor(D3DCOLOR color)
{
#if defined(_DEBUG) || defined(DEBUG)
	g_Color = color;
#endif
}
