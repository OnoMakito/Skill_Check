
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


int datadelete(int notsaved)
{
	int select = 0;

	for (;;)
	{
		system("cls");

		textcolor(LIGHTRED);
		gotoxy(34, 15);
		printf("注意！");
		gotoxy(20, 16);
		printf("保存されたデータも削除されます！");	//削除警告
		gotoxy(24, 17);
		printf("消えたデータは戻せません");


		textcolor(WHITE);
		gotoxy(26, 19);
		printf("本当に削除しますか？");		//最終確認
		gotoxy(29, 21);
		printf("Yes: 9   No:0\n");

		select = getch();	//ユーザの選択



		if (select == '9')	//１を指定した場合(それ以外は何もしない)
		{
			FILE *fp;

			fp = fopen("データファイル.csv", "wb");

			if (fp == NULL)
			{
				printf("データの削除に失敗しました。\nプログラムを終了します。");
				getch();
				exit(ABEND);
			}

			fwrite(NULL, 0, 1, fp);

			fclose(fp);	//ファイルを閉じる

			for (int i = 0; i < 4; i++)		//各キャラクターステータス初期化
			{
				strcpy(character[i].name, "");
				character[i].hp = 0;
				character[i].mp = 0;
				character[i].def = 0;
				character[i].speed = 0;
				strcpy(character[i].element, "");
				strcpy(character[i].skill, "");
				character[i].existance = 0;

			}

			notsaved = 0;	//すべてのデータを消しセーブの必要がなくなったため、メニューなどで起きるセーブ未実施の警告を解除する

			system("cls");
			printf("データを削除しました。");
			getch();
			return notsaved;
		}
		else if (select == '0')
		{
			return notsaved;
		}

	}


}