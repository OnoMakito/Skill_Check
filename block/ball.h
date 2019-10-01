#pragma once

typedef struct
{
	 Float2 g_ballposition;
	 Float2 g_playerposition;
	 Float2 blockposition;

	bool Exist;

	bool horizon = false;	//false:�� ture:�E
	bool vertical = false;	//false�F��@true�F��
	bool blockhit = false; //false:��@true:��
	bool hit = false;
	int number;
}BALL;


void InitBall();
void UninitBall();
void UpdateBall();
void DrawBall();

bool GetHit(int index);

int getnumber(int index);

void Ball_Create();

bool GetBall_Exist(int index);