#include "Fade.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"


FADE_STATE g_fade_state;
SCENE Fade_Next_Scene;
float g_FadeAlpha;


void FadeInit()
{
	g_fade_state = FADE_STATE_NONE;

	g_FadeAlpha = 0.0f;

}

void FadeUpdate()
{
	if (g_fade_state == FADE_STATE_OUT)
	{
		if (g_FadeAlpha >= 1.0f)
		{
			g_FadeAlpha = 1.0f;
			g_fade_state = FADE_STATE_IN;
		}
		g_FadeAlpha -= (1.0f / 200.0f);
	}
	else if (g_fade_state == FADE_STATE_IN)
	{
		if (g_FadeAlpha <= 0.0f)
		{
			g_FadeAlpha = 0.0f;
			g_fade_state = FADE_STATE_OUT;
		}
		g_FadeAlpha -= (1.0f / 200.0f);
	}
	
}


void FadeDraw()
{
	if (g_fade_state == FADE_STATE_NONE)
	{
		return;
	}


	SetTexture(0);

	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, MakeFloat4(0.0f, 0.0f, 0.0f, g_FadeAlpha));



}


void FadeUninit()
{


}

void Fade(SCENE NextScene)
{
	Fade_Next_Scene = NextScene;
	g_fade_state = FADE_STATE_OUT;
}


FADE_STATE GetFadeState()
{
	return g_fade_state;
}




























