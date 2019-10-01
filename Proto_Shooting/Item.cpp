#include "Item.h"
#include "MyTex.h"
#include "Sprite.h"
#include "Enemy.h"



Energy_Cupsule energy_cupsule[4];

static unsigned int EnergyCupsule_tex;



void EnergyCupsule_Init()
{
	EnergyCupsule_tex = Texture_SetLoadFile("Asset\\Energy_Cupsule.png", 50, 50);

	for (int i = 0; i < 4; i++)
	{
		energy_cupsule[i].Item_Exist = false;
		energy_cupsule[i].Item_Circle.radius = 30;
	}

}

void EnergyCupsule_Update()
{
	for (int i = 0; i < 4; i++)
	{
		if (energy_cupsule[i].Item_Exist)
		{
			energy_cupsule[i].Item_Position.x-=3;
			energy_cupsule[i].Item_Circle.position.x-=3;


			if (energy_cupsule[i].Item_Position.x <= -50)
			{
				energy_cupsule[i].Item_Exist = false;
			}

		}
	}

}

void EnergyCupsule_Draw()
{

	for (int i = 0; i < 4; i++)
	{
		if(energy_cupsule[i].Item_Exist)
		{
			Sprite_Draw(EnergyCupsule_tex, energy_cupsule[i].Item_Position.x, energy_cupsule[i].Item_Position.y, 0, 0, 50, 50, 0, 0, 0, 1);
		
		}
	}

}

void EnergyCupsule_UnInit()
{
}

void EnergyCupsule_Destroy(int index)
{
	energy_cupsule[index].Item_Exist = false;
}

void EnergyCupsule_Create(D3DXVECTOR2 Dragon_Position)
{
	for (int i = 0; i < 4; i++)
	{
		if (energy_cupsule[i].Item_Exist)
		{
			continue;
		}


		energy_cupsule[i].Item_Exist = true;
		energy_cupsule[i].Item_Position = Dragon_Position;
		energy_cupsule[i].Item_Position.y += 116;
		
		energy_cupsule[i].Item_Circle.position = Dragon_Position;
		energy_cupsule[i].Item_Circle.position.y +=116;

		break;
	}
}

bool EnergyCupsule_GetExist(int index)
{
	return energy_cupsule[index].Item_Exist;
}

const Circle * EnemyCupsule_GetCollision(int index)
{
	return &energy_cupsule[index].Item_Circle;
}
