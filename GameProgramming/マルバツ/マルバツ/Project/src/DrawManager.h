#pragma once

// ================================================================================
// 描画処理関数群
// ================================================================================
void DrawInit();	// 描画処理初期化 (ゲーム起動時に一度だけ呼び出す)
void DrawEnd();		// 描画処理終了　 (ゲーム終了時、DxLib_Endの前に一度だけ呼び出す)

void DrawInformation( int turn );			// 情報文章を描画
void DrawGameClear( int winner );			// ゲームクリアの文字を描画
void DrawBgLine();							// 枠線を描画
void DrawStone( int x, int y, int stone );	// 盤面のマス(x, y)に石を描画
void DrawCursor( int x, int y );			// カーソルを描画
