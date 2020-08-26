#pragma once

#include "DxLib.h"

// ==============================
// 定数定義
// ==============================
#define WINDOW_W	640
#define WINDOW_H	480

// 盤面のマス数
#define STAGE_WIDTH  3	// 横のマス数
#define STAGE_HEIGHT 3	// 縦のマス数

// ゲームの白石、黒石
#define STONE_WHITE	0
#define STONE_BLACK	1
#define STONE_MAX	2

// 勝敗を管理する数値
#define WINNER_WHITE	0	// 白石の勝ち
#define WINNER_BLACK	1	// 黒石の勝ち
#define WINNER_DRAW		2	// 引き分け
#define WINNER_NON		-1	// 勝者なし(未決着)
