#include "score.h"
#include "number.h"


static int num;



void Score_Init()
{
	num=0;

}




void Score_Draw(int score, float x, float y, int digit, bool zero, bool left)
{
	for (int i = 0; i < digit; i++)
	{
		num = score % 10;
		Number_Draw(num, (60*digit - 60*i)+x, y);
		score /= 10;
	}

}



