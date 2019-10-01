#include "number.h"
#include "MyTex.h"
#include "Sprite.h"



unsigned int g_tex_number;



void Number_Init()
{
	g_tex_number = Texture_SetLoadFile("Asset\\number.tga", 220, 44);
}



void Number_Draw(int number, float x, float y)
{
	if (number < 0 || number>9)	//-1�ȉ��A�P�O�ȏ�̒l�͕`��s�B(�ꌅ���Ɨ����ĕ`�悷��B)
	{
		return;
	}
		Sprite_Draw(g_tex_number, x, y, number*22, 0.0f, 22, 44, 0.0f, 0.0f, 0.0f, 1.0f);
	
}