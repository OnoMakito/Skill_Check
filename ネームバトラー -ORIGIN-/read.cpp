
#define CONIOEX
#include "conioex.h"


#define NEND 0		//exit関数：正常終了
#define  ABEND 1	//exit関数：異常終了


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

void read()		//ファイルに保存されているデータを読みこむ。
{
	FILE *fp;
	fp = fopen("データファイル.csv", "rb");	//ファイル展開

	if (fp == NULL)
	{
		printf("データの読み込みに失敗しました。\nプログラムを終了します。");
		getch();
		exit(ABEND);
	}

	for (int i = 0; i < 4; i++)	//4回読み込む
	{
		if (fread(&character[i], sizeof(character[i]), 1, fp) <= 0)	//プレイヤーのデータを読み込む
		{
			break;
		}

	}

	fclose(fp);	//ファイルを閉じる

	return;
}