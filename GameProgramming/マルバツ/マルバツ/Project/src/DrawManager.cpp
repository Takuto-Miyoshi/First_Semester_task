
#include "DxLib.h"
#include "WinMain.h"
#include "DrawManager.h"


#define CELLSIZE			100		// １マスのサイズ
#define CURSORSIZE			96		// カーソルのサイズ
#define CIRCLE_R			48		// プレイヤー円の半径

#define DRAW_OFFSET_X		10		// 描画オフセットＸ
#define DRAW_OFFSET_Y		60		// 描画オフセットＹ

#define GAME_AREA_WIDTH		(STAGE_WIDTH * CELLSIZE)	// ゲームエリア幅
#define GAME_AREA_HEIGHT	(STAGE_HEIGHT * CELLSIZE)	// ゲームエリア高さ


// ================================================================================
// 描画処理初期化 (ゲーム起動時に一度だけ呼び出す)
// ================================================================================
void DrawInit()
{
}

// ================================================================================
// 描画処理終了　 (ゲーム終了時、DxLib_Endの前に一度だけ呼び出す)
// ================================================================================
void DrawEnd()
{
}

// ================================================================================
// 情報文章を描画
// truen = 現在の手番
// ================================================================================
void DrawInformation( int turn )
{
	DrawString( 10, 10, "縦、横、斜めに石を揃えよう！", GetColor(0,0,0) );

	DrawString( 10, 380, "操作方法", GetColor(80,80,80) );
	DrawString( 10, 400, "↑↓←→　：カーソル移動", GetColor(80,80,80) );
	DrawString( 10, 420, "ＥＮＴＥＲ：石を置く", GetColor(80,80,80) );
}

// ================================================================================
// ゲームクリアの文字を描画
// ================================================================================
void DrawGameClear( int winner )
{
	int left   = DRAW_OFFSET_X + 400;
	int top    = DRAW_OFFSET_Y;
	int center_x = left + int(CELLSIZE * 0.5);
	int center_y = top + 20 + int(CELLSIZE * 0.5);

	switch( winner )
	{
	case WINNER_WHITE:
		DrawString(left + 20, top, "Winner", GetColor(0,255,0) );
		DrawCircle(center_x, center_y, CIRCLE_R, GetColor(0xFF, 0xFF, 0xFF), TRUE);
		break;

	case WINNER_BLACK:
		DrawString(left + 20, top, "Winner", GetColor(0,0,0) );
		DrawCircle(center_x, center_y, CIRCLE_R, GetColor(0x00, 0x00, 0x00), TRUE);
		break;

	case WINNER_DRAW:
		DrawString( left, top, "引き分け！", GetColor(80,80,80) );
		break;
	}
}

// ================================================================================
// 枠線を描画
// ================================================================================
void DrawBgLine()
{
	const int left   = DRAW_OFFSET_X-1;
	const int top    = DRAW_OFFSET_Y-1;
	const int right  = left + GAME_AREA_WIDTH  + 1;
	const int bottom = top  + GAME_AREA_HEIGHT + 1;

	// 外枠
	DrawLine( left,  top,    right, top,    GetColor( 0xFF, 0xFF, 0xFF) );
	DrawLine( right, top,    right, bottom, GetColor( 0xFF, 0xFF, 0xFF) );
	DrawLine( right, bottom, left,  bottom, GetColor( 0xFF, 0xFF, 0xFF) );
	DrawLine( left,  bottom, left,  top,    GetColor( 0xFF, 0xFF, 0xFF) );

	// 内枠
	DrawLine(left + ((GAME_AREA_WIDTH / 3) * 1), top, left + ((GAME_AREA_WIDTH / 3) * 1), bottom, GetColor(0xFF, 0xFF, 0xFF));
	DrawLine(left + ((GAME_AREA_WIDTH / 3) * 2), top, left + ((GAME_AREA_WIDTH / 3) * 2), bottom, GetColor(0xFF, 0xFF, 0xFF));
	DrawLine(left, top + ((GAME_AREA_HEIGHT / 3) * 1), right, top + ((GAME_AREA_HEIGHT / 3) * 1), GetColor(0xFF, 0xFF, 0xFF));
	DrawLine(left, top + ((GAME_AREA_HEIGHT / 3) * 2), right, top + ((GAME_AREA_HEIGHT / 3) * 2), GetColor(0xFF, 0xFF, 0xFF));
}

// ================================================================================
// 盤面のマス(x, y)に石を描画
// x = マスの x座標
// y = マスの y座標
// stone = 配置する石の値
// ================================================================================
void DrawStone( int x, int y, int stone )
{
	const int center_x = DRAW_OFFSET_X + (x * CELLSIZE) + int(CELLSIZE * 0.5);
	const int center_y = DRAW_OFFSET_Y + (y * CELLSIZE) + int(CELLSIZE * 0.5);
	switch( stone )
	{
	case STONE_WHITE:
		DrawCircle(center_x, center_y, CIRCLE_R, GetColor(0xFF, 0xFF, 0xFF), TRUE);
		break;

	case STONE_BLACK:
		DrawCircle(center_x, center_y, CIRCLE_R, GetColor(0x00, 0x00, 0x00), TRUE);
		break;
	}
}

// ================================================================================
// カーソルを描画
// x = マスの x座標
// y = マスの y座標
// ================================================================================
void DrawCursor( int x, int y )
{
	const int left		= DRAW_OFFSET_X + (x * CELLSIZE) + int((CELLSIZE - CURSORSIZE)*0.5);
	const int top		= DRAW_OFFSET_Y + (y * CELLSIZE) + int((CELLSIZE - CURSORSIZE)*0.5);
	DrawBox( left, top, left+ CURSORSIZE, top+ CURSORSIZE, GetColor( 0xFF, 0x00, 0x00), FALSE );
}
