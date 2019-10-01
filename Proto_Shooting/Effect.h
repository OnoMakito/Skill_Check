#pragma once


#ifndef EFFECT_H
#define EFFECT_H

#include "collision.h"


#define EFFECT_MAX (5000)

#define EFFECT_BULLET (0)
#define EFFECT_BURNER (1)

typedef struct Effect_tag
{
	D3DXVECTOR2 g_Effect_Position;
	int Life_Frame;	//������܂ł̃t���[��(����)
	int Create_Frame;	//�쐬���̃t���[��
	D3DCOLOR Effect_Color;	//�|���S���̐F
	int Mode;	//�p�r�F��

}Effect;


void Effect_Init(void);	//�e�ۂ̏�����

void Effect_Update(void);	//�e�ۂ̍X�V

void Effect_Draw(void);	//�e�ۂ̕`��

void Effect_Uninit(void);	//�e�ۉ������


void Effect_Create(float x, float y,D3DCOLOR Color,int LifeFrame,int Mode);	//�e�ۂ̐������W�ݒ�



#endif