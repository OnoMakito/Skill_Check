#pragma once

#ifndef COLLISION_H
#define COLLISION_H

#include <d3dx9.h>

typedef struct Circle_tag
{
	D3DXVECTOR2 position;
	float radius;
}Circle;

bool Circle_Collision(const Circle* pA,const Circle* pB);

#endif
