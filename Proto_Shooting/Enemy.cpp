#include "common.h"
#include "Enemy.h"
#include "MyTex.h"
#include "Sprite.h"
#include "collision.h"
#include "Debug.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "Explosion.h"
#include "common.h"
#include "EnemyGenerate.h"
#include "PatternAnimation.h"
#include "Item.h"
#include "sound.h"
#include "Effect.h"

static unsigned int Flier1_Tex;	//�e�N�X�`���ϐ�
static unsigned int Flier2_Tex;
static unsigned int Dragon_Tex;
static unsigned  int LastEnemy_Pattern_Tex;
static int Enemy_WaitCount;
static bool WaitCountBool;


Enemy flier1[ENEMY_MAX];	//�\���̐錾
Enemy2 flier2[ENEMY_MAX];
Dragon dragon[ENEMY_MAX];
Last_Enemy LastEnemy;


void Enemy_Init()
{
	Flier1_Tex = Texture_SetLoadFile("Asset\\Enemy1.png", 194, 239);
	Flier2_Tex = Texture_SetLoadFile("Asset\\Enemy2.png", 112, 130);
	Dragon_Tex = Texture_SetLoadFile("Asset\\Dragon.png", 180, 232);
	LastEnemy_Pattern_Tex = Texture_SetLoadFile("Asset\\LastEnemy_Pattern.png",510, 520);

	for (int i = 0; i < ENEMY_MAX; i++)	//�G��ԏ�����
	{
		flier1[i].HP = 100;
		flier1[i].EnemyCircle.radius = 50;//�����蔻��̔��a
		flier1[i].EnemyCircle.position.x = 10000;
		flier1[i].EnemyCircle.position.y = 10000;
		flier1[i].EnemyExist = false;

		flier2[i].EnemyCircle.radius = 28;
		flier2[i].EnemyCircle.position.x = 10000;
		flier2[i].EnemyCircle.position.y = 10000;
		flier2[i].EnemyExist = false;

		dragon[i].EnemyCircle.radius = 50;
		dragon[i].EnemyCircle.position.x = 10000;
		dragon[i].EnemyCircle.position.y = 10000;
		dragon[i].EnemyExist = false;

	}


	//���X�{�X���菉�����E��Ԃ�������
	LastEnemy.EnemyExist = false;

	LastEnemy.LeftWing.PartsExist = false;
	LastEnemy.Right_Wing.PartsExist = false;
	LastEnemy.Center.PartsExist = false;
	
	LastEnemy.LeftWing.Parts_Circle.radius = 50;
	LastEnemy.Right_Wing.Parts_Circle.radius = 50;
	LastEnemy.Center.Parts_Circle.radius = 50;

	LastEnemy.LastEnemy_Bullet_FrameCount = 0;

	Enemy_WaitCount = 0;
	WaitCountBool = false;
}


void Enemy_Update()
{
	for (int i = 0; i < ENEMY_MAX; i++)	//Enemy1�̍X�V����
	{
		if (!flier1[i].EnemyExist)
		{
			flier1[i].EnemyCircle.position.x = 10000;
			flier1[i].EnemyCircle.position.y = 10000;
			continue;	//�������̏����͂����ɉ������Ȃ�
		}
		
		//�G�̍��W�X�V
		flier1[i].g_EnemyPosition.x -= ENEMY_SPEED-2;
		flier1[i].EnemyCircle.position = flier1[i].g_EnemyPosition;	//�����蔻��v���~�̍��W���X�V
		flier1[i].EnemyCircle.position.x += 100;//����
		flier1[i].EnemyCircle.position.y += 45;//����
		if (flier1[i].g_EnemyPosition.x <= -180)	//�G�̈ړ�����
		{
			flier1[i].EnemyExist=false;
		}
		if (flier1[i].HP <= 0)
		{
			Flier1_Destroy(i);
		}

		Effect_Create(flier1[i].g_EnemyPosition.x+40, flier1[i].g_EnemyPosition.y+55, D3DCOLOR_RGBA(255, 255, 0, 255), 10, EFFECT_BURNER);

	}


	for (int i = 0; i < ENEMY_MAX; i++)	//Enemy2�̍X�V����
	{
		if (!flier2[i].EnemyExist)
		{
			flier2[i].EnemyCircle.position.x = 10000;
			flier2[i].EnemyCircle.position.y = 10000;
			continue;
		}

		flier2[i].enemy2_angle += 0.1f;

		//�G�̍��W�X�V
		flier2[i].g_EnemyPosition.x -= ENEMY_SPEED;
		flier2[i].g_Enemy_Rotate_Center.x -= ENEMY_SPEED;
		flier2[i].g_EnemyPosition.y = sin(flier2[i].enemy2_angle)*flier2[i].move_radius+flier2[i].g_Enemy_Rotate_Center.y;
		flier2[i].EnemyCircle.position = flier2[i].g_EnemyPosition;	//�����蔻��v���~�̍��W���X�V
		flier2[i].EnemyCircle.position.x +=50;//����
		flier2[i].EnemyCircle.position.y += 40;//����

		Effect_Create(flier2[i].g_EnemyPosition.x + 10, flier2[i].g_EnemyPosition.y + 28, D3DCOLOR_RGBA(255, 0, 0, 255), 20, EFFECT_BURNER);

		if (flier2[i].g_EnemyPosition.x <= -180)	//�G�̈ړ�����
		{
			flier2[i].EnemyExist = false;
		}
	}

	for (int i = 0; i < ENEMY_MAX; i++)	//Enemy3�̍X�V����
	{

		
			if (dragon[i].HP <= 0&&dragon[i].EnemyExist)	//�̗͂��Ȃ��Ȃ����ꍇ�֐��ŏ���
			{
				Dragon_Destroy(i);
			}
		
			if (Get_EnemyGenerateFrameCount() < 2400)	//���X�{�X������܂Ő퓬
			{
				if (!dragon[i].EnemyExist)
				{
					dragon[i].EnemyCircle.position.x = 10000;
					dragon[i].EnemyCircle.position.x = 10000;
					continue;	//���������̏����͍s��Ȃ��B
				}

				dragon[i].enemy2_angle += 0.05;

				//�G�̍��W�X�V
				if (dragon[i].g_EnemyPosition.x >= 500)
				{
					dragon[i].g_EnemyPosition.x -= ENEMY_SPEED;
					dragon[i].g_Enemy_Rotate_Center.x -= ENEMY_SPEED - 2;
				}

				dragon[i].g_EnemyPosition.y = sin(dragon[i].enemy2_angle)*dragon[i].move_radius + dragon[i].g_Enemy_Rotate_Center.y;	//�㉺�ړ�
				dragon[i].EnemyCircle.position = dragon[i].g_EnemyPosition;	//������W�X�V
				dragon[i].EnemyCircle.position.x += 100;	//������W����
				dragon[i].EnemyCircle.position.y += 50;	//������W����

			

				if (dragon[i].Bullet_FrameCount % 30 == 0)
				{
					Dragon_Bullet_Create(dragon[i].g_EnemyPosition);	//�e�۔���
				}
			
			}
			else				//���X�{�X�o�����̃h���S���̑ޔ�
			{						
				dragon[i].g_EnemyPosition.x += 2;
				if (dragon[i].g_EnemyPosition.x > 2000)
				{
					dragon[i].EnemyExist = false;
				}
			}

		if (dragon[i].g_EnemyPosition.x <= -180)	//�G�̈ړ�����
		{
			dragon[i].EnemyExist = false;
		}


		dragon[i].Bullet_FrameCount++;

	}





	if (LastEnemy.EnemyExist)	//���X�{�X�̍X�V����
	{
		if (LastEnemy.LeftWing.PartsExist || LastEnemy.Right_Wing.PartsExist || LastEnemy.Center.PartsExist)
		{
			LastEnemy.LastEnemy_Bullet_FrameCount++;


			if (LastEnemy.LastEnemy_position.x > 380)	//����x���W��y���W�X�V(�㉺�^��)
			{
				LastEnemy.LastEnemy_position.x -= ENEMY_SPEED - 5;
				LastEnemy.LastEnemy_Rotate_Center.x -= ENEMY_SPEED - 7;
			}
			else
			{
				LastEnemy.LastEnemy_position.y = sin(LastEnemy.LastEnemy_angle)*LastEnemy.LastEnemyMove_radius + LastEnemy.LastEnemy_Rotate_Center.y;
				LastEnemy.LastEnemy_angle += 0.02;
			}

			//���X�{�X�@�����蔻����W����
			//�E��
			LastEnemy.Right_Wing.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 120;
			LastEnemy.Right_Wing.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 50;
			//�{��
			LastEnemy.Center.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 150;
			LastEnemy.Center.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 130;
			//����
			LastEnemy.LeftWing.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 150;
			LastEnemy.LeftWing.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 240;


			//��������
			if (LastEnemy.LeftWing.HP <= 0)
			{
				if (LastEnemy.LeftWing.PartsExist)
				{
					EnergyCupsule_Create(LastEnemy.LeftWing.Parts_Circle.position);	//�񕜃A�C�e������
				}
				LastEnemy.LeftWing.PartsExist = false;	//��������
			}
			if (LastEnemy.Right_Wing.HP <= 0)
			{
				if (LastEnemy.Right_Wing.PartsExist)
				{
					EnergyCupsule_Create(LastEnemy.Right_Wing.Parts_Circle.position);	//�񕜃A�C�e������
				}
				LastEnemy.Right_Wing.PartsExist = false;	//�E������
			}
			if (LastEnemy.Center.HP <= 0)
			{
				if (LastEnemy.Center.PartsExist)
				{
					EnergyCupsule_Create(LastEnemy.Center.Parts_Circle.position);	//�񕜃A�C�e������
				}
				LastEnemy.Center.PartsExist = false;	//�Z���^�[������
			}

			if (LastEnemy.LastEnemy_Bullet_FrameCount % 90 == 0)	//�e�ۂ̐���
			{
				TwinBullet_Create(LastEnemy.LastEnemy_position);
			}

			if (LastEnemy.LastEnemy_Bullet_FrameCount % 180 == 0)	//�e�ۂ̐���
			{
				EnergyBullet_Create(LastEnemy.LastEnemy_position);
			}
			if (LastEnemy.LastEnemy_Bullet_FrameCount % 150==0)	//�e�ۂ̐���
			{
				Dragon_Bullet_Create(LastEnemy.LastEnemy_position);
			}

		}
		else if (!LastEnemy.LeftWing.PartsExist && !LastEnemy.Right_Wing.PartsExist && !LastEnemy.Center.PartsExist)	//�S�������o
		{
			LastEnemy.LastEnemy_position.x++;	//��ނ���������
			LastEnemy.LastEnemy_position.y += 2;

			if (LastEnemy.LastEnemy_position.y+100 >= 400)	//�������ď���
			{
				Explosion_Create(LastEnemy.LastEnemy_position.x+100, LastEnemy.LastEnemy_position.y+100);
				Explosion_Create(LastEnemy.LastEnemy_position.x+200, LastEnemy.LastEnemy_position.y+100);
				Explosion_Create(LastEnemy.LastEnemy_position.x+150, LastEnemy.LastEnemy_position.y+100);
				Explosion_Create(LastEnemy.LastEnemy_position.x+130, LastEnemy.LastEnemy_position.y+100);
				Explosion_Create(LastEnemy.LastEnemy_position.x+180, LastEnemy.LastEnemy_position.y+100);
				LastEnemy.EnemyExist = false;
				WaitCountBool=true;
			}

		}

	}

	if (WaitCountBool)
	{
		Enemy_WaitCount++;
	}

	if (Enemy_WaitCount > 60)
	{
		SetSecene(2);
	}

}

void Enemy_Draw()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (flier1[i].EnemyExist)	//Flire1�`��
		{
			Sprite_Draw(Flier1_Tex, flier1[i].g_EnemyPosition.x, flier1[i].g_EnemyPosition.y, 0, 0, 194, 239, 0, 0, 0, 1);
			Debug_DrawCircle(flier1[i].EnemyCircle.position.x, flier1[i].EnemyCircle.position.y, flier1[i].EnemyCircle.radius);
		}
	
		if (flier2[i].EnemyExist)	//Flier2�`��
		{
			Sprite_Draw(Flier2_Tex, flier2[i].g_EnemyPosition.x, flier2[i].g_EnemyPosition.y, 0, 0, 112, 130, 0, 0, 0, 1);
			Debug_DrawCircle(flier2[i].EnemyCircle.position.x, flier2[i].EnemyCircle.position.y, flier2[i].EnemyCircle.radius);
		}
		if (dragon[i].EnemyExist)	//Dragon�`��
		{
			Sprite_Draw(Dragon_Tex, dragon[i].g_EnemyPosition.x, dragon[i].g_EnemyPosition.y, 0, 0, 180, 232, 0, 0, 0, 1);
			Debug_DrawCircle(dragon[i].EnemyCircle.position.x, dragon[i].EnemyCircle.position.y, dragon[i].EnemyCircle.radius);
		}
	}

	if (LastEnemy.EnemyExist)	//���X�{�X�`��
	{
		if (!LastEnemy.LeftWing.PartsExist|| !LastEnemy.Right_Wing.PartsExist|| !LastEnemy.Center.PartsExist)//��������
		{
			if (!LastEnemy.LeftWing.PartsExist&&LastEnemy.Right_Wing.PartsExist&&LastEnemy.Center.PartsExist)	//�����̂ݑ���
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 0, 352, 161, 166, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.Right_Wing.Parts_Circle.position.x, LastEnemy.Right_Wing.Parts_Circle.position.y, LastEnemy.Right_Wing.Parts_Circle.radius);
				Debug_DrawCircle(LastEnemy.Center.Parts_Circle.position.x, LastEnemy.Center.Parts_Circle.position.y, LastEnemy.Center.Parts_Circle.radius);

			}
			if (LastEnemy.LeftWing.PartsExist && !LastEnemy.Right_Wing.PartsExist&&LastEnemy.Center.PartsExist)	//�E���̂ݑ���
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 0, 184, 161, 166, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.LeftWing.Parts_Circle.position.x, LastEnemy.LeftWing.Parts_Circle.position.y, LastEnemy.LeftWing.Parts_Circle.radius);
				Debug_DrawCircle(LastEnemy.Center.Parts_Circle.position.x, LastEnemy.Center.Parts_Circle.position.y, LastEnemy.Center.Parts_Circle.radius);
			}
			if (!LastEnemy.Center.PartsExist&&LastEnemy.LeftWing.PartsExist&&LastEnemy.Right_Wing.PartsExist)	//�{�̂̂ݑ���
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 320, 0, 161, 182, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.Right_Wing.Parts_Circle.position.x, LastEnemy.Right_Wing.Parts_Circle.position.y, LastEnemy.Right_Wing.Parts_Circle.radius);
				Debug_DrawCircle(LastEnemy.LeftWing.Parts_Circle.position.x, LastEnemy.LeftWing.Parts_Circle.position.y, LastEnemy.LeftWing.Parts_Circle.radius);
			}
			if (!LastEnemy.LeftWing.PartsExist&&!LastEnemy.Center.PartsExist&&LastEnemy.Right_Wing.PartsExist)	//�����E�{�̑���
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 343, 354, 161, 166, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.Right_Wing.Parts_Circle.position.x, LastEnemy.Right_Wing.Parts_Circle.position.y, LastEnemy.Right_Wing.Parts_Circle.radius);
			}
			if (!LastEnemy.LeftWing.PartsExist && !LastEnemy.Right_Wing.PartsExist&&LastEnemy.Center.PartsExist)	//�����E�E������
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 343, 185, 153, 159, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.Center.Parts_Circle.position.x, LastEnemy.Center.Parts_Circle.position.y, LastEnemy.Center.Parts_Circle.radius);
			}
			if (!LastEnemy.Center.PartsExist && !LastEnemy.Right_Wing.PartsExist&&LastEnemy.LeftWing.PartsExist)	//�E���E�{�̑���
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 161, 184, 161, 166, 0, 0, 0, 1);
				Debug_DrawCircle(LastEnemy.LeftWing.Parts_Circle.position.x, LastEnemy.LeftWing.Parts_Circle.position.y, LastEnemy.LeftWing.Parts_Circle.radius);
			}
			if (!LastEnemy.LeftWing.PartsExist && !LastEnemy.Right_Wing.PartsExist && !LastEnemy.Center.PartsExist)	//�S��
			{
				Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 162, 0, 161, 166, 0, 0, 0, 1);
			}
		}
		else
		{
			Sprite_Draw(LastEnemy_Pattern_Tex, LastEnemy.LastEnemy_position.x, LastEnemy.LastEnemy_position.y, 0, 0, 161, 182, 0, 0, 0, 1);	//�������(�����Ȃ�)
			Debug_DrawCircle(LastEnemy.Right_Wing.Parts_Circle.position.x, LastEnemy.Right_Wing.Parts_Circle.position.y, LastEnemy.Right_Wing.Parts_Circle.radius);
			Debug_DrawCircle(LastEnemy.LeftWing.Parts_Circle.position.x, LastEnemy.LeftWing.Parts_Circle.position.y, LastEnemy.LeftWing.Parts_Circle.radius);
			Debug_DrawCircle(LastEnemy.Center.Parts_Circle.position.x, LastEnemy.Center.Parts_Circle.position.y, LastEnemy.Center.Parts_Circle.radius);
		}

		if (Get_EnemyBulletEffectExist())//���X�{�X�ɂ��ꕔ�e�ې������Ăѓ���Ƃ��ăG�t�F�N�g������
		{
			PatternAnimation_Effect(LastEnemy.LastEnemy_position.x-30 , LastEnemy.LastEnemy_position.y + 66, GetFrame());
			PatternAnimation_Effect(LastEnemy.LastEnemy_position.x-30 , LastEnemy.LastEnemy_position.y + 153, GetFrame());
		}

	}

}

void Enemy_Uninit()
{


}



void Flier1_Create(float x, float y)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (flier1[i].EnemyExist)
		{
			continue;
		}




		//���݂��Ȃ��G�̐������J�n����B

		flier1[i].EnemyExist = true;
		flier1[i].HP = 100;
		flier1[i].g_EnemyPosition.x = x;
		flier1[i].g_EnemyPosition.y = y;

		flier1[i].EnemyCircle.position.x = x + 130;
		flier1[i].EnemyCircle.position.y = y + 116;
		break;
	}
}

void Flier2_Create(float x, float y)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (flier2[i].EnemyExist)
		{
			continue;
		}




		//���݂��Ȃ��G�̐������J�n����B

		flier2[i].EnemyExist = true;

		flier2[i].enemy2_angle = 0;

		flier2[i].g_EnemyPosition.x = x;
		flier2[i].g_EnemyPosition.y = y;

		flier2[i].g_Enemy_Rotate_Center.x = x - 20.0f;
		flier2[i].g_Enemy_Rotate_Center.y = y;

		flier2[i].EnemyCircle.position.x = x + 130;
		flier2[i].EnemyCircle.position.y = y + 116;
		break;
	}
}

void Dragon_Create(float x, float y,int index)
{
	
		if (dragon[index].EnemyExist)
		{
			return;
		}

		//���݂��Ȃ��G�𐶐�����

		dragon[index].EnemyExist = true;
		dragon[index].HP = 100;
		dragon[index].enemy2_angle = 0;
		dragon[index].g_EnemyPosition.x = x;
		dragon[index].g_EnemyPosition.y = y;
		dragon[index].g_Enemy_Rotate_Center.x = x - 20.0f;
		dragon[index].g_Enemy_Rotate_Center.y = y;
		dragon[index].EnemyCircle.position.x = x + 130;
		dragon[index].EnemyCircle.position.y = y + 116;

		

	

}

void LastEnemy_Create()
{
	if (!LastEnemy.EnemyExist)
	{
		LastEnemy.EnemyExist = true;	//��ԁF�^

		LastEnemy.LeftWing.PartsExist = true;	//������ԁF����
		LastEnemy.Right_Wing.PartsExist = true;	//�E����ԁF����
		LastEnemy.Center.PartsExist = true;		//�{�̏�ԁF����
		
		LastEnemy.LeftWing.HP = 200;	//�����ϋv�͐ݒ�	
		LastEnemy.Right_Wing.HP = 200;	//�E���ϋv�͐ݒ�
		LastEnemy.Center.HP = 250;		//�{�̑ϋv�͐ݒ�


		LastEnemy.LastEnemy_position.x = 800;	//���X�{�X���W�ݒ�
		LastEnemy.LastEnemy_position.y = 70;		//���X�{�X���W�ݒ�

		LastEnemy.LastEnemy_Rotate_Center.y = LastEnemy.LastEnemy_position.y;

		LastEnemy.LeftWing.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 150;	//���������蔻����W
		LastEnemy.LeftWing.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 50;

		LastEnemy.Center.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 120;	//�E�������蔻����W
		LastEnemy.Center.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 150;

		LastEnemy.Right_Wing.Parts_Circle.position.x = LastEnemy.LastEnemy_position.x + 150;	//�{�̓����蔻����W
		LastEnemy.Center.Parts_Circle.position.y = LastEnemy.LastEnemy_position.y + 250;

		LastEnemy.LastEnemy_angle = 0;	//�ړ��l������
		//�e�p�[�c�̏������W�ݒ�
		//�e�p�[�c�̉�]���A�p�x�A���a��������

	}
}


bool Flier1_Exist(int index)//���݂��邩�ǂ���
{
	return flier1[index].EnemyExist;
}

bool Flier2_Exist(int index)//���݂��邩�ǂ���
{
	return  flier2[index].EnemyExist;
}

bool Dragon_Exist(int index)//���݂��邩�ǂ���
{
	return dragon[index].EnemyExist;
}

bool LastEnemy_Parts_Exist(int index)//���݂��邩�ǂ���
{
	switch (index)
	{
	case 0:
		return LastEnemy.LeftWing.PartsExist;
		break;

	case 1:
		return LastEnemy.Right_Wing.PartsExist;
		break;

	case 2:
		return LastEnemy.Center.PartsExist;
		break;
	
	}

}

bool LastEnemy_Exist()//���݂��邩�ǂ���
{
	return LastEnemy.EnemyExist;
}

void Flier1_Destroy(int index)//���ŏ���
{
	flier1[index].EnemyExist = false;
	flier1[index].EnemyCircle.position.x = 10000;
	flier1[index].EnemyCircle.position.y = 10000;
}

void Flier2_Destroy(int index)//���ŏ���
{
	flier2[index].EnemyExist = false;
	flier2[index].EnemyCircle.position.x = 10000;
	flier2[index].EnemyCircle.position.y = 10000;
	PlaySound(SOUND_LABEL_SE_DAMAGE);
}

void Dragon_Destroy(int index)//���ŏ���
{
	srand(timeGetTime());
	int Item_Create=rand()%10;

	if (Item_Create<=4)
	{
		EnergyCupsule_Create(dragon[index].g_EnemyPosition);	//40���̊m���ŉ񕜃A�C�e������
	}

	dragon[index].EnemyExist = false;
	dragon[index].EnemyCircle.position.x = 10000;
	dragon[index].EnemyCircle.position.y = 10000;
}

void Last_Enemy_Parts_Destroy(int index)	//���X�{�X�p�[�c�̔j��
{
	switch (index)
	{
	case 0:
		LastEnemy.LeftWing.PartsExist = false;
		break;
	
	case 1:
		LastEnemy.Right_Wing.PartsExist = false;
		break;

	case 2:
		LastEnemy.Center.PartsExist = false;
		break;
	
	
	
	}

	
}


const Circle* Flier1_GetCollision(int index)	//�����蔻��
{
	return &flier1[index].EnemyCircle;
}
const Circle* Flier2_GetCollision(int index)//�����蔻��
{
	return &flier2[index].EnemyCircle;
}

const Circle* Dragon_GetCollision(int index)//�����蔻��
{
	return &dragon[index].EnemyCircle;
}

const Circle* LastEnemy_Parts_Collision(int index)//�����蔻��
{


	switch (index)
	{
	case 0:
		return &LastEnemy.LeftWing.Parts_Circle;
		break;
	
	case 1:
		return &LastEnemy.Right_Wing.Parts_Circle;
		break;

	case 2:
		return &LastEnemy.Center.Parts_Circle;
		break;

	}

}

int Flier1_DMG(int index)//�G�_���[�W
{
	flier1[index].HP -= 50;

	PlaySound(SOUND_LABEL_SE_DAMAGE);

	if (flier1[index].HP <= 0)
	{
		Flier1_Destroy(index);

		return 20;
	}

	return 0;
}

int Dragon_DMG(int index)//�G�_���[�W
{
	dragon[index].HP -= 15;	//�_���[�W

	PlaySound(SOUND_LABEL_SE_DAMAGE);

	if (dragon[index].HP <= 0)
	{
		return 100;	//�X�R�A�ԋp
	}

	return 0;
}

int LastEnemy_Parts_DMG(int index)//�G�_���[�W
{

	PlaySound(SOUND_LABEL_SE_DAMAGE);

	switch (index)
	{
	case 0:
		LastEnemy.LeftWing.HP -= 10;	//�_���[�W
		if (LastEnemy.LeftWing.HP <= 0)
		{
			return 200;	//�X�R�A���Z
		}
		return 0;
		break;

	case 1:
		LastEnemy.Right_Wing.HP -= 10;//�_���[�W
		if (LastEnemy.Right_Wing.HP <= 0)
		{
			return 200;//�X�R�A���Z
		}
		return 0;
		break;

	case 2:
		LastEnemy.Center.HP -= 10;	//�_���[�W
		if (LastEnemy.Center.HP <= 0)
		{
			return 200;	//�X�R�A���Z
		}
		return 0;
		break;

	
	}




}

D3DXVECTOR2 Get_LastEnemy_Position(void)//���W�擾
{
	return LastEnemy.LastEnemy_position;
}

D3DXVECTOR2 Get_Dragon_Position(int index)//���W�擾
{
	return dragon[index].g_EnemyPosition;
}


