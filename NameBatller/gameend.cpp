
#define CONIOEX
#include "conioex.h"

#define NEND 0		//exit関数：正常終了
#define  ABEND 1	//exit関数：異常終了

extern int mmf;
extern int bmf1;
extern int bmf2;

int gameend(int notsaved)	//プログラムの終了
{
	int select;

	for (;;)	//
	{
		system("cls");

		if (notsaved == 1)	//セーブ未実施の場合警告文を出力
		{
			gotoxy(20, 14);
			textcolor(LIGHTRED);	//赤字で強調
			printf("注意：データが保存されていません！");
			textcolor(WHITE);
		}

		gotoxy(25, 15);
		printf("ゲームを終了しますか？");	//終了確認
		gotoxy(29, 17);
		printf("Yes: 1   No:0\n");

		select = getch();

		if (select == '1')
		{
			closesound(mmf);	//終了時に音楽ファイルを閉じる
			closesound(bmf1);
			closesound(bmf2);
			exit(NEND);
		}
		else if (select == '0')	//0を入力した場合メニューへ戻る
		{
			return notsaved;
		}
	}
}