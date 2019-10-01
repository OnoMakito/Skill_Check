
#define CONIOEX

#include "conioex.h"

typedef struct	//status型の作成
{
	char name[35];
	float hp;
	int mp;
	int def;
	int speed;
	char element[6];
	char skill[35];
	int existance;
}status;

extern status character[4];

void check()	//キャラクター詳細情報確認
{
	system("cls");
	printf("\n現在のキャラクター\n\n");

	for (int i = 0; i < 4; i++)
	{
		printf("\n%d番目\n名前：%s\n体力：%.0f         魔力：%d       防御力：%d       速度:%d\n攻撃属性：", i + 1, character[i].name, character[i].hp, character[i].mp, character[i].def, character[i].speed);	//全員のステータス表示

																																															//属性ごとにテキストカラ―を変える	
		if (strcmp(character[i].element, "無") == 0)
		{
			textcolor(LIGHTGRAY);
		}
		if (strcmp(character[i].element, "炎") == 0)
		{
			textcolor(LIGHTRED);
		}
		if (strcmp(character[i].element, "水") == 0)
		{
			textcolor(LIGHTCYAN);
		}
		if (strcmp(character[i].element, "雷") == 0)
		{
			textcolor(YELLOW);
		}
		if (strcmp(character[i].element, "風") == 0)
		{
			textcolor(LIGHTGREEN);
		}
		if (strcmp(character[i].element, "闇") == 0)
		{
			textcolor(LIGHTMAGENTA);
		}
		if (strcmp(character[i].element, "光") == 0)
		{
			textcolor(YELLOW);
		}
		printf("%s", character[i].element);

		textcolor(WHITE);

		printf("       スキル名：");

		if (strcmp(character[i].element, "無") == 0)	//属性ごとにスキル名に使うテキストカラ―を設定
		{
			textcolor(LIGHTGRAY);
		}
		if (strcmp(character[i].element, "炎") == 0)
		{
			textcolor(LIGHTRED);
		}
		if (strcmp(character[i].element, "水") == 0)
		{
			textcolor(LIGHTCYAN);
		}
		if (strcmp(character[i].element, "雷") == 0)
		{
			textcolor(YELLOW);
		}
		if (strcmp(character[i].element, "風") == 0)
		{
			textcolor(LIGHTGREEN);
		}
		if (strcmp(character[i].element, "闇") == 0)
		{
			textcolor(LIGHTMAGENTA);
		}
		if (strcmp(character[i].element, "光") == 0)
		{
			textcolor(YELLOW);
		}

		printf("%s\n", character[i].skill);
		textcolor(WHITE);
		printf("\n---------------------------------------------------------------");
	}
	getch();

	return;
}