#include "main.h"
#include "texture.h"
#include "Effect.h"
#include "Block.h"
#include "Sprite.h"
#include "ball.h"


Explosion g_Explosion[EXPLOSION_MAX];

static int g_ExplosionTexuture;
static Float2 g_ExplosionPosition;
static bool hit;
static int blocknumber;
static Float2 blockposition;
static int frame = 0;

static int speed=60;

void ExplosionInit()	//�C�ӂ̃^�C�~���O�ŏ�����
{
	g_ExplosionTexuture = LoadTexture("rom:/explosion.tga");

}

void ExplosionUpdate()	//�����`��
{
	if (hit == false)
	{
		//hit = GetHit();	//true or false
	}
	else
	{
		speed--;	//�Đ������̔ԍ��Ɉڂ�܂ł̃J�E���g������B
	}

	//blocknumber = getnumber();	//�Ō�ɓ��������u���b�N
	blockposition = getblockposition(blocknumber);

	
}

void ExplosionDraw()	//�`��
{
	if (frame > EXPLOSION_MAX)	//�ԍ����S�����𒴂��Ă����珉�������A�`����I��
	{
		frame =0;
		hit = false;
	}

	
	
	if (hit == true)
	{
		if (speed <= 0)	//�J�E���g��0�ȉ��ɂȂ����玟�ɑJ��
		{
			SetTexture(g_ExplosionTexuture);	//�e�N�X�`���ݒ�

			DrawSprite(blockposition.x, blockposition.y, 50.0f, 50.0f,
				frame % 4 * 0.25, frame / 4 * 0.25, 0.25, 0.25,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

			frame++;	//���̔ԍ���
			speed = 60;
		}
	}
}

void ExplosionUninit()	//�I���֐�
{
	UnloadTexture(g_ExplosionTexuture);
}
