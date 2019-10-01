//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <Windows.h>

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum	//�y�Ȃ�ǉ�����ꍇ�����ɒǉ�����	�Đ��ł���y�Ȃ�wav�t�@�C������
{
	SOUND_LABEL_BGM000=0 ,		// BGM0
	SOUD_LABEL_BGM001 ,	//���X�{�XBGM
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_LASTSHOT,	//���X�{�X�e�� Energy
	SOUND_LABEL_SE_LASTSHOT1,	//���X�{�X�e�� Twin
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_DAMAGE,	//Damage��
	SOUND_LABEL_SE_HEAL02,	//�񕜉�
	SOUND_LABEL_SE_WARNING,	//�x����
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
