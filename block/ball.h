#pragma once

typedef struct
{
	 Float2 g_ballposition;
	 Float2 g_playerposition;
	 Float2 blockposition;

	bool Exist;

	bool horizon = false;	//false:左 ture:右
	bool vertical = false;	//false：上　true：下
	bool blockhit = false; //false:上　true:下
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