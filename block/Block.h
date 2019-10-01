#pragma once

void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();

typedef struct block_tag
{
	Float2 BlockPosition;
	bool BlockExist = true;

}Block;

bool GetBlockExist(int i);

Float2 getblockposition(int i);


float GetBlock_Position_x(int index);
float GetBlock_Position_y(int index);