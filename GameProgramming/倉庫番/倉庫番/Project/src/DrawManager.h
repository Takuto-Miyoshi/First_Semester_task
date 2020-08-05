#pragma once

// ================================================================================
// 描画処理関数群
// ================================================================================
void DrawInit();		// 描画処理初期化 (ゲーム起動時に一度だけ呼び出す)
bool InitSuccessed();	// 初期化が成功したか
void DrawEnd();			// 描画処理終了　 (ゲーム終了時、DxLib_Endの前に一度だけ呼び出す)

void DrawObject( int x, int y, int type );				// ゲームの配置物を描画
void DrawPlayer( int x, int y, int dir, int animeNo );	// プレイヤーを描画
void DrawGameClear();									// ゲームクリアの文字を描画
