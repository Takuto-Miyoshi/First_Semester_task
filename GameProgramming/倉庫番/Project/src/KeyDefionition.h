#pragma once

#include "DxLib.h"

// ================================================================================
// キー定義
// ================================================================================

// キー種類
#define MY_INPUT_UP		0	// 上キー
#define MY_INPUT_DOWN	1	// 下キー
#define MY_INPUT_LEFT	2	// 左キー
#define MY_INPUT_RIGHT	3	// 右キー
#define MY_INPUT_RESET	4	// リセットボタン
#define MY_INPUT_MAX	5	// 入力キーの最大数

#define MY_INPUT_START	MY_INPUT_UP
#define MY_INPUT_END	MY_INPUT_MAX

// キーアサイン
const int KEY_ASSIGN[MY_INPUT_MAX]
{
	KEY_INPUT_UP,		// MY_INPUT_UP
	KEY_INPUT_DOWN,		// MY_INPUT_DOWN
	KEY_INPUT_LEFT,		// MY_INPUT_LEFT
	KEY_INPUT_RIGHT,	// MY_INPUT_RIGHT
	KEY_INPUT_R,		// MY_INPUT_RESET
};
