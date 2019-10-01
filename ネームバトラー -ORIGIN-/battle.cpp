
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

extern int mmf;
extern int bmf1;
extern int bmf2;

int battle_disp(float H1, float H2, int M1, int M2, float D1, float D2, char E1[6], char E2[6], int select1, int select2);		//戦闘用画面
int B1(int *M1, int *M2, int select1, int select2, float *H1, float *H2, float *D1, float *D2, char *E1, char *E2, int *sa1, int *counter1, int dmg, int *regene);	//一人目のターン
int B2(int *M2, int *M1, int select2, int select1, float *H1, float *H2, float *D1, float *D2, char *E1, char *E2, int *sa2, int *counter2, int dmg, int *regene);	//二人目のターン
void animeWait();	//待機場面

void battle()	//戦闘開始
{


	//戦闘を行えるかどうかを確認
	if (character[0].existance + character[1].existance + character[2].existance + character[3].existance < 2)	//全キャラクター文のexistanceを加算。2以上でなければメニュー(main)へ戻る。
	{
		printf("\n選べるキャラクターが少ないです！\nキャラクターを二人以上設定しましょう。");
		getch();
		return;
	}

	int counter1 = 0;	//一人目のスキル、鏡花水月のカウンター判定(2:カウンター発動,1:カウンター待ち,0:通常行動)
	int counter2 = 0;	//二人目のスキル、鏡花水月のカウンター判定(2:カウンター発動,1:カウンター待ち,0:通常行動)
	int dmg = 0;	//ダメージ計測変数
	int countdmg1 = 0;	//一人目のカウンター用ダメージ変数
	int countdmg2 = 0;	//二人目のカウンター用ダメージ変数
	int regene1 = 0;	//毎ターン持続回復(1:回復 0:何もしない)
	int regene2 = 0;	//毎ターン持続回復(1：回復　0：何もしない)
	int sa1 = 0;	//一人目のスキル発動状態(2:発動済み・1:発動条件達成・0:未発動)		略：Skill Activated1
	int sa2 = 0;	//二人目のスキル発動状態(2:発動済み・1:発動条件達成・0:未発動)		略：Skill Activated2

	int select1;
	int select2;

	system("cls");
	printf("\n１:%s\n\n２:%s\n\n３:%s\n\n４:%s\n", character[0].name, character[1].name, character[2].name, character[3].name);	//キャラクター名表示
	printf("\n一人目のキャラクターを選んでください。(0でキャンセル)\n");		//一人目のキャラクターを指定
	select1 = getch();


	for (select1; select1 != '0' && character[select1 - '1'].existance == 0 || select1 == 13;)	//選ばれた番号にキャラクターがいない場合と、エンターキーが入力された場合の再入力要求。-1の番号を持つキャラクターはいないため0を入力された場合は無視する
	{
		system("cls");
		printf("\n１:%s\n\n２:%s\n\n３:%s\n\n４:%s\n", character[0].name, character[1].name, character[2].name, character[3].name);	//キャラクター名の表示
		printf("\nその番号のキャラクターは存在しません。\nもう一度選んでください。(0でキャンセル)");
		select1 = getch();
	}


	if (select1 == '0')	//０を入力された場合、メニュー(main)へ戻る
	{
		return;
	}

	printf("\n%s", character[select1 - '1'].name);

	char N1[21];
	strcpy(N1, character[select1 - '1'].name);	//一人目の名前を代入
	float H1 = character[select1 - '1'].hp;	//一人目のプレイヤーの体力　
	int M1 = character[select1 - '1'].mp;	//一人目のプレイヤーの攻撃力
	float D1 = character[select1 - '1'].def;	//一人目のプレイヤーの防御力(1000で割り、相手の攻撃を防御力の割合だけ軽減する)
	D1 /= 1000;
	int speed1 = character[select1 - '1'].speed;	//一人目の速度計算

	char E1[6];
	strcpy(E1, character[select1 - '1'].element);	//一人目のプレイヤーの属性

	char skill1[35];
	strcpy(skill1, character[select1 - '1'].skill);	//一人目のプレイヤーのスキル名





	printf("\n\n二人目のキャラクターを選んでください。\n");		//二人目のキャラクターを指定

	select2 = getch();


	for (select2; select2 != '0' && (select2 == select1 || character[select2 - '1'].existance == 0) || select2 == 13;)	//二人目の番号を選んだ際に一人目と被っている場合とエンターキーを押された場合、再入力要求
	{
		system("cls");
		printf("\n１:%s\n\n２:%s\n\n３:%s\n\n４:%s\n", character[0].name, character[1].name, character[2].name, character[3].name);	//各キャラクター表示
		if (select2 == select1)	//二人目が一人目とキャラ被り
		{
			printf("\n一人目と同じキャラクターは選べません。");
		}
		if (select2 != '0' && character[select2 - '1'].existance == 0)	//選ばれた番号にキャラがいない場合の再入力処理。　-1の番号にキャラはいないため、0を押された場合は無視する。
		{
			printf("\nそのキャラクターは存在しません。");
		}
		printf("\nもう一度入力してください。(0でキャンセル)");
		select2 = getch();
	}

	if (select2 == '0')	//0を入力された場合にメニューへ戻る
	{
		return;
	}

	printf("\n%s", character[select2 - '1'].name);	//二人目のキャラクター名を表示

	char N2[21];
	strcpy(N2, character[select2 - '1'].name);
	float H2 = character[select2 - '1'].hp;	//二人目の体力
	int M2 = character[select2 - '1'].mp;	//二人目の攻撃力
	float D2 = character[select2 - '1'].def;	//二人目の防御力(5000で割り、防御力の割合だけ相手の攻撃を軽減する。)
	D2 /= 1000;
	int speed2 = character[select2 - '1'].speed;	//二人目の速度

	char E2[6];
	strcpy(E2, character[select2 - '1'].element);	//二人目の属性

	char skill2[35];
	strcpy(skill2, character[select2 - '1'].skill);		//二人目のスキル名


	stopsound(mmf);

	textcolor(LIGHTRED);
	gotoxy(5, 20);
	printf("戦闘を開始します。");
	gotoxy(6, 21);
	printf("Please AnyKey");
	textcolor(WHITE);
	getch();

	if (speed1 < speed2)	//二人目が先に行動する
	{
		srand(timeGetTime());
		int music = rand() % 10;	//音楽再生(曲は２パターン)
		if (music >= 5)
		{
			playsound(bmf1, 1);
		}
		else
		{
			playsound(bmf2, 1);
		}

		system("cls");//画面リセット
		battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//戦闘画面
		printf("\n%sの先制攻撃！！", N2);
		getch();



		for (; H1 > 0 && H2 > 0;)	//どちらかのプレイヤーの体力が0になるまでループ
		{
			if (H1 > 0 && H2 > 0)	//ターンごとに戦闘の継続を確認する。
			{
				if (H2 <= character[select2 - '1'].hp / 2 && sa2 == 0)	//体力が半分以下になると、一度だけスキルを発動する
				{
					sa2 = 1;
				}


				battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//戦闘画面
				animeWait();	//待機アニメ
				printf("\n%sの攻撃！\n", N2);
				getch();
				dmg = H1;
				B2(&M2, &M1, select2, select1, &H1, &H2, &D1, &D2, &E1[0], &E2[0], &sa2, &counter2, countdmg2, &regene2);	//二人目のターン
				dmg -= H1;	//このターンで与えたダメージ
				if (counter1 == 1)	//相手がカウンター待ちの場合
				{
					countdmg1 = dmg;
					counter1 = 2;	//相手がカウンター発動に移る。
				}
				printf("\n合計%dのダメージ！", dmg);
				getch();
			}


			if (H1 > 0 && H2 > 0)	//ターンごとに戦闘の継続を確認する。
			{

				if (H1 <= character[select1 - '1'].hp / 2 && sa1 == 0)	//体力が半分以下になると、一度だけスキルを発動する。
				{
					sa1 = 1;
				}

				battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//戦闘画面
				animeWait();	//待機アニメ
				printf("\n%sの攻撃！", N1);
				getch();
				dmg = H2;
				B1(&M1, &M2, select1, select2, &H1, &H2, &D1, &D2, &E1[0], &E2[0], &sa1, &counter1, countdmg1, &regene1);	//一人目のターン
				dmg -= H2;	//このターンで与えたダメージ
				if (counter2 == 1)	//相手がカウンター待ちの場合
				{
					countdmg2 = dmg;
					counter2 = 2;	//相手がカウンター発動に移る。
				}
				printf("\n合計%dのダメージ！", dmg);
				getch();
			}

		}

		if (H1 <= 0)
		{
			battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//戦闘画面
			printf("\n%sの勝利！！", N2);	//勝利者名表示
			getch();
			if (music >= 5)	//音楽停止
			{
				stopsound(bmf1);
			}
			else
			{
				stopsound(bmf2);
			}


			playsound(mmf, 1);	//メニュー曲再生
			return;	//メニューに戻る
		}
		if (H2 <= 0)
		{
			battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//戦闘画面
			printf("\n%sの勝利！！", N1);	//勝利者名表示
			getch();

			if (music >= 5)	//音楽停止
			{
				stopsound(bmf1);
			}
			else
			{
				stopsound(bmf2);
			}

			playsound(mmf, 1);	//メニュー曲再生
			return;	//メニューに戻る
		}


	}
	else	//一人目が先に行動する
	{
		srand(timeGetTime());
		int music = rand() % 10;	//音楽再生(曲は２パターン)
		if (music >= 5)
		{
			playsound(bmf1, 1);
		}
		else
		{
			playsound(bmf2, 1);
		}



		battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);
		printf("\n%sの先制攻撃！！", N1);

		for (; H1 > 0 && H2 > 0;)	//どちらかの体力が0になるまでループ
		{

			if (H1 > 0 && H2 > 0)	//ターンごとに戦闘の継続を確認する。
			{
				if (H1 <= character[select1 - '1'].hp / 2 && sa1 == 0)	//体力が半分以下になると、一度だけスキルを発動する。
				{
					sa1 = 1;
				}

				battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//戦闘画面
				animeWait();	//待機アニメ
				printf("\n%sの攻撃！", N1);
				getch();
				dmg = H2;
				B1(&M1, &M2, select1, select2, &H1, &H2, &D1, &D2, &E1[0], &E2[0], &sa1, &counter1, countdmg1, &regene1);	//一人目のターン
				dmg -= H2;	//このターンで与えたダメージ
				if (counter2 == 1)	//相手がカウンター待ちの場合
				{
					countdmg2 = dmg;
					counter2 = 2;	//相手がカウンター発動にうつる。
				}
				printf("\n合計%dのダメージ！", dmg);
				getch();
			}

			if (H1 > 0 && H2 > 0)//ターンごとに戦闘の継続を確認する。
			{
				if (H2 <= character[select2 - '1'].hp / 2 && sa2 == 0)	//体力が半分以下になると、一度だけスキルを発動する
				{
					sa2 = 1;
				}

				battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//戦闘画面
				animeWait();	//待機アニメ
				printf("\n%sの攻撃！\n", N2);
				getch();
				dmg = H1;
				B2(&M2, &M1, select2, select1, &H1, &H2, &D1, &D2, &E1[0], &E2[0], &sa2, &counter2, countdmg2, &regene2);	//戦闘画面表示
				dmg -= H1;	//このターンで与えたダメージ
				if (counter1 == 1)	//相手がカウンター待ちの場合
				{
					countdmg1 = dmg;
					counter1 = 2;	//相手がカウンター発動に移る。
				}
				printf("\n合計%dのダメージ！", dmg);
				getch();
			}


		}

		if (H1 <= 0)
		{
			battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//戦闘画面
			printf("\n%sの勝利！！", N2);	//勝利者名表示
			getch();

			if (music >= 5)	//音楽停止
			{
				stopsound(bmf1);
			}
			else
			{
				stopsound(bmf2);
			}
			playsound(mmf, 1);	//メニュー曲再生
			return;	//メニューへ
		}
		if (H2 <= 0)
		{
			battle_disp(H1, H2, M1, M2, D1, D2, E1, E2, select1, select2);	//戦闘画面
			printf("\n%sの勝利！！", N1);	//勝利者名表示
			getch();

			if (music >= 5)	//音楽停止
			{
				stopsound(bmf1);
			}
			else
			{
				stopsound(bmf2);
			}

			playsound(mmf, 1);	//メニュー曲再生
			return;	//メニューへ
		}

	}



}