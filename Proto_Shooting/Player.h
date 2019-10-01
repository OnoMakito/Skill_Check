#pragma once

#ifndef PLAYER_H
#define PALYER_H

#include "collision.h"

#define PLAYER_INVISIBLE (30)


typedef struct PLAYER_TAG	//�v���C���[�̍\����
{
	int g_Player_HP;

	D3DXVECTOR2 g_PlayerPosition;
	Circle Player_Circle;
	bool g_Player_Exist;
}Player;

void Player_Init(void);	//�������W�E�e�N�X�`���̏���

void Player_Update(void);	//�L�[���͂ňړ��E

void Player_Draw(void);	//�v���C���[�̏�Ԃ��Ď����ĕ`��(�����E���S�E�����Ȃ�)

void Player_Uninit(void);	//�e�N�X�`�����(�V�[���I�����ɊJ������Ȃ�A�����ɏ����K�v�͂Ȃ��B)

bool Player_Exist(void);

void Player_DMG(int DMG);

void Player_Destroy(void);

D3DXVECTOR2 Get_Player_Position(void);

const Circle* Player_GetCollision(void);

int Get_Player_HP(void);

void Player_Result_Udate(void);

#endif
