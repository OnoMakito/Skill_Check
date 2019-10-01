
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

int create(int notsaved)	//キャラクタ作成
{
	system("cls");	//画面リセット

	int select;

	printf("\n1:%s\n\n2:%s\n\n3:%s\n\n4:%s\n\n\n何番目のキャラクタを設定しますか？  (0で戻る)", character[0].name, character[1].name, character[2].name, character[3].name);	//キャラクター名と番号を表示

	select = _getch();	//番号を選択

	for (select; select != '0'&&select != '1'&&select != '2'&&select != '3'&&select != '4';)	//例外処理（もう一度入力）
	{
		system("cls");
		printf("もう一度入力してください。\n\n");
		printf("\n1:%s\n\n2:%s\n\n3:%s\n\n4:%s\n\n\n何番目のキャラクタを設定しますか？  (0で戻る)", character[0].name, character[1].name, character[2].name, character[3].name);

		select = _getch();
	}


	if (select == '0')
	{
		return notsaved;	//0を入力した場合、メニューへ戻る(mainへ)
	}



	system("cls");
	printf("なまえをにゅうりょくしてください。\n\n　名前:");

	setcursortype(SOLIDCURSOR);	//カーソルを表示

	scanf("%s", character[select - '1'].name);	//名前の入力
	rewind(stdin);

	for (select; _mbstrlen(character[select - '1'].name) <= 1 || _mbstrlen(character[select - '1'].name) > 20;)	//名前が短い場合と長い場合の再入力開始
	{
		system("cls");
		if (strlen(character[select - '1'].name) <= 1)
		{
			printf("\n名前が短すぎます！\n\nもう一度入力してください\n");
			printf("\n名前：");
		}
		else if (strlen(character[select - '1'].name) > 20)
		{
			printf("\n名前が長すぎます！\n\nもう一度入力してください\n");
			printf("\n名前：");
		}

		scanf("\n%s", character[select - '1'].name);
		rewind(stdin);

	}

	setcursortype(NOCURSOR);	//カーソル表示を消す

	int count = strlen(character[select - '1'].name);	//文字コードを入手する回数の初期値

	int total = 0;		//文字コードの合計値
	int ep = 0;			//element point 属性値
	int max;	//各ステータスの最大値




				////////////////////////////////////////////////////////パラメータ設定開始

	for (int i = 0; i < count; i++)
	{

		total += abs(character[select - '1'].name[i]);	//すべての文字コードの合計値を計測

	}

	ep = total % 10;		//コード合計値の一桁目を計測　(後にこれをもとに属性を決める)


	total = total / count;	//合計値から、全体の平均を入手


	printf("\n\n\n\n\n");

	character[select - '1'].hp = abs(character[select - '1'].name[1]) + total;	//二つ目の文字コードに平均値を足した値を体力にする
	int HP = character[select - '1'].hp;	//スピードの計算のためにint型の変数へ格納する。
	character[select - '1'].mp = abs(character[select - '1'].name[3]) + total;	//四つ目の文字コードに平均値を足した値を攻撃にする
	character[select - '1'].def = total * 2;	//平均値を2倍にした値を防御力にする。
	character[select - '1'].speed = (HP + character[select - '1'].mp + character[select - '1'].def) % 100;	//すべてのステータスを合計し、それの十桁目までをスピードとする。


	max = character[select - '1'].hp;	//maxに体力値を格納
	int sp = 1;	//スキルの初期値を１にしておく。

	if (max < character[select - '1'].mp)
	{
		max = character[select - '1'].mp;	//maxに攻撃値を格納
		sp = 2;	//体力よりも攻撃が大きければスキルの数値を２にする
	}
	if (max < character[select - '1'].def)
	{
		max = character[select - '1'].def;
		sp = 3;	//体力または攻撃力よりも防御が大きければスキルの数値を３にする。
	}


	if (ep == 0)	//コード合計値が0の場合
	{
		strcpy(character[select - '1'].element, "無");

		if (sp == 1)	//各ステータス中体力が最高の場合
		{
			strcpy(character[select - '1'].skill, "覚醒");
		}
		else if (sp == 2)	//各ステータス中攻撃が最高の場合
		{
			strcpy(character[select - '1'].skill, "オーバークロック");
		}
		else if (sp == 3)	//各ステータス中防御が最高の場合
		{
			strcpy(character[select - '1'].skill, "エレメントブレイク");
		}
	}

	if (ep == 1 || ep == 2)	//コード合計値が1か2の場合
	{
		strcpy(character[select - '1'].element, "炎");

		if (sp == 1)	//各ステータス中体力が最高の場合
		{
			strcpy(character[select - '1'].skill, "情け容赦なしの大爆発");
		}
		else if (sp == 2)	//各ステータス中攻撃が最高の場合
		{
			strcpy(character[select - '1'].skill, "アトミックインパクト");
		}
		else if (sp == 3)		//各ステータス中防御が最高の場合
		{
			strcpy(character[select - '1'].skill, "メテオライト");
		}
	}
	if (ep == 3 || ep == 4)	//コード合計値が3か4の場合
	{
		strcpy(character[select - '1'].element, "水");

		if (sp == 1)	//各ステータス中体力が最高の場合
		{
			strcpy(character[select - '1'].skill, "オーシャンズアギト");
		}
		else if (sp == 2)	//各ステータス中攻撃が最高の場合
		{
			strcpy(character[select - '1'].skill, "海刃オケアノス");
		}
		else if (sp == 3)	//各ステータス中防御が最高の場合
		{
			strcpy(character[select - '1'].skill, "鏡花水月");
		}

	}
	if (ep == 5 || ep == 6)	//コード合計値が5か6の場合
	{
		strcpy(character[select - '1'].element, "風");

		if (sp == 1)	//各ステータス中体力が最高の場合
		{
			strcpy(character[select - '1'].skill, "ライジングストーム");
		}
		else if (sp == 2)	//各ステータス中攻撃が最高の場合
		{
			strcpy(character[select - '1'].skill, "疾風怒濤");
		}
		else if (sp == 3)	//各ステータス中防御が最高の場合
		{
			strcpy(character[select - '1'].skill, "サイクロンエッジ");
		}

	}
	if (ep == 7)	//コード合計値が7の場合
	{
		strcpy(character[select - '1'].element, "雷");

		if (sp == 1)	//各ステータス中体力が最高の場合
		{
			strcpy(character[select - '1'].skill, "ライトニングスラッシュ");
		}
		else if (sp == 2)	//各ステータス中攻撃が最高の場合
		{
			strcpy(character[select - '1'].skill, "アークブラスト");
		}
		else if (sp == 3)	//各ステータス中防御が最高の場合
		{
			strcpy(character[select - '1'].skill, "ママラガン");
		}

	}
	if (ep == 8)	//コード合計値が8の場合
	{
		strcpy(character[select - '1'].element, "光");

		if (sp == 1)	//各ステータス中体力が最高の場合
		{
			strcpy(character[select - '1'].skill, "明けの明星");
		}
		else if (sp == 2)	//各ステータス中攻撃が最高の場合
		{
			strcpy(character[select - '1'].skill, "シャイニングスピア");
		}
		else if (sp == 3)	//各ステータス中防御が最高の場合
		{
			strcpy(character[select - '1'].skill, "治癒の光");
		}

	}
	if (ep == 9)	//コード合計値が9の場合
	{
		strcpy(character[select - '1'].element, "闇");

		if (sp == 1)	//各ステータス中体力が最高の場合
		{
			strcpy(character[select - '1'].skill, "宵の明星");
		}
		else if (sp == 2)	//各ステータス中攻撃が最高の場合
		{
			strcpy(character[select - '1'].skill, "ブラッディギア");
		}
		else if (sp == 3)	//各ステータス中防御が最高の場合
		{
			strcpy(character[select - '1'].skill, "ブラックアポカリプス");
		}

	}


	character[select - '1'].hp *= 4.3;	//体力を増やし、戦闘時間を伸ばす

	character[select - '1'].existance = 1;		//変数に１を代入。そのキャラクターが存在することを示す




												//ステータス設定結果
	printf("\n\n体力:%.0f", character[select - '1'].hp);	//体力の表示と評価
	if (character[select - '1'].hp >= 900)
	{
		textcolor(LIGHTRED);
		printf("\n強い！！\n");
		textcolor(WHITE);
	}
	else if (character[select - '1'].hp >= 700 && character[select - '1'].hp < 900)
	{
		textcolor(LIGHTCYAN);
		printf("\nまあまあ\n");
		textcolor(WHITE);
	}
	else
	{
		textcolor(LIGHTGRAY);
		printf("\n弱い…\n");
		textcolor(WHITE);
	}


	printf("\n魔力:%d", character[select - '1'].mp);	//攻撃力の表示と評価
	if (character[select - '1'].mp >= 200)
	{
		textcolor(LIGHTRED);
		printf("\n強い！！\n");
		textcolor(WHITE);
	}
	else if (character[select - '1'].mp >= 167 && character[select - '1'].mp <= 199)
	{
		textcolor(LIGHTCYAN);
		printf("\nまあまあ\n");
		textcolor(WHITE);
	}
	else
	{
		textcolor(LIGHTGRAY);
		printf("\n弱い…\n");
		textcolor(WHITE);
	}



	printf("\n防御:%d", character[select - '1'].def);		//防御力の表示と評価
	if (character[select - '1'].def >= 200)
	{
		textcolor(LIGHTRED);
		printf("\n強い！\n");
		textcolor(WHITE);
	}
	else if (character[select - '1'].def >= 167 && character[select - '1'].def <= 199)
	{
		textcolor(LIGHTCYAN);
		printf("\nまあまあ\n");
		textcolor(WHITE);
	}
	else
	{
		textcolor(LIGHTGRAY);
		printf("\n弱い…\n");
		textcolor(WHITE);
	}

	printf("\n速度:%d", character[select - '1'].speed);	//スピードの表示と評価
	if (character[select - '1'].speed >= 75)
	{
		textcolor(LIGHTRED);
		printf("\n速い！！\n");
		textcolor(WHITE);
	}
	else if (character[select - '1'].speed >= 40 && character[select - '1'].speed <= 74)
	{
		textcolor(LIGHTCYAN);
		printf("\nまあまあ\n");
		textcolor(WHITE);
	}
	else
	{
		textcolor(LIGHTGRAY);
		printf("\n遅い…\n");
		textcolor(WHITE);
	}

	printf("\n属性:");

	//属性ごとにテキストカラ―を変更する
	if (ep == 0)	//無属性
	{
		textcolor(LIGHTGRAY);
	}
	if (ep == 1 || ep == 2)	//炎属性
	{
		textcolor(LIGHTRED);
	}
	if (ep == 3 || ep == 4)	//水属性
	{
		textcolor(LIGHTCYAN);
	}
	if (ep == 5 || ep == 6)	//風属性
	{
		textcolor(LIGHTGREEN);
	}
	if (ep == 7 || ep == 8)	//雷属性・光属性
	{
		textcolor(YELLOW);
	}
	if (ep == 9)	//闇属性
	{
		textcolor(LIGHTMAGENTA);
	}
	printf("%s\n", character[select - '1'].element);
	textcolor(WHITE);
	printf("\nスキル:");
	if (ep == 0)	//無属性
	{
		textcolor(LIGHTGRAY);
	}
	if (ep == 1 || ep == 2)	//炎属性
	{
		textcolor(LIGHTRED);
	}
	if (ep == 3 || ep == 4)	//水属性
	{
		textcolor(LIGHTCYAN);
	}
	if (ep == 5 || ep == 6)	//風属性
	{
		textcolor(LIGHTGREEN);
	}
	if (ep == 7 || ep == 8)	//雷属性・光属性
	{
		textcolor(YELLOW);
	}
	if (ep == 9)	//闇属性
	{
		textcolor(LIGHTMAGENTA);
	}

	printf("<< %s >>", character[select - '1'].skill);

	////スキルの説明
	if (ep == 0)	//無属性
	{
		textcolor(LIGHTGRAY);
		switch (sp)
		{
		case 1:printf("\n   属性はなくとも、その強き信念が究極の力を呼び覚ます＿＿！！"); break;
		case 2:printf("\n   今こそ解き放て、すべてを超越せし力を＿＿！！"); break;
		case 3:printf("\n   人間が神の失敗作に過ぎないのか、\n   神が人間の失敗作に過ぎないのか。\n\n      ＿＿フリードリヒ・ヴィルヘルム・ニーチェ");
		}
	}
	if (ep == 1 || ep == 2)	//炎属性
	{
		textcolor(LIGHTRED);
		switch (sp)
		{
		case 1:printf("\n   羅刹の如きその殺意は、地を焼き天をも焦がす。\n   すべてを燃やす覚悟はあるか＿＿？"); break;
		case 2:printf("\n   燃える意志の前に、防御など無力でしかない。\n   相手の防御を削り壊せ！"); break;
		case 3:printf("\n   天より振り降ろされし鉄槌は、差別することなく、全て等しく叩き潰す。");
		}
	}
	if (ep == 3 || ep == 4)	//水属性
	{
		textcolor(LIGHTCYAN);
		switch (sp)
		{
		case 1:printf("\n   逆らうもの全てを飲み込む海。\n   そのアギトで相手の攻撃を喰らえ！"); break;
		case 2:printf("\n   大海をも引き裂く刃、その名はオケアノス。\n   相手の防御を無視した攻撃！"); break;
		case 3:printf("\n   極限を超えた覇気は、全てをいなし、全てを無に帰す。\n   之正に、鏡花水月の如し。"); break;
		}
	}
	if (ep == 5 || ep == 6)	//風属性
	{
		textcolor(LIGHTGREEN);
		switch (sp)
		{
		case 1:printf("\n   駆け上がれ、その風と共に！\n   自身の攻撃と防御が上昇！"); break;
		case 2:printf("\n   絶え間なき怒涛の連撃！\n   荒ぶる風の力を叩き込め！"); break;
		case 3:printf("\n   敵を切りさくは疾風の刃！\n   自身の速度が速いほど威力が上昇！"); break;
		}
	}
	if (ep == 7)//雷属性
	{
		textcolor(YELLOW);
		switch (sp)
		{
		case 1:printf("\n   空を引き裂く紫電の一閃。\n   相手の防御が半減した状態で強力な一撃！"); break;
		case 2:printf("\n   その怒りは、轟雷と共に鳴り響く＿＿\n   体力を犠牲に、強力な一撃！"); break;
		case 3:printf("\n   叫べ！轟け！その咆哮は大地をも揺るがす！！\n   攻撃と防御を合わせた強力な一撃！"); break;
		}
	}
	if (ep == 8)	//光属性
	{
		textcolor(YELLOW);
		switch (sp)
		{
		case 1:printf("\n   始まりに煌く光、その名もルシフェル。\n   攻撃と防御を代償に強力な一撃"); break;
		case 2:printf("\n   気高き光槍に貫けるものはない。\n   相手の防御を無視した攻撃！"); break;
		case 3:printf("\n   全てを救う光、人はそれを奇跡と呼ぶ。\n   防御が上昇し、毎ターン持続回復効果付与！"); break;
		}
	}
	if (ep == 9)	//闇属性
	{
		textcolor(LIGHTMAGENTA);
		switch (sp)
		{
		case 1:printf("\n   終焉にゆらめく怪光、その名もシャレム。\n   攻撃と防御を代償に強力な一撃"); break;
		case 2:printf("\n   黑き歯車は生き血を呑み込み加速する＿＿。\n   体力を犠牲にし、攻撃と防御を大きく上昇"); break;
		case 3:printf("\n   「奪う」、それが闇の神髄なり。\n   相手の防御を奪い取り、自分の攻撃力を上昇！"); break;
		}
	}

	textcolor(WHITE);




	getch();

	system("cls");

	notsaved = 1;	//セーブ未実施を示す

	return notsaved;	//メニュー(main)へ戻る
}