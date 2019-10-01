#include "collision.h"
#include "Enemy.h"
#include "Bullet.h"

bool Circle_Collision(const Circle* pA, const Circle* pB)
{
	return (pA->radius + pB->radius)*(pA->radius + pB->radius)
			>
		D3DXVec2LengthSq(&(pA->position - pB->position));	//ベクトルの長さを計測(距離を計測)
	//Sq:二乗を意味する。



	/*	
		"互いの円の中心の距離＜互いの半径の合計"
	の場合、弾丸と敵は同時に消滅する。
	
	*/
}








