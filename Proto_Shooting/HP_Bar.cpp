#include "HP_Bar.h"
#include "Player.h"
#include "MyTex.h"
#include "Sprite.h"



static unsigned int HP_Bar_Tex;	//�e�N�X�`���i�[�ϐ�
static unsigned int HP_Text_Tex;

static int Player_HP;	//HP�i�[�ϐ�
static float Player_HPforDraw;	//�`��p�i�[�ϐ�


void HP_Bar_Init()
{
	HP_Bar_Tex = Texture_SetLoadFile("Asset\\HP_Bar.png", 500, 50);	//�e�N�X�`���̓ǂݍ���
	HP_Text_Tex = Texture_SetLoadFile("Asset\\HP_Text.png", 100, 50);
	Player_HP = Player_HPforDraw=Get_Player_HP();	//�eHP�ϐ���������
}

void HP_Bar_Update()
{

	Player_HP = Get_Player_HP();	//���t���[���@�̗͂��X�V

	if (Player_HP < Player_HPforDraw)
	{
		Player_HPforDraw--;
	}
	else if(Player_HP>Player_HPforDraw)
	{
		Player_HPforDraw++;
	}

	if (Player_HPforDraw <= 0)
	{
		Player_HPforDraw = 0;
	}

}

void HP_Bar_Draw()
{

	Sprite_Draw(HP_Text_Tex, 0, 0, 0, 0, 100, 50, 0, 0, 0, 1);


	if (Player_HP > 75)	//�\��
	{
		Sprite_Draw_HP_Bule(HP_Bar_Tex, 53, 0, 0, 0, (float)500 * (Player_HPforDraw /100), 50, 0, 0, 0, 1, (Player_HPforDraw / 100));
	}
	else if (Player_HP > 50 && Player_HP <= 75)	//�Ε\��
	{
		Sprite_Draw_HP_Green(HP_Bar_Tex, 53, 0, 0, 0, (float)500 * (Player_HPforDraw / 100), 50, 0, 0, 0, 1, (Player_HPforDraw / 100));
	}
	else if (Player_HP > 25 && Player_HP <= 50)	//���F�\��
	{
		Sprite_Draw_HP_Yellow(HP_Bar_Tex, 53, 0, 0, 0, (float)500 * (Player_HPforDraw / 100), 50, 0, 0, 0, 1, (Player_HPforDraw / 100));
	}
	else if (Player_HP <= 25)	//�ԕ\��
	{
		Sprite_Draw_HP_Red(HP_Bar_Tex, 53, 0, 0, 0, (float)500 * (Player_HPforDraw / 100), 50, 0, 0, 0, 1, (Player_HPforDraw / 100));
	}

}

void HP_Bar_UnInit()
{
}



