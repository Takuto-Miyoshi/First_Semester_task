
#include "DxLib.h"
#include "GameDefinition.h"
#include "DrawManager.h"

/**
■画像について
	それぞれのサイズは 横:32, 縦:32 です
*/


// ================================================================================
// グローバル関数
// ================================================================================
// 画像データハンドル
int PlayerGraphHandle[DIR_MAX][DIR_IMAGE_MAX];
int GroundGraphHandle;
int BlockGraphHandle;
int CrateGraphHandle[※※];		// クレートの種類最大数
int ClearGraphHandle;

// アニメーションのインデックス配列
int ANIME_IDX_ARRAY[PLAYER_ANIME_MAX] = { 0, 1, 0, 2 };


// ================================================================================
// 描画処理初期化 (ゲーム起動時に一度だけ呼び出す)
// ================================================================================
void DrawInit()
{
	// 画像ハンドルを保持する変数の初期化
	for( int i = 0; i < DIR_MAX; i++ )
	{
		for( int j = 0; j < DIR_IMAGE_MAX; j++ )
		{
			PlayerGraphHandle[i][j] = -1;
		}
	}
	GroundGraphHandle = -1;
	BlockGraphHandle = -1;
	for( int i = 0; i < ※※; i++ )
	{
		CrateGraphHandle[i] = -1;
	}
	ClearGraphHandle = -1;

	// 画像データ読み込み
	for( int i = 0; i < DIR_MAX; i++ )
	{
		for( int j = 0; j < DIR_IMAGE_MAX; j++ )
		{
			char str[256];
			sprintf_s( str, sizeof(str), "data/Player/player_%02d.png", (i * DIR_IMAGE_MAX) + j );
			PlayerGraphHandle[i][j] = LoadGraph( str );
		}
	}

	GroundGraphHandle = LoadGraph( "data/Ground/ground.png" );
	BlockGraphHandle = LoadGraph( "data/Ground/block.png" );
	for( int i = 0; i < ※※; i++ )
	{
		char str[256];
		sprintf_s( str, sizeof(str), "data/Crate/crate_%02d.png", i );
		CrateGraphHandle[i] = LoadGraph( str );
	}

	ClearGraphHandle = LoadGraph( "data/Clear.png" );
}

// ================================================================================
// 初期化が成功したか
// true = 成功
// false = 失敗
// ================================================================================
bool InitSuccessed()
{
	for( int i = 0; i < DIR_MAX; i++ )
	{
		for( int j = 0; j < DIR_IMAGE_MAX; j++ )
		{
			if( PlayerGraphHandle[i][j] == -1 )
			{
				return false;
			}
		}
	}

	if( GroundGraphHandle == -1)
	{
		return false;
	}

	if( BlockGraphHandle == -1)
	{
		return false;
	}

	for( int i = 0; i < ※※; i++ )
	{
		if( CrateGraphHandle[i] == -1)
		{
			return false;
		}
	}

	if( ClearGraphHandle == -1 )
	{
		return false;
	}

	return true;
}

// ================================================================================
// 描画処理終了　 (ゲーム終了時、DxLib_Endの前に一度だけ呼び出す)
// ================================================================================
void DrawEnd()
{
	for( int i = 0; i < DIR_MAX; i++ )
	{
		for( int j = 0; j < DIR_IMAGE_MAX; j++ )
		{
			DeleteGraph( PlayerGraphHandle[i][j] );
		}
	}
	DeleteGraph( GroundGraphHandle );
	DeleteGraph( BlockGraphHandle );
	for( int i = 0; i < ※※; i++ )
	{
		DeleteGraph( CrateGraphHandle[i] );
	}
}

// ================================================================================
// ゲームの配置物を描画　（プレイヤーはアニメーションをするため別関数）
// x = マスのx座標
// y = マスのy座標
// type = 配置物の種類
// ================================================================================
void DrawObject( int x, int y, int type )
{
	※※　コメントに合わせて描画処理をコーディング
	// マスの座標を、画面座標へ変換

	// 地面の描画

	// 配置物の描画
}

// ================================================================================
// プレイヤーを描画
// x = マスのx座標
// y = マスのy座標
// dir = プレイヤーの今の向き
// animeNo = 歩行パターン番号
// ================================================================================
void DrawPlayer( int x, int y, int dir, int animeNo )
{
	※※　描画処理をコーディング
	// まずは１つの画像を表示するだけを目指す
	// 最終的に、向いている方向の画像でアニメーションしていれば最高
}

// ================================================================================
// ゲームクリアの文字を描画
// ================================================================================
void DrawGameClear()
{
	DrawGraph( (WINDOW_W / 2) - 160, (WINDOW_H / 2) - 160, ClearGraphHandle, TRUE );
}
