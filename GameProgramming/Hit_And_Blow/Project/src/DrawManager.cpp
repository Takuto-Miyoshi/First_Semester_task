
#include "DxLib.h"
#include "WinMain.h"
#include "DrawManager.h"

/**
■画像について
	０から９それぞれのサイズは 横:84, 縦:99 です
*/

// ================================================================================
// グローバル関数
// ================================================================================
int numberGraphHandle = -1;		// 数字画像を使うための変数
int clearGraphHandle = -1;		// クリア画像を使うための変数


// ================================================================================
// 描画処理初期化 (ゲーム起動時に一度だけ呼び出す)
// ================================================================================
void DrawInit()
{
	numberGraphHandle = LoadGraph( "data/Number.png" );
	clearGraphHandle = LoadGraph( "data/Clear.png" );
}

// ================================================================================
// 描画処理終了　 (ゲーム終了時、DxLib_Endの前に一度だけ呼び出す)
// ================================================================================
void DrawEnd()
{
	DeleteGraph(numberGraphHandle);
	DeleteGraph(clearGraphHandle);
}

// ================================================================================
// 情報文章を描画
// ================================================================================
void DrawInformation()
{
	DrawString( 10, 10, "Hit と Blow をヒントに、正解の数字を当てよう！", GetColor(0,0,0) );

	DrawString( 10, 280, "操作方法", GetColor(80,80,80) );
	DrawString( 10, 300, "←→　　　：カーソル移動", GetColor(80,80,80) );
	DrawString( 10, 320, "↑↓　　　：数字の変更", GetColor(80,80,80) );
	DrawString( 10, 340, "ＥＮＴＥＲ：答えを合わせる", GetColor(80,80,80) );
}

// ================================================================================
// ゲームクリアの文字を描画
// ================================================================================
void DrawGameClear()
{
	DrawGraph( (WINDOW_W / 2) - 160, (WINDOW_H / 2) - 160, clearGraphHandle, TRUE );
}

// ================================================================================
// Hit, Blowを描画
// hit  = ヒットしている数
// blow = ブローしている数
// count = 今までの入力回数
// ================================================================================
void DrawHint( int hit, int blow, int count )
{
	DrawFormatString( 10, 40, GetColor(0,0,0), "Hit  = %d", hit );
	DrawFormatString( 10, 60, GetColor(0,0,0), "Blow = %d", blow );
	DrawFormatString( 10, 80, GetColor(0,0,0), "入力 = %d回", count );
}

// ================================================================================
// 入力数字を描画
// array = 配列の先頭アドレス
// digit = 配列の数(=桁数)
// ================================================================================
void DrawNum( int* array, int digit )
{
	if( array == NULL || digit < 0 )
	{
		return;
	}

	int left = (WINDOW_W / 2) - ((digit * 84) / 2);
	int top  = (WINDOW_H / 2) - (99 / 2);

	for( int i=0; i < digit; i++ )
	{
		int x = left + (84 * i);
		int y = top;
		DrawRectGraph( x, y, 84 * array[i], 0, 84, 99, numberGraphHandle, TRUE );
	}
}

// ================================================================================
// カーソルを描画
// cursor = 現在のカーソル位置
// isValid = 入力されている数字が有効か
// digit = 桁数
// ================================================================================
void DrawCursor( int cursor, bool isValid, int digit )
{
	int left = (WINDOW_W / 2) - ((digit * 84) / 2);
	int top  = (WINDOW_H / 2) - (99 / 2);

	int x = left + (84 * cursor);
	int y = top;

	DrawBox( x, y, x + 84, y + 99, GetColor(255,0,0), FALSE );
	if( isValid == false )
	{
		DrawString( 10, 100, "重複している数字があります", GetColor(255,0,0) );
	}
}

