#pragma once

class Item
{
public:
	float position_x;
	float position_y;

	bool Exist;

};


void Item_Init(void);

void Item_Update(void);

void Item_Draw(void);

void Item_UnInit(void);

