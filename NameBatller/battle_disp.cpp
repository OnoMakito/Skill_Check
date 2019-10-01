
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



int battle_disp(float H1, float H2, int M1, int M2, float D1, float D2, char E1[6], char E2[6], int select1, int select2)		//戦闘用画面
{



	int icon = H1 / character[select1 - '1'].hp * 10;	//一人目の現HPと最大HPを比較した際の割合
	int icon2 = H2 / character[select2 - '1'].hp * 10;//二人目の現HPと最大HPを比較した際の割合

													  ///////////////////////////////////////////////////////////////////////////
													  //一人目表示
	int count = 0;	//HPアイコン計測変数

	system("cls");


	if (H1 < 0)
	{
		H1 = 0;		//体力がマイナスの値にならないようにする。
	}


	printf("＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿\n");
	printf("|　　　　　　　　　　　　　　　　　　　　　　| 体力：%.0f\n", H1);
	printf("|　　　");



	printf("%s", character[select1 - '1'].name);		//名前

	for (int i = 0; i < 38 - strlen(character[select1 - '1'].name); i++)
	{
		printf(" ");			//名前直後の空白
	}

	printf("|　　　　　  魔力：%d\n", M1);	//空白の終わり

	printf("|　　　　　　　　　　　　　　　　　　　　　　| 属性：");

	if (strcmp(E1, "無") == 0 || strcmp(E1, "覚醒") == 0 || strcmp(E1, "OV-C") == 0)
	{
		textcolor(WHITE);
	}
	if (strcmp(E1, "炎") == 0)
	{
		textcolor(LIGHTRED);
	}
	if (strcmp(E1, "水") == 0)
	{
		textcolor(LIGHTCYAN);
	}
	if (strcmp(E1, "雷") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E1, "風") == 0)
	{
		textcolor(LIGHTGREEN);
	}
	if (strcmp(E1, "闇") == 0)
	{
		textcolor(LIGHTMAGENTA);
	}
	if (strcmp(E1, "光") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E1, "壊") == 0)
	{
		textcolor(LIGHTGRAY);
	}

	printf("%s\n", E1);

	textcolor(WHITE);


	printf("|  体力：");


	//textbackground(LIGHTGRAY);
	if (strcmp(E1, "無") == 0|| strcmp(E1, "覚醒") == 0|| strcmp(E1, "OV-C") == 0)
	{
		textcolor(WHITE);
	}
	if (strcmp(E1, "炎") == 0)
	{
		textcolor(LIGHTRED);
	}
	if (strcmp(E1, "水") == 0)
	{
		textcolor(LIGHTCYAN);
	}
	if (strcmp(E1, "雷") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E1, "風") == 0)
	{
		textcolor(LIGHTGREEN);
	}
	if (strcmp(E1, "闇") == 0)
	{
		textcolor(LIGHTMAGENTA);
	}
	if (strcmp(E1, "光") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E1, "壊") == 0)
	{
		textcolor(LIGHTGRAY);
	}

	for (int i = 1; i <= icon; i++)			//hpの最大アイコン表示を10に固定
	{
		printf("◆");
		count += 1;
	}
	textbackground(BLACK);
	textcolor(WHITE);
	for (int i = 1; i <= 18 - count; i++)			//ｈｐ表示直後の空白
	{
		printf("　");
	}




	printf("|　　　　　　防御力：%.0f\n", D1 * 1000);	//空白の終わり



											//空欄2２
	printf("|　　　　　　　　　　　　　　　　　　　　　　|\n");
	printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//二人目表示

	count = 0;	//体力アイコン計測変数の初期化


	if (H2 < 0)
	{
		H2 = 0;		//体力がマイナスの値にならないようにする。
	}

	printf("＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿\n");	//二人目出力開始
	printf("|　　　　　　　　　　　　　　　　　　　　　　| 体力：%.0f\n", H2);
	printf("|　　　");

	printf("%s", character[select2 - '1'].name);		//名前の表示

	for (int i = 0; i < 38 - strlen(character[select2 - '1'].name); i++)
	{
		printf(" ");			//名前直後の空白
	}

	printf("|　　　　　　魔力：%d\n", M2);	//空白の終わり	
	printf("|　　　　　　　　　　　　　　　　　　　　　　| 属性：");

	if (strcmp(E2, "無") == 0 || strcmp(E2, "覚醒") == 0 || strcmp(E2, "OV-C") == 0)
	{
		textcolor(WHITE);
	}
	if (strcmp(E2, "炎") == 0)
	{
		textcolor(LIGHTRED);
	}
	if (strcmp(E2, "水") == 0)
	{
		textcolor(LIGHTCYAN);
	}
	if (strcmp(E2, "雷") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E2, "風") == 0)
	{
		textcolor(LIGHTGREEN);
	}
	if (strcmp(E2, "闇") == 0)
	{
		textcolor(LIGHTMAGENTA);
	}
	if (strcmp(E2, "光") == 0)
	{
		textcolor(YELLOW);

	}
	if (strcmp(E2, "壊") == 0)
	{
		textcolor(LIGHTGRAY);
	}


	printf("%s\n", E2);

	textcolor(WHITE);


	printf("|  体力：");	//体力表示開始

	//textbackground(LIGHTGRAY);
	if (strcmp(E2, "無") == 0||strcmp(E2,"覚醒")==0||strcmp(E2,"OV-C")==0)
	{
		textcolor(WHITE);
	}
	if (strcmp(E2, "炎") == 0)
	{
		textcolor(LIGHTRED);
	}
	if (strcmp(E2, "水") == 0)
	{
		textcolor(LIGHTCYAN);
	}
	if (strcmp(E2, "雷") == 0)
	{
		textcolor(YELLOW);
	}
	if (strcmp(E2, "風") == 0)
	{
		textcolor(LIGHTGREEN);
	}
	if (strcmp(E2, "闇") == 0)
	{
		textcolor(LIGHTMAGENTA);
	}
	if (strcmp(E2, "光") == 0)
	{
		textcolor(YELLOW);

	}
	if (strcmp(E2, "壊") == 0)
	{
		textcolor(LIGHTGRAY);
	}

	for (int i = 1; i <= icon2; i++)			//hpのアイコン最大表示を10に固定
	{
		printf("◆");
		count += 1;
	}
	textbackground(BLACK);
	textcolor(WHITE);
	for (int i = 1; i <= 18 - count; i++)			//ｈｐ表示直後の空白
	{
		printf("　");
	}


	printf("|　　　　　　防御力：%.0f\n", D2 * 1000);//空白の終わり
	printf("|　　　　　　　　　　　　　　　　　　　　　　|\n");
	printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n");		//二人目出力終了



	return 0;
}