//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <Windows.h>

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum	//楽曲を追加する場合ここに追加する	再生できる楽曲はwavファイルだけ
{
	SOUND_LABEL_BGM000=0 ,		// BGM0
	SOUD_LABEL_BGM001 ,	//ラスボスBGM
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_LASTSHOT,	//ラスボス弾丸 Energy
	SOUND_LABEL_SE_LASTSHOT1,	//ラスボス弾丸 Twin
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_DAMAGE,	//Damage音
	SOUND_LABEL_SE_HEAL02,	//回復音
	SOUND_LABEL_SE_WARNING,	//警告音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
