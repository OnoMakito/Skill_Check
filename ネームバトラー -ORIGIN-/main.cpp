
//	HAL東京　AT11E-341　13番　小野牧人
//	ＣＰ提出課題
//
//	ネームバトラー　

//////全体の流れ
//①プロトタイプ宣言・グローバル変数宣言終了後、main文の最初で各ファイルを読み込む。
//②main文の中からtitle関数を呼び出しタイトルを表示。タイトル表示後なんらかの入力でmain文へ戻る。
//③main文中の無限ループの中にメニュー表示があり、そこから各モードへと移行。
//④create関数でキャラクターを二人以上設定し、battle関数で戦闘を開始。
//⑤battle関数でキャラを選択し、戦闘用の仮の変数に代入。
//⑥ループ処理を開始し、battle_disp関数で戦闘画面を展開、anime関数で顔文字表示、B1,B2関数で戦闘中のキャラの行動を交互に演算。
//⑦battle関数中でどちらかのキャラの体力が０になれば、main文へ戻る。


////キャラクターのパラメータの設定方法
//①入力した名前のすべての文字コードを合計し、それの平均を出す。
//②二つ目の文字コードに平均値を足した値を体力とする。
//③四つ目の文字コードに平均値を足した値を攻撃に設定する。
//④平均値を2倍にした値を防御力にする。
//⑤全ステータスを合計し、それの十桁以下の値をスピードとする。(速いほうが先行を取る。)
//⑥全文字コードの合計値の一桁目を出し、それを元に属性を決める。
//⑦体力・攻撃・防御のうち最も高いステータスと属性によって、そのキャラクターのスキルを設定。
//⑧体力をそのまま反映すると戦闘がすぐに終わるため、戦闘時間調整のために最後に体力の値を4.3倍する。
//⑨existance変数に１を入れ、その番号のキャラクターが存在することを示す。(設定されていない場合は0になっている。)


//キャラクターの属性
//炎は風、雷に強い
//風は水、雷に強い
//水は炎、雷に強い
//雷は炎、水、風に強い。
//闇は光に強い。
//光は闇に強い。
//無は属性的な有利不利は存在しない。

//戦闘中のスキル発動時にのみ発生する属性
//壊…すべての属性に対して自身の攻撃が弱化される。(威力減少)
//覚醒…すべての属性に対して自身の攻撃が上昇する。・毎ターン持続回復
//OV-C…毎ターン乱数でできた数だけで連続攻撃ができる(最大五回)・毎ターン持続回復

//スキルについて
//キャラクターの体力が50％以下になると、戦闘中に一度だけスキルを発動。
//それぞれステータスを組み合わせた計算によりダメージ付与や体力の回復、ステータスの変動や属性の変化などがある。








#define _CRT_SECURE_NO_WARNINGS

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



status character[4] =	//各メンバー初期値
{
	"　",		//name
	0,		//hp
	0,		//mp
	0,		//def
	0,		//speed
	"　",		//element
	"　",			//スキル名
	0		//existance(存在するかどうか　１：存在　0：存在しない)
};


//BGMアドレス格納変数
int mmf;	//menu music file
int bmf1;		//battle music file
int bmf2;		//bsttle music file2



/////関数プロトタイプ宣言

void title();	//タイトル
void check();	//キャラクター表示
int create(int notsaved);	//キャラクター作成
void battle();	//戦闘システム
int save(int notsaved);	//キャラクターデータのセーブ
void read();			//キャラクターデータのロード(自動)
int datadelete(int notsaved);	//全データの削除
int gameend(int notsaved);

//戦闘画面の顔文字

int main()
{

	//BGM楽曲ファイル展開

	mmf = opensound("メニュー曲.mp3");
	if (mmf == 0)
	{
		printf("ファイルの展開ができません。\nプログラムを終了します。\nエラー：メニュー曲");
		getch();
		exit(ABEND);
	}

	bmf1 = opensound("戦闘曲１.mp3");
	if (bmf1 == 0)
	{
		printf("ファイルの展開ができません\nプログラムを終了します。\nエラー：戦闘曲1");
		getch();
		exit(ABEND);
	}

	bmf2 = opensound("戦闘曲２.mp3");
	if (bmf2 == 0)
	{
		printf("ファイルの展開ができません\nプログラムを終了します。\nエラー:戦闘曲2");
		getch();
		exit(ABEND);
	}

	setvolume(mmf, 20);
	setvolume(bmf1, 10);
	setvolume(bmf2, 10);

	char windowtitle[15];
	strcpy(windowtitle, "ネームバトラー");
	setcaption(windowtitle);

	textcolor(WHITE);
	setcursortype(NOCURSOR);



	read();	//最後にセーブしたデータを読み込む


	title();	//タイトルを出力
	system("cls");	//画面をクリア




					//////////////////////////////////////////////////////////////////////////////////ここからゲームが始まる



	int notsaved = 0;

	for (;;)		//ゲーム全体の無限ループを開始。
	{
		srand(timeGetTime());	//メニューの枠の色を乱数で決める

		system("cls");

		int select;

		if (notsaved == 0)	//通常のメニュー表示
		{
			int color = rand() % 10;
			gotoxy(7, 7);
			switch (color)
			{
			case 0:textcolor(WHITE); break;	//乱数の一桁が0なら白
			case 1:case 2:textcolor(LIGHTRED); break;//乱数の一桁が1または2なら赤
			case 3:case 4:textcolor(LIGHTBLUE); break;//乱数の一桁が3または4なら青
			case 5:case 6:textcolor(LIGHTGREEN); break;//乱数の一桁が5または6なら緑
			case 7:case 8:textcolor(YELLOW); break;//乱数の一桁が7または8なら黄
			case 9:textcolor(LIGHTMAGENTA); break;//乱数の一桁が9なら紫
			}
			printf("◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆"); gotoxy(7, 8); textcolor(WHITE);
			printf("◇　 　　　　　　　　　　　　　 　　　　　　　　　　　◇"); gotoxy(7, 9);
			printf("◇ 　　　　　　　　　　　　　　　 　　　　　　　　　　◇"); gotoxy(7, 10);
			printf("◇"); textcolor(WHITE); printf("　　1:キャラクターの確認　　　　 　 　　　　　　　　"); textcolor(WHITE); printf("◇"); gotoxy(7, 11);
			printf("◇　　　　　　　　　　　　　　　 　　　 　　　　　　　◇"); gotoxy(7, 12);
			printf("◇"); textcolor(WHITE); printf("　　2:キャラクターを作る　　 　　　　　 　　　　　　"); textcolor(WHITE); printf("◇"); gotoxy(7, 13);
			printf("◇　　　　　　　　　　　　　 　　　　　　　 　　　　　◇"); gotoxy(7, 14);
			printf("◇"); textcolor(WHITE); printf("　　3:戦闘開始　　　　　 　　　　　　　　 　　　　　"); textcolor(WHITE); printf("◇"); gotoxy(7, 15);
			printf("◇　　　　　　　　　　　 　　　　　　　　　　 　　　　◇"); gotoxy(7, 16);
			printf("◇"); textcolor(WHITE); printf("　　4:セーブ　           　　　　　　　　　　 　　　"); textcolor(WHITE); printf("◇"); gotoxy(7, 17);
			printf("◇　　　　　　　　　　 　　　　　　　　　　　　　 　　◇"); gotoxy(7, 18);
			printf("◇"); textcolor(WHITE); printf("　　5:終了　　　　 　　　　　　　　　　　　　　　 　"); textcolor(WHITE); printf("◇"); gotoxy(7, 19);
			printf("◇　　　　　　　　　　　　　　　　　 　　　　　　　 　◇"); gotoxy(7, 20);
			printf("◇"); textcolor(WHITE); printf(" 　　　　　　　　　　　 　　　　　9:データを削除する"); textcolor(WHITE); printf("◇"); gotoxy(7, 21); textcolor(BLUE);
			color = rand() % 10;
			switch (color)
			{
			case 0:textcolor(WHITE); break;	//乱数の一桁が0なら白
			case 1:case 2:textcolor(LIGHTRED); break;//乱数の一桁が1または2なら赤
			case 3:case 4:textcolor(LIGHTBLUE); break;//乱数の一桁が3または4なら青
			case 5:case 6:textcolor(LIGHTGREEN); break;//乱数の一桁が5または6なら緑
			case 7:case 8:textcolor(YELLOW); break;//乱数の一桁が7または8なら黄
			case 9:textcolor(LIGHTMAGENTA); break;//乱数の一桁が9なら紫
			}
			printf("◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆"); textcolor(WHITE);

			gotoxy(8, 25);
			printf("番号を選んでください。\n");
		}

		else if (notsaved == 1)	//セーブ未実施警告表示あり
		{
			gotoxy(7, 7);
			int color = rand() % 10;
			gotoxy(7, 7);
			switch (color)
			{
			case 0:textcolor(WHITE); break;	//乱数の一桁が0なら白
			case 1:case 2:textcolor(LIGHTRED); break;//乱数の一桁が1または2なら赤
			case 3:case 4:textcolor(LIGHTBLUE); break;//乱数の一桁が3または4なら青
			case 5:case 6:textcolor(LIGHTGREEN); break;//乱数の一桁が5または6なら緑
			case 7:case 8:textcolor(YELLOW); break;//乱数の一桁が7または8なら黄
			case 9:textcolor(LIGHTMAGENTA); break;//乱数の一桁が9なら紫
			}
			printf("◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆"); gotoxy(7, 8); textcolor(WHITE);
			printf("◇　 　　　　　　　　　　　　　 　　　　　　　　　　　◇"); gotoxy(7, 9);
			printf("◇ 　　　　　　　　　　　　　　　 　　　　　　　　　　◇"); gotoxy(7, 10);
			printf("◇"); textcolor(WHITE); printf("　　1:キャラクターの確認　　　　 　 　　　　　　　　"); textcolor(WHITE); printf("◇"); gotoxy(7, 11);
			printf("◇　　　　　　　　　　　　　　　 　　　 　　　　　　　◇"); gotoxy(7, 12);
			printf("◇"); textcolor(WHITE); printf("　　2:キャラクターを作る　　 　　　　　 　　　　　　"); textcolor(WHITE); printf("◇"); gotoxy(7, 13);
			printf("◇　　　　　　　　　　　　　 　　　　　　　 　　　　　◇"); gotoxy(7, 14);
			printf("◇"); textcolor(WHITE); printf("　　3:戦闘開始　　　　　 　　　　　　　　 　　　　　"); textcolor(WHITE); printf("◇"); gotoxy(7, 15);
			printf("◇　　　　　　　　　　　 　　　　　　　　　　 　　　　◇"); gotoxy(7, 16);
			printf("◇"); textcolor(WHITE); printf("　　4:セーブ");; textcolor(LIGHTRED); printf("(セーブされていません)                  "); textcolor(WHITE);		//セーブされていない場合、警告として赤文字で表示する。
			printf("◇"); gotoxy(7, 17);
			printf("◇　　　　　　　　　　 　　　　　　　　　　　　　 　　◇"); gotoxy(7, 18);
			printf("◇"); textcolor(WHITE); printf("　　5:終了　　　　 　　　　　　　　　　　　　　　 　"); textcolor(WHITE); printf("◇"); gotoxy(7, 19);
			printf("◇　　　　　　　　　　　　　　　　　 　　　　　　　 　◇"); gotoxy(7, 20);
			printf("◇"); textcolor(WHITE); printf(" 　　　　　　　　　　　 　　　　　9:データを削除する"); textcolor(WHITE); printf("◇"); gotoxy(7, 21); textcolor(BLUE);

			color = rand() % 10;
			switch (color)
			{
			case 0:textcolor(WHITE); break;	//乱数の一桁が0なら白
			case 1:case 2:textcolor(LIGHTRED); break;//乱数の一桁が1または2なら赤
			case 3:case 4:textcolor(LIGHTBLUE); break;//乱数の一桁が3または4なら青
			case 5:case 6:textcolor(LIGHTGREEN); break;//乱数の一桁が5または6なら緑
			case 7:case 8:textcolor(YELLOW); break;//乱数の一桁が7または8なら黄
			case 9:textcolor(LIGHTMAGENTA); break;//乱数の一桁が9なら紫
			}
			printf("◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆"); textcolor(WHITE);

			gotoxy(8, 25);
			printf("番号を選んでください。\n");
		}

		select = getch();	//モードの選択


		if (select == '1')
		{
			check();	//キャラクター詳細情報確認
		}

		if (select == '2')
		{
			notsaved = create(notsaved);	//キャラクター設定　(誰かが設定されればセーブを促すメニューになる)
		}

		if (select == '3')
		{
			battle();		//戦闘開始　（関数内で戦闘に関する処理へと派生）
		}

		if (select == '4')
		{
			notsaved = save(notsaved);	//データセーブ　（セーブを行うことで未実施警告のない通常メニューになる）
		}

		if (select == '5')
		{
			gameend(notsaved);		//プログラムの終了　（セーブ未実施であれば、終了確認時に警告を表示する。）
		}

		if (select == '9')
		{
			notsaved = datadelete(notsaved);	//全データの削除　（削除した場合、セーブ未実施警告のない通常メニューになる）
		}


	}



}
