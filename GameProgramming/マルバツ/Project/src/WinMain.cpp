
// ==============================
// 2020年 前期 
// ゲームプログラミング１
// 制作課題 その２
// ==============================

/**
■説明
	以下のプログラムは [ 〇×(三目並べ) ] というゲームをコーディングし、
	実行を確認したうえでその一部分を削除したものです。

	削除した部分は　※※　と記載し、
	本来入るべき処理の内容をコメントしてあります。

	コメント内容や他のコードを読み解き、ゲームを完成させなさい。

	※Hit And Blowに比べてコメントのヒントが少ないので
	　どのような処理を書けばよいか良く考えましょう
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
■〇×(三目並べ)のルール
	ルールについては、自分で調べて把握するようにしてください
*/

#include "WinMain.h"
#include "InputManager.h"
#include "DrawManager.h"
#include <stdio.h>
#include <time.h>

// ==============================
// グローバル変数
// ==============================
int map[STAGE_WIDTH][STAGE_HEIGHT];		// 横:STAGE_WIDTH、縦:STAGE_HEIGHTのint型２次元配列 map を宣言

// ==============================
// 関数プロトタイプ宣言
// ==============================
// 盤面の x, y の位置に石が置けるかどうか
bool IsPutStone(int x, int y); // bool型の戻り値、int型の引数x,yを持つIsPutStone関数を宣言
// 勝者が居るかを調べる
int CheckWinner(int stone); // int型の戻り値を持つCheckWinner関数を宣言

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
	SetMainWindowText("マルバツ");
	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	// ローカル変数宣言
	// ----------------------------------------------------
	int pos_x = 0;		// X座標選択位置
	int pos_y = 0;		// Y座標選択位置
	int turn = STONE_WHITE;	// 現在の手番
	int winner = WINNER_NON;	// 勝利者

	int stone_Counter = 0;	// 石の数をカウントする

	// 各種初期化処理
	// ----------------------------------------------------
	InputInit();			// 入力処理初期化関数の呼び出し
	DrawInit();				// 描画処理初期化関数の呼び出し

	// mapの初期化
	for (int x = 0; x < STAGE_WIDTH; x++) {
		for (int y = 0; y < STAGE_HEIGHT; y++) {
			map[x][y] = STONE_MAX;
		}
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
		InputUpdate();			// 入力処理更新関数の呼び出し
		// 勝利者のチェック
		winner = CheckWinner(stone_Counter);


		// --- 入力状況をチェックして、適切な処理を行う
		// 決着がついてない時だけ入力を受け付けるように if文 でチェックする
		if( winner == WINNER_NON )
		{
			// 上下左右の入力があった時の処理
			// 盤面の外にはカーソル移動できない
			if( IsPushKey(MY_INPUT_DOWN) == true )
			{
				if (pos_y < 2) {
					pos_y += 1;
				}
			}
			else if( IsPushKey(MY_INPUT_UP) == true )
			{
				if (pos_y > 0) {
					pos_y -= 1;
				}
			}
			else if( IsPushKey(MY_INPUT_LEFT) == true )
			{
				if (pos_x > 0) {
					pos_x -= 1;
				}
			}
			else if( IsPushKey(MY_INPUT_RIGHT) == true )
			{
				if (pos_x < 2) {
					pos_x += 1;
				}
			}
			// 決定(=エンターキー)が押された時の処理
			else if( IsPushKey(MY_INPUT_ENTER) == true )
			{
				// 現在の座標が有効か if文 でチェックし、
				// 結果が true の時、以下の処理を行う
				if ( IsPutStone(pos_x, pos_y) == true )
				{
					// 選択されている座標と対応するmap配列の要素へturnの値を代入
					map[pos_x][pos_y] = turn;
					// 次のターンに回すため、turnの値を変更する
					turn = (turn + 1) % 2;

					// 石の数をカウント
					stone_Counter += 1;
				}
			}
		}

		// 以下、描画処理
		// ----------------------------------------------------
		DrawInformation(turn); // 情報文章を描画
		DrawGameClear(winner); // ゲームクリアの文字を描画
		DrawBgLine(); // 枠線を描画
		//２重for文を使って盤面の石を描画する
		for (int x = 0; x < STAGE_HEIGHT; x++) {
			for (int y = 0; y < STAGE_WIDTH; y++) {
				DrawStone(x, y, map[x][y]);
			}
		}
		DrawCursor(pos_x, pos_y); //カーソルを描画

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
// 盤面の x, y の位置に石が置けるかどうか
// true = 置ける
// false = 置けない
// ==============================
bool IsPutStone( int x, int y )
{
	
	//※※　盤面の x, y の位置に石が置けるならtrue,置けないならfalseを返す処理
	if (map[x][y] == STONE_MAX) {
		return true;
	}
	else {
		return false;
	}
}

// ==============================
// 勝者が居るかを調べる
// ==============================
int CheckWinner(int stone)
{
	// 縦、横、斜めが同じ石かどうかを調べる
	int stdTemp = 0;

	/*
	 
	 x-y
	-------------
	|0-0|1-0|2-0|
	-------------
	|0-1|1-1|2-1|
	-------------
	|0-2|1-2|2-2|
	-------------
	
	*/
	
	stdTemp = map[1][1]; // map[1][1]は盤面の中心　これを基準に調べる

	if (stdTemp != STONE_MAX) {
		if (stdTemp == map[1][0]) {
			if (stdTemp == map[1][2]) {
				return stdTemp;
			}
		}
		if (stdTemp == map[0][0]) {
			if (stdTemp == map[2][2]) {
				return stdTemp;
			}
		}
		if (stdTemp == map[0][1]) {
			if (stdTemp == map[2][1]) {
				return stdTemp;
			}
		}
		if (stdTemp == map[0][2]) {
			if (stdTemp == map[2][0]) {
				return stdTemp;
			}
		}
	}

	stdTemp = map[0][2]; // map[0][2]は盤面の左下　つぎの基準にする

	if (stdTemp != STONE_MAX) {
		if (stdTemp == map[0][1]) {
			if (stdTemp == map[0][0]) {
				return stdTemp;
			}
		}
		if (stdTemp == map[1][2]) {
			if (stdTemp == map[2][2]) {
				return stdTemp;
			}
		}
	}

	stdTemp = map[2][0]; // map[2][0]は盤面の右上　最後の基準にする

	if (stdTemp != STONE_MAX) {
		if (stdTemp == map[1][0]) {
			if (stdTemp == map[0][0]) {
				return stdTemp;
			}
		}
		if (stdTemp == map[2][1]) {
			if (stdTemp == map[2][2]) {
				return stdTemp;
			}
		}
	}

	// もし、まだ揃っていなかったら、盤面に置かれている石の数を調べる
	// 全てのマスに石が置かれていたら引き分け
	if (stone >= (STAGE_WIDTH * STAGE_HEIGHT)) {
		return STONE_MAX;
	}
	
	// 上記のいずれかでも無かったらWINNER_NONを返す
	return WINNER_NON;
}
