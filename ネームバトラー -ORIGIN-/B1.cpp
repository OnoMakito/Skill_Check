
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


int battle_disp(float H1, float H2, int M1, int M2, float D1, float D2, char E1[6], char E2[6], int select1, int select2);		//戦闘用画面
void animeWait();	//待機場面
void animeA1H(char E1[5]);	//一人目攻撃ヒット時
void animeA1A(char E1[5]);	//一人目攻撃失敗時	


int B1(int *M1, int *M2, int select1, int select2, float *H1, float *H2, float *D1, float *D2, char *E1, char *E2, int *sa1, int *counter1, int dmg, int *regene)	//一人目のターン
{

	srand(timeGetTime());

	int random = rand() % 10;	//生成された乱数の一桁目を格納

	if (strcmp(E1, "炎") == 0)	//属性が炎の場合
	{
		if (*sa1 == 0 || *sa1 == 2)	//通常攻撃
		{
			if (strcmp(E2, "風") == 0 || strcmp(E2, "雷") == 0)	//相手の属性が風もしくは雷の場合
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
					animeA1H(E1);	//攻撃アニメ
					printf("\n属性が有利だ！");
					getch();
					*H2 -= (*M1*(1 - *D2))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
					animeA1H(E1);	//攻撃アニメ
					printf("\n属性が有利だ＿＿＿\n　　＿＿会心の一撃！！");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
					animeA1A(E1);//回避アニメ
					printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
					//回避回数を一つ加算
				}


			}
			else	//相手の属性がそれ以外の場合
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
					animeA1H(E1);	//攻撃アニメ
					*H2 -= (*M1*(1 - *D2));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
					animeA1H(E1);	//攻撃アニメ
					printf("\n会心の一撃！！");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
					animeA1A(E1);	//回避アニメ
					printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
				}
			}
		}
		else if (*sa1 == 1)	//スキル発動
		{
			printf("\nスキル発動！！");
			getch(); battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
			animeA1H(E1);	//攻撃アニメ

			if (strcmp(character[select1 - '1'].skill, "情け容赦なしの大爆発") == 0)
			{
				textcolor(LIGHTRED);
				printf("\n\n<< 情け容赦なしの大爆発 >>");
				textcolor(WHITE);
				*H1 *= 0.1;
				*H2 -= (*M1*(1 - *D2)) * 3.3;
				getch();
				printf("\n爆発の影響で自分もダメージを受けた。");
			}
			if (strcmp(character[select1 - '1'].skill, "アトミックインパクト") == 0)
			{
				textcolor(LIGHTRED);
				printf("\n\n<< アトミックインパクト >>");
				textcolor(WHITE);
				*H2 -= (*M1*(1 - *D2))*1.4;
				*D2 /= 2;
				getch();
				printf("\n相手の防御力が半減した！");
			}
			if (strcmp(character[select1 - '1'].skill, "メテオライト") == 0)
			{
				textcolor(LIGHTRED);
				printf("\n\n<< メテオライト >>");
				textcolor(WHITE);
				*H2 -= (*M1*(1 - *D2)) * 2;
				getch();
				printf("\n大ダメージ！");

			}

			*sa1 = 2;	//SkillActivatedを２にする。(スキル発動済み)

		}

	}

	if (strcmp(E1, "水") == 0)	//属性が水の場合
	{
		if (*counter1 == 0)	//カウンター待機をしていない状態
		{
			if (*sa1 == 0 || *sa1 == 2)//通常攻撃
			{
				if (strcmp(E2, "炎") == 0 || strcmp(E2, "雷") == 0)	//相手の属性が炎もしくは雷の場合
				{

					if (random >= 2 && random <= 7)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
						animeA1H(E1);	//攻撃アニメ
						printf("\n属性が有利だ！");
						getch();
						*H2 -= (*M1*(1 - *D2))*1.25;
					}
					else if (random >= 8)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
						animeA1H(E1);//攻撃アニメ
						printf("\n属性が有利だ＿＿＿\n　　＿＿会心の一撃！！");
						getch();
						*H2 -= (*M1*(1 - *D2)) * 1.3;

					}
					else
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
						animeA1A(E1);	//回避アニメ
						printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
					}

				}
				else
				{

					if (random >= 2 && random <= 7)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
						animeA1H(E1);	//攻撃アニメ
						*H2 -= (*M1*(1 - *D2));
					}
					else if (random >= 8)
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
						animeA1H(E1);	//攻撃アニメ
						printf("\n会心の一撃！！");
						getch();
						*H2 -= (*M1*(1 - *D2)) * 1.2;
					}
					else
					{
						battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
						animeA1A(E1);	//回避アニメ
						printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
					}
				}
			}
			else if (*sa1 == 1)	//スキル発動
			{
				printf("\nスキル発動！！");
				getch();

				if (strcmp(character[select1 - '1'].skill, "オーシャンズアギト") == 0)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
					animeA1H(E1);
					textcolor(LIGHTCYAN);
					printf("\n\n<< オーシャンズアギト >>");
					textcolor(WHITE);
					*H2 -= (*M1*(1 - *D2))*1.5;
					*M2 *= 0.7;
					getch();
					printf("\n相手の攻撃力が減少した！");
				}
				if (strcmp(character[select1 - '1'].skill, "海刃オケアノス") == 0)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
					animeA1H(E1);
					textcolor(LIGHTCYAN);
					printf("\n\n<< 海刃オケアノス >>");
					textcolor(WHITE);
					*H2 -= *M1*1.5;
					getch();
					printf("\n相手の防御を無視した強烈な一撃！！");
				}
				if (strcmp(character[select1 - '1'].skill, "鏡花水月") == 0)
				{
					textcolor(LIGHTCYAN);
					printf("\n\n<< 鏡花水月 >>");
					textcolor(WHITE);
					*counter1 = 1;
					getch();
					printf("\n%sは集中力を高める…", character[select1 - '1'].name);

				}
				*sa1 = 2;
			}
		}
		else if (*counter1 == 1)
		{
			//何もしない
		}
		else if (*counter1 == 2)
		{
			if (dmg != 0)	//カウンターの成功
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1H(E1);
				printf("\nカウンター発動！！");
				*H2 -= (dmg*(1 - *D2)) * 3.8;
				getch();
				*counter1 = 0;
			}
			else
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeWait();
				printf("\nカウンター失敗…");
				getch();
				*counter1 = 0;
			}
		}


	}


	if (strcmp(E1, "風") == 0)	//自分が風属性の場合
	{

		if (*sa1 == 0 || *sa1 == 2)//通常攻撃
		{
			if (strcmp(E2, "水") == 0 || strcmp(E2, "雷") == 0)	//相手の属性が水もしくは神内rの場合
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
					animeA1H(E1);
					printf("\n属性が有利だ！");
					getch();
					*H2 -= (*M1*(1 - *D2))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
					animeA1H(E1);
					printf("\n属性が有利だ＿＿＿\n　　＿＿会心の一撃！！");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘画面
					animeA1A(E1);
					printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
				}

			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					*H2 -= (*M1*(1 - *D2));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					printf("\n会心の一撃！！");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1A(E1);
					printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
				}
			}
		}
		else if (*sa1 == 1)	//スキル発動
		{
			printf("\nスキル発動！！");
			getch();

			if (strcmp(character[select1 - '1'].skill, "ライジングストーム") == 0)
			{
				textcolor(LIGHTGREEN);
				printf("\n\n<< ライジングストーム >>");
				textcolor(WHITE);
				*M1 *= 1.5;
				*D1 *= 1.5;
				*H2 -= (*M1*(1 - *D2))*0.8;
				getch();
				printf("\n攻撃と防御が上昇した！！");
			}
			if (strcmp(character[select1 - '1'].skill, "疾風怒濤") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
				animeA1H(E1);
				textcolor(LIGHTGREEN);
				printf("\n\n<< 疾風怒濤 >>");
				textcolor(WHITE);
				for (int i = 0; i < 4; i++)
				{
					int enemy = *H2;
					srand(timeGetTime());
					random = rand() % 10;
					if (random >= 3 && random <= 7)
					{
						*H2 -= (*M1*(1 - *D2))*0.6;
						enemy -= *H2;
						printf("\n%dのダメージ！", abs(enemy));
					}
					else if (random >= 8)
					{
						printf("\n会心の一撃！！");
						*H2 -= (*M1*(1 - *D2)) * 0.7;
						enemy -= *H2;
						printf("\n%dのダメージ！", abs(enemy));
					}
					else
					{

						printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
					}
					getch();
				}
				printf("\n4回攻撃！！");
			}
			if (strcmp(character[select1 - '1'].skill, "サイクロンエッジ") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
				animeA1H(E1);
				textcolor(LIGHTGREEN);
				printf("\n\n<< サイクロンエッジ >>");
				textcolor(WHITE);
				*H2 -= ((character[select1 - '1'].speed * 3) + (*M1*1.1))*(1 - *D2);
				getch();
				printf("\n目にも止まらぬ斬撃！！");

			}
			*sa1 = 2;
		}

	}

	if (strcmp(E1, "雷") == 0)	//雷属性の場合
	{

		if (*sa1 == 0 || *sa1 == 2)	//通常攻撃
		{
			if (strcmp(E2, "炎") == 0 || strcmp(E2, "水") == 0 || strcmp(E2, "風") == 0)	//相手の属性が炎、水、風のいずれかである場合
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					printf("\n属性が有利だ！");
					getch();
					*H2 -= (*M1*(1 - *D2))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					printf("\n属性が有利だ＿＿＿\n　　＿＿会心の一撃！！");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1A(E1);
					printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
				}


			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					*H2 -= (*M1*(1 - *D2));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					printf("\n会心の一撃！！");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1A(E1);
					printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
				}
			}
		}
		else if (*sa1 == 1)	//スキル発動
		{
			printf("\nスキル発動！！");
			getch();
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
			animeA1H(E1);

			if (strcmp(character[select1 - '1'].skill, "ライトニングスラッシュ") == 0)
			{
				textcolor(YELLOW);
				printf("\n\n<< ライトニングスラッシュ >>");
				textcolor(WHITE);
				*H2 -= (*M1*(1 - *D2 / 2))*2.2;
				getch();
				printf("\n大ダメージ！！");
			}
			if (strcmp(character[select1 - '1'].skill, "アークブラスト") == 0)
			{
				textcolor(YELLOW);
				printf("\n\n<< アークブラスト >>");
				textcolor(WHITE);
				int arc = *H1;
				*H1 /= 2;
				arc -= *H1;
				*H2 -= arc * 3;
				getch();
				printf("\n捨て身の一撃！");
			}
			if (strcmp(character[select1 - '1'].skill, "ママラガン") == 0)
			{
				textcolor(YELLOW);
				printf("\n\n<< ママラガン >>");
				textcolor(WHITE);
				int mm = *M1 + *D1;
				*H2 -= (mm*(1 - *D2))*2.2;
				getch();
				printf("\n大ダメージ！");

			}

			*sa1 = 2;	//SkillActivatedを２にする。(スキル発動済み)

		}


	}

	if (strcmp(E1, "闇") == 0)	//自身が闇属性の場合
	{
		if (*sa1 == 0 || *sa1 == 2)//通常攻撃
		{
			if (strcmp(E2, "光") == 0)	//相手が光属性の場合
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					printf("\n属性が有利だ！");
					getch();
					*H2 -= (*M1*(1 - *D2))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					printf("\n属性が有利だ＿＿＿\n　　＿＿会心の一撃！！");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1A(E1);
					printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
				}

			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					*H2 -= (*M1*(1 - *D2));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					printf("\n会心の一撃！！");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1A(E1);
					printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
				}
			}
		}
		else if (*sa1 == 1)	//スキル発動
		{
			printf("\nスキル発動！！");
			getch();

			if (strcmp(character[select1 - '1'].skill, "宵の明星") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
				animeA1H(E1);
				textcolor(LIGHTMAGENTA);
				printf("\n\n<< 宵の明星 >>");
				textcolor(WHITE);
				int yoi = *M1;
				*M1 *= 0.5;	//攻撃力を半減する
				yoi -= *M1;	//攻撃力の減った値だけ変数に代入
				yoi += *D1;
				*D1 *= 0.5;	//防御力を半減する
				yoi -= *D1;	//防御力の減った値だけ変数に代入

				*H2 -= (yoi*2.5) * (1 - *D2);
				*H1 += yoi * 1.5;
				getch();
				printf("\n攻撃力と防御力を代償に、強力な一撃！！\n体力が回復した！");
			}
			if (strcmp(character[select1 - '1'].skill, "ブラッディギア") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
				animeA1H(E1);
				textcolor(LIGHTMAGENTA);
				printf("\n\n<< ブラッディギア >>");
				textcolor(WHITE);

				int blood = *H1;	//変数に現在の自分の体力を格納
				*H1 /= 2;		//体力が半減		
				blood /= 2;	//格納した値を半減(体力と同じだけ減る)	

				*M1 += blood * 2;	//減った体力の2倍の値攻撃に加算
				*D1 += (blood * 2) / 1000;	//減った体力の2倍の値防御に加算
				getch();
				printf("\n体力が半減したが、\n攻撃と防御が大幅に上昇した！！");
			}
			if (strcmp(character[select1 - '1'].skill, "ブラックアポカリプス") == 0)
			{
				textcolor(LIGHTMAGENTA);
				printf("\n\n<< ブラックアポカリプス >>");
				textcolor(WHITE);
				*M1 += *D2;
				*D2 = 0;
				getch();
				printf("\n相手の防御力を奪った！！\n相手は防御力が0になった！！");

			}
			*sa1 = 2;
		}
	}

	if (strcmp(E1, "光") == 0)	//自分が光属性
	{
		if (*sa1 == 0 || *sa1 == 2)//通常攻撃
		{
			if (strcmp(E2, "闇") == 0)	//相手が闇属性
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					printf("\n属性が有利だ！");
					getch();
					*H2 -= (*M1*(1 - *D2))*1.25;
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					printf("\n属性が有利だ＿＿＿\n　　＿＿会心の一撃！！");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.3;

				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1A(E1);
					printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
				}

			}
			else
			{

				if (random >= 2 && random <= 7)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					*H2 -= (*M1*(1 - *D2));
				}
				else if (random >= 8)
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1H(E1);
					printf("\n会心の一撃！！");
					getch();
					*H2 -= (*M1*(1 - *D2)) * 1.2;
				}
				else
				{
					battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);//戦闘画面
					animeA1A(E1);
					printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
				}
			}
		}
		else if (*sa1 == 1)	//スキル発動
		{
			printf("\nスキル発動！！");
			getch();

			if (strcmp(character[select1 - '1'].skill, "明けの明星") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
				animeA1H(E1);
				textcolor(YELLOW);
				printf("\n\n<< 明けの明星 >>");
				textcolor(WHITE);
				int ake = *M1;
				*M1 *= 0.5;//攻撃力を半減する
				ake -= *M1;//攻撃力の減った値だけ変数に代入
				ake += *D1;
				*D1 *= 0.5;//防御力を半減する
				ake -= *D1;//防御力の減った値だけ変数に代入

				*H2 -= (ake*2.5) * (1 - *D2);
				*H1 += ake;
				getch();
				printf("\n攻撃力と防御力を代償に、強力な一撃！！\n体力が回復した！");
			}
			if (strcmp(character[select1 - '1'].skill, "シャイニングスピア") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
				animeA1H(E1);
				textcolor(YELLOW);
				printf("\n\n<< シャイニングスピア >>");
				textcolor(WHITE);
				*H2 -= *M1*1.5;
				getch();
				printf("\n相手の防御を無視した強烈な一撃！！");
			}
			if (strcmp(character[select1 - '1'].skill, "治癒の光") == 0)
			{
				textcolor(YELLOW);
				printf("\n\n<< 治癒の光 >>");
				textcolor(WHITE);
				*regene = 1;
				*D1 *= 1.5;
				getch();
				printf("\n持続回復付与！\n防御力が上昇した！");


			}
			*sa1 = 2;
		}

	}

	if (strcmp(E1, "無") == 0)	//自身の属性が無属性の場合
	{
		if (*sa1 == 0 || *sa1 == 2)//通常攻撃
		{
			if (random >= 2 && random <= 7)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1H(E1);
				*H2 -= (*M1*(1 - *D2));
			}
			else if (random >= 8)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1H(E1);
				printf("\n会心の一撃！！");
				getch();
				*H2 -= (*M1*(1 - *D2)) * 1.2;
			}
			else
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1A(E1);
				printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
			}
		}
		else if (*sa1 == 1)	//スキル発動
		{
			printf("\nスキル発動！！");
			if (strcmp(character[select1 - '1'].skill, "覚醒") == 0)
			{
				textcolor(LIGHTGRAY);
				printf("\n<< 覚醒 >>");
				textcolor(WHITE);

				strcpy(E1, "覚醒");
				getch();
				*H1 *= 1.28;
				*regene = 1;
				printf("\n属性が変化した！！\n持続回復効果付与！\n攻撃がはずれなくなった。");
				return 0;
			}
			if (strcmp(character[select1 - '1'].skill, "オーバークロック") == 0)
			{
				textcolor(LIGHTGRAY);
				printf("\n<< オーバークロック >>");
				textcolor(WHITE);

				strcpy(E1, "OV-C");
				printf("\n属性が変化した。");
				printf("\n攻撃回数が増加した！");
				*regene = 1;
				printf("\n持続回復効果付与！");
				return 0;
			}
			if (strcmp(character[select1 - '1'].skill, "エレメントブレイク") == 0)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);	//戦闘用画面
				animeA1H(E1);
				textcolor(LIGHTGRAY);
				printf("\n<< エレメントブレイク >>");
				textcolor(WHITE);
				strcpy(E2, "壊");
				*H2 -= (*M1*(1 - *D2))*1.3;
				printf("\n相手の属性を破壊した！\n相手は弱体化した！");
				printf("\n相手はダメージを受けた。");
			}
			*sa1 = 2;
		}
	}
	if (strcmp(E1, "覚醒") == 0)
	{
		if (random >= 1 && random <= 6)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA1H(E1);
			*H2 -= (*M1*(1 - *D2))*1.4;
		}
		else if (random >= 7)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA1H(E1);
			printf("\n会心の一撃！！");
			getch();
			*H2 -= (*M1*(1 - *D2)) * 1.7;
		}
	}
	if (strcmp(E1, "壊") == 0)
	{
		if (random >= 3 && random <= 7)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA1H(E1);
			*H2 -= (*M1*(1 - *D2))*0.9;
		}
		else if (random >= 8)
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA1H(E1);
			printf("\n会心の一撃！！");
			getch();
			*H2 -= (*M1*(1 - *D2));
		}
		else
		{
			battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
			animeA1A(E1);
			printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
		}
	}
	if (strcmp(E1, "OV-C") == 0)
	{
		srand(timeGetTime());
		int ov = rand() % 10;	//発生したランダム値の一桁目を求める
		ov /= 2;	//ランダム値の一桁目を2で割り、最高で4の値に変化させる。
		ov += 1;	//最低でも１の値にするために１を追加する。(最低：1　最高：5)

		for (int i = 0; i < ov; i++)
		{

			srand(timeGetTime());	//ランダム値をシードにする
			random = rand() % 10;	//ランダム値の一桁目を代入する。

			if (random >= 2 && random <= 7)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1H(E1);
				printf("\n\nクロック%d！", i + 1);
				int enemy = *H2;
				*H2 -= (*M1*(1 - *D2))*0.7;
				enemy -= *H2;
				printf("\n%dのダメージ！", enemy);
			}
			else if (random >= 8)
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1H(E1);
				printf("\n\nクロック%d！", i + 1);
				int enemy = *H2;
				printf("\n会心の一撃！！");
				*H2 -= (*M1*(1 - *D2)) * 0.8;
				enemy -= *H2;
				printf("\n%dのダメージ！", enemy);
			}
			else
			{
				battle_disp(*H1, *H2, *M1, *M2, *D1, *D2, E1, E2, select1, select2);
				animeA1A(E1);
				printf("\n\nクロック%d！", i + 1);
				printf("\n%sは攻撃を避けた！", character[select2 - '1'].name);
			}

			getch();
		}

		printf("\n%d回攻撃！！", ov);
		getch();
	}

	if (*regene == 1)
	{
		*H1 *= 1.38;
		printf("\n回復効果発動");
	}

	return *M1, select1, select2, *H2, *D2;
}