#pragma once

// ================================================================================
// 描画処理関数群
// ================================================================================
void DrawInit();	// 描画処理初期化 (ゲーム起動時に一度だけ呼び出す)
void DrawEnd();		// 描画処理終了　 (ゲーム終了時、DxLib_Endの前に一度だけ呼び出す)

void DrawInformation();									// 情報文章を描画
void DrawGameClear();									// ゲームクリアの文字を描画
void DrawHint( int hit, int blow, int count );			// Hit, Blow, 入力回数を描画
void DrawNum( int* array, int digit );					// 入力数字を描画
void DrawCursor( int cursor, bool isValid, int digit );	// カーソルを描画
