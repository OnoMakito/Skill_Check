#pragma once

#define EXPLOSION_MAX (16)

struct Explosion
{
	Float2 position;
	int frame;
	bool exist;
};

void ExplosionInit();

void ExplosionUpdate();

void ExplosionDraw();

void ExplosionUninit();
