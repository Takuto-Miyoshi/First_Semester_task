// ==============================
// 2020年 前期 
// ゲームプログラミング１
// 制作課題 その１
// ==============================

/**
■説明
	以下のプログラムは [ Hit And Blow ] というゲームをコーディングし、
	実行を確認したうえで、その一部分を削除したものです。

	削除した部分は　※※　と記載し、
	本来入るべき処理の内容をコメントしてあります。

	コメント内容や他のコードを読み解き、ゲームを完成させなさい。
 */

/**
■制作環境
	このプログラムは、[ ＤＸライブラリ ] というライブラリを用いて作られています。
		ホームページ：https://dxlib.xsrv.jp/
		リファレンス：https://dxlib.xsrv.jp/dxfunc.html

	ＤＸライブラリについて興味のある人は、
	ホームページ、リファレンスページ（用意されている関数の説明）を見てみてください。
*/

/**
■Hit And Blowのルール
	ルールについては、自分で調べて把握するようにしてください

	オンライン上で遊べるサイトもありますので、
	実際に遊んでみるのもよいでしょう
*/

/*
追加でできること
・DXライブラリのリファレンスや、ソースコードを見ながら背景の表示を行ってみる
・グローバル変数になっている部分をローカル変数でも動くように改造する
・バグがないか、ブレイクポイントなどを使ってチェックする
*/

#include "WinMain.h"
#include "InputManager.h"
#include "DrawManager.h"
#include <stdio.h>
#include <time.h>

// ==============================
// 定数定義
// ==============================
const int DIGITS = 4;
//※※　DIGITSという名前の定数or定義で値は４	// 問題の桁数

// ==============================
// グローバル変数
// ==============================

//※※　整数型の変数count					// 推測回数	
int count;

//※※　整数型の変数cursor					// 選択カーソル
int cursor;

//※※　整数型、配列の要素数DIGITSのtarget	// 目標数の保存配列
int target[DIGITS];

//※※　整数型、配列の要素数DIGITSのnum	// 推測数の保存配列
int num[DIGITS];

// ==============================
// 関数プロトタイプ宣言
// ==============================
// 問題となるDIGITS桁の数字を作成する
void CreateTargetNumber();

// 入力された数字が有効かどうか調べる
bool IsValidNumber();
// 入力された数字の、特定の桁が正しいか調べる
bool IsValidDigit( int digit );
// 入力された値のHit数、Blow数をチェックする
bool IsMatch(int* numHit, int* numBlow);

// ==============================
// Main関数
// ==============================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ＤＸライブラリを使う上での初期化処理
	// ----------------------------------------------------
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_W, WINDOW_H, 32);
	SetBackgroundColor(125, 125, 255);
	SetMainWindowText("Hit and Blow");
	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	// ローカル変数宣言
	// ----------------------------------------------------
	
	//※※　整数型の変数hitを宣言し、0で初期化
	int hit = 0;
	
	//※※　整数型の変数blowを宣言し、0で初期化
	int blow = 0;
	
	//※※　bool型の変数gameClearを宣言し、falseで初期化(trueでゲームクリア)
	bool gameClear = false;

	// 各種初期化処理
	// ----------------------------------------------------
	InputInit();			// 入力処理初期化関数の呼び出し
	DrawInit();				// 描画処理初期化関数の呼び出し
	CreateTargetNumber(); // 問題となる数字の作成

	
	//※※　// countを０で初期化
	count = 0;
		
	//※※　// cursorを０で初期化
	cursor = 0;
	
	//※※　// 配列 num を for文 で初期化
	for (int i = 0; i < DIGITS; i++) {
		num[i] = i;
	}
	

	// ゲームのメインループ
	// 画面を１回表示する毎にwhile分を１回処理する
	// ----------------------------------------------------
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ＤＸライブラリを使う上で、１フレーム分の処理を始めるためのお約束
		// ----------------------------------------------------
		ClearDrawScreen();
		clsDx();

		// 以下、毎フレーム更新する処理
		// ----------------------------------------------------
		InputUpdate();	// 入力処理更新関数の呼び出し

		// --- 入力状況をチェックして、適切な処理を行う
		// ゲームクリアしていない時だけ入力を受け付けるように if文 でチェックする
		if( gameClear == false )
		{
			if(IsPushKey(MY_INPUT_UP))
			{
				//※※	// num配列のcursor番目を 1 増やす
					// 増やした結果、9 より大きくなった場合は、0にする
				num[cursor] = (num[cursor] + 1) % 10;
			}
			else if(IsPushKey(MY_INPUT_DOWN))
			{
				//※※	// num配列のcursor番目を 1 減らす
					// 減らした結果、0 より小さくなった場合は、9にする
				num[cursor]--;
				if (num[cursor] <= 0) {
					num[cursor] = 9;
				}
			}
			else if(IsPushKey(MY_INPUT_LEFT))
			{
				//※※	// cursorを 1 減らす
					// 減らした結果、0 より小さくなった場合は、0にする
				cursor--;
				if (cursor <= 0) {
					cursor = 0;
				}
			}
			else if(IsPushKey(MY_INPUT_RIGHT))
			{
				//※※	// cursorを 1 増やす
						// 増やした結果、(DIGITS - 1) より大きくなった場合は、(DIGITS - 1)にする
				cursor++;
				if (cursor >= DIGITS - 1) {
					cursor = DIGITS - 1;
				}
			}
			else if(IsPushKey(MY_INPUT_ENTER))
			{
				// 入力した数字が有効か if文 でチェックする
				if( IsValidNumber() == true )
				{
					// チェックした結果が true の時、以下の処理を行う
					// hit, blowの数をチェックし、その返り値を gameClear に代入
					gameClear = IsMatch(&hit, &blow);
					// 入力回数 count を 1増やす
					count++;
				}
			}
		}

		// 以下、描画処理
		// ----------------------------------------------------
		DrawInformation();
		DrawHint( hit, blow, count );
		DrawNum( num, DIGITS );
		DrawCursor( cursor, IsValidNumber(), DIGITS );

		// ゲームクリアしていれば、追加で描画
		if( gameClear == true )
		{
			DrawGameClear();
		}

		// ＤＸライブラリを使う上で、モニターへゲーム画面を表示するためのお約束
		// 必ずループの最後で呼び出す
		// ----------------------------------------------------
		ScreenFlip();
	}

	// 後始末
	// ----------------------------------------------------
	DrawEnd();		// 描画処理終了

	// ＤＸライブラリを使う上での終了処理
	// ----------------------------------------------------
	DxLib_End();
	return 0;
}

// ==============================
// 問題となるDIGITS桁の数字を作成する
// ==============================
void CreateTargetNumber()
{
	//※※		// 乱数をtime()関数で初期化
	srand((unsigned)time(NULL));

	// 0 から DIGITS より小さい間繰り返す for文
	// ループカウンタの変数名は i とする
	for( int i = 0; i < DIGITS; i++ ){
		target[i] = 0;

		bool isValid;
		do {
			//※※		// 現在の要素へ、乱数値を代入
			target[i] = rand() % 9;

			//※※
			// 以下の処理を行う
			// 同じ数字がないかをチェック
			// 今回の数字が無効な値だったら isValid を false に
			// 有効な値だったら isValid を true にする
			for (int j = 0; j < DIGITS; j++) {
				if (target[j] == target[i] && i != j) {
					isValid = false;
					break;
				}
				isValid = true;
			}
		} while( isValid == false );
	}
}

// ==============================
// 入力された数字が有効かどうか調べる
// 有効(重複していない)であれば true, 無効であれば false を返す
// ==============================
bool IsValidNumber()
{
	// 0 から DIGITS より小さい間繰り返す for文
	// ループカウンタの変数名は i とする
	for( int i = 0; i < DIGITS; i++ ){
		// i 番目の桁が無効だったら false を返す
		for (int j = i + 1; j < DIGITS; j++) {
			if (num[i] == num[j] && i != j) {
				return false;
			}
		}
	}
	return true;
}

// ==============================
// 入力された数字の、特定の桁が有効か調べる
// 有効(重複していない)であれば true, 無効であれば false を返す
// ==============================
bool IsValidDigit( int digit )
{
	if( digit < 0 || digit >= DIGITS )
	{
		return false;
	}

	// 0 から DIGITS より小さい間繰り返す for文
	// ループカウンタの変数名は i とする
	for( int i = 0; i < DIGITS; i++ ){
		if (digit == i) {
			continue; // 条件に合う場合は以下の処理をスキップする
		}

		if (num[digit] == num[i]) {
			return false;
		}
		// 以下の処理を行う
		// digit と i が同じ場合は調べる必要がないので continue する
		// num配列の digit 番目と i 番目を比較し、
		// 同じだったら重複しているということなので false を返す
	}

	return true; // for文を抜けたら重複がないということなので true を返す
}

// ==============================
// 入力された値のHit数、Blow数をチェックする
// 正解(完全一致)した場合は true, そうでない場合は false を返す
// ==============================
bool IsMatch(int* numHit, int* numBlow)
{
	*numHit = 0;
	*numBlow = 0;
	// numHit と numBlow が指すアドレスの中身を 0 で初期化する

	for(int i = 0; i < DIGITS; i++)
	{
		for(int j = 0; j < DIGITS; j++)
		{
			//※※
			// target の i 番目、 num の j 番目が同じか調べる
			if( target[i] == num[j] )
			{
				// 当てるべき数が num に入っていることが分かったので、Hit か Blow かを調べる

				if (target[i] == num[i]) {
					*numHit += 1;
				}
				else {
					*numBlow += 1;
				}
				// 配列の同じ位置にある場合は numHit のアドレスの中身を 1 増やす
				// そうでない場合は numBlow のアドレスの中身を 1 増やす
			}
		}
	}
	return (*numHit == DIGITS);
}
