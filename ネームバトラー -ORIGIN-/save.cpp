
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


int save(int notsaved)		//現在の状況をセーブ
{
	FILE *fp;

	fp = fopen("データファイル.csv", "wb");	//ファイル展開

	if (fp == NULL)
	{
		printf("セーブに失敗しました。\nプログラムを終了します。");
		getch();
		exit(ABEND);
	}

	fwrite(character, sizeof(character[0]), 4, fp);		//データ書き込み

	fclose(fp);	//ファイルを閉じる

	printf("セーブが完了しました。");

	getch();

	notsaved = 0;

	return notsaved;
}