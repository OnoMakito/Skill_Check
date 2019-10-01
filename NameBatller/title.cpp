
#define CONIOEX
#define  ABEND 1	//exit関数：異常終了

#include "conioex.h"

extern int mmf;

void title()
{


	//サウンドに関する注意喚起及びライセンス表示
	textcolor(LIGHTRED);
	gotoxy(28, 18);
	printf("注意：音が出ます！");
	gotoxy(28, 20);
	printf("-Please  Anykey-");
	textcolor(WHITE);
	gotoxy(9, 36);
	printf("フリー配布楽曲使用");
	gotoxy(9, 37);
	printf("作曲者：　Mr.Kimy　MAKOOTO　カワサキヤスヒロ");
	gotoxy(9, 38);
	printf("配布サイト：Dova-Symdorome");

	getch();



	//////タイトルアニメーション開始
	system("cls");
	gotoxy(24, 1);
	printf("ネ　ー　ム　バ　ト　ラ　ー");
	Sleep(80);
	system("cls");
	gotoxy(24, 2);
	printf("ネ　ー　ム　バ　ト　ラ　ー");
	Sleep(80);
	for (int i = 0; i <= 11; i++)
	{
		gotoxy(1, 1);

		insline();
		Sleep(80);
	}


	system("cls");

	Sleep(250);

	srand(timeGetTime());

	for (int i = 0; i <= 1000; i++)	//二進数の背景を展開(すべて出力するのにラグがあるが、それもアニメーションとして扱う。)
	{
		int x = rand() % 100;
		for (x; x >= 71;)
		{
			x = rand() % 100;
		}

		int y = rand() % 100;
		for (y; y >= 41;)
		{
			y = rand() % 100;
		}

		switch (x % 10)
		{
		case 1:
		case 2:
			textcolor(RED);
			break;
		case 3:
		case 4:
			textcolor(BLUE);
			break;
		case 5:
		case 6:
			textcolor(GREEN);
			break;
		case 7:
		case 8:
			textcolor(MAGENTA);
			break;
		case 9:
		case 0:
			textcolor(CYAN);
			break;
		}

		gotoxy(x, y);
		if (rand() % 10 >= 5)
		{
			printf("0");
		}
		else
		{
			printf("1");
		}

		if (i % 100 == 50)
		{
			Sleep(5);
		}
	}


	//グラデーション二進数展開(タイトル上部)
	gotoxy(1, 13);
	textcolor(LIGHTCYAN);
	printf("1110001");
	textcolor(CYAN);
	printf("0001011");
	textcolor(LIGHTBLUE);
	printf("1000111");
	textcolor(MAGENTA);
	printf("0101011");
	textcolor(LIGHTMAGENTA);
	printf("0110010");
	textcolor(LIGHTRED);
	printf("1010110");
	textcolor(YELLOW);
	printf("1001101");
	textcolor(LIGHTGREEN);
	printf("0110011");
	textcolor(GREEN);
	printf("0010101");
	textcolor(DARKGRAY);
	printf("0010100");


	//ゲーム名展開
	textcolor(LIGHTRED);
	gotoxy(5, 14);
	printf("                  __________________________                    "); gotoxy(5, 15);
	printf(" _  _ __＿／／／／   ネ ー ム バ ト ラ ー   ＼＼＼＼＿__ _  _   "); gotoxy(5, 16);
	printf("　        ＼＼＼＼_______Name.Battler_______／／／／            "); gotoxy(5, 17);
	printf("                     ￣￣￣￣￣￣￣￣￣￣                       ");


	//グラデーション二進数展開(タイトル下部)
	gotoxy(1, 18);
	textcolor(DARKGRAY);
	printf("0010100");
	textcolor(GREEN);
	printf("0010101");
	textcolor(LIGHTGREEN);
	printf("0110011");
	textcolor(YELLOW);
	printf("1001101");
	textcolor(LIGHTRED);
	printf("1010110");
	textcolor(LIGHTMAGENTA);
	printf("0110010");
	textcolor(MAGENTA);
	printf("0101011");
	textcolor(LIGHTBLUE);
	printf("1000111");
	textcolor(CYAN);
	printf("0001011");
	textcolor(LIGHTCYAN);
	printf("1110001");


	//制作者名及び所属情報表示
	gotoxy(9, 39);
	printf("制作：ＨＡＬ東京　ＡＴ１１Ｅ―３４１　１３番　小野牧人");



	//タイトルがすべて表示された後、メニュー曲を開始
	playsound(mmf, 1);


	//何らかの入力を受け付け、このゲームの特徴・趣旨を説明
	getch();
	textcolor(LIGHTCYAN);
	gotoxy(23, 23);
	printf("ネームバトラーへようこそ！"); gotoxy(5, 24);
	printf("この世界ではキャラクターの名前を元にパラメータが決定されます！");
	gotoxy(5, 26);
	printf("さっそく、あなただけの最強のキャラクターを見つけ出しましょう！");

	textcolor(WHITE);

	getch();


}