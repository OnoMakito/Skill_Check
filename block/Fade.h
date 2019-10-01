#pragma once
#include "main.h"

enum FADE_STATE
{
	FADE_STATE_NONE,
	FADE_STATE_IN,
	FADE_STATE_OUT

};



void FadeInit(void);

void FadeUpdate(void);

void FadeDraw(void);

void FadeUninit(void);

void Fade(SCENE x);

FADE_STATE GetFadeState();


