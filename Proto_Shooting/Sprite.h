#pragma once

#ifndef SPRITE_H

#define SPRITE_H

#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//XYZ��RHW�������_�f�[�^��\���B	RHW:���_���W�ύX�������������

#include <d3d9.h>
#include <d3dx9.h>

typedef struct vertex2d_tag		//�^�O�����邱�Ƃ��ł���B(�C��)
{
	D3DXVECTOR4 position;	//���_���W
	D3DCOLOR color;			//�F���
	D3DXVECTOR2 uv;			//�摜��UV���W


}vertex1;


void Sprite_Init();	

void Sprite_Draw(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom);	//�g��A�k���B
void Sprite_Draw_Alpha(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom,int alpha);	//�g��A�k���B

//id:�e�N�X�`����Id�@ d:��ʍ��W �@cut:�؂���UV���W�@c:��]�̒��S���W

void Sprite_SetColor(D3DCOLOR Color);

void Sprite_Uninit();

void Sprite_Draw_HP_Bule(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom,float HP);	//HP�o�[�i�j
void Sprite_Draw_HP_Green(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom,float HP);	//HP�o�[�i�j
void Sprite_Draw_HP_Yellow(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom,float HP);	//HP�o�[�i�j
void Sprite_Draw_HP_Red(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom, float HP);	//HP�o�[�i�j



void Sprite_Draw_Mirror(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h);	//���]������B

void Sprite_Draw_Effect(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom);	//�g��A�k���B

#endif
