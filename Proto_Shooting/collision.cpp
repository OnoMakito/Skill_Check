#include "collision.h"
#include "Enemy.h"
#include "Bullet.h"

bool Circle_Collision(const Circle* pA, const Circle* pB)
{
	return (pA->radius + pB->radius)*(pA->radius + pB->radius)
			>
		D3DXVec2LengthSq(&(pA->position - pB->position));	//�x�N�g���̒������v��(�������v��)
	//Sq:�����Ӗ�����B



	/*	
		"�݂��̉~�̒��S�̋������݂��̔��a�̍��v"
	�̏ꍇ�A�e�ۂƓG�͓����ɏ��ł���B
	
	*/
}








