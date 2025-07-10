#include "VirtualScreenManager.h"
#include "DxLib.h"

// 仮想画面サイズとそのハンドルの静的変数定義
// ※初期値は1280x720の仮想画面を想定
int VirtualScreenManager::s_virtualWidth = 1280;
int VirtualScreenManager::s_virtualHeight = 720;
int VirtualScreenManager::s_virtualScreenHandle = -1;

// 仮想画面の初期化（解像度とバッファを生成）
void VirtualScreenManager::Init(int virtualW, int virtualH)
{
    s_virtualWidth = virtualW;
    s_virtualHeight = virtualH;

    // 仮想画面を作成（Zバッファ付き＝TRUE）
    // 3D描画に必要な深度バッファも含めて生成
    s_virtualScreenHandle = MakeScreen(virtualW, virtualH, TRUE);
}

// 描画開始処理（仮想画面への描画設定）
void VirtualScreenManager::BeginDraw()
{
    // 描画先を仮想画面に切り替え
    SetDrawScreen(s_virtualScreenHandle);

    // 色バッファのクリア（前フレームの残像を消去）
    ClearDrawScreen();

    // Zバッファの完全な初期化を行うため、画面全体に塗りつぶし描画を実施
    // ※DxLibの ClearDrawScreen() ではZバッファが完全にクリアされない場合がある為
    DrawBox(0, 0, s_virtualWidth, s_virtualHeight, GetColor(0, 255, 255), TRUE);
}

// 描画終了処理（仮想画面→実ウィンドウ画面へ転送）
void VirtualScreenManager::EndDraw()
{
	int windowW, windowH;               // 実画面のサイズを取得
	GetWindowSize(&windowW, &windowH);  // ウィンドウの幅と高さを取得

    // 実画面（バックバッファ）へ戻す
    SetDrawScreen(DX_SCREEN_BACK);

    // 仮想画面の内容を、ウィンドウサイズにスケーリングして描画
	// DXLibの DrawExtendGraph() を使用
    DrawExtendGraph
    (
		0                           // 描画開始X座標
		, 0                         // 描画開始Y座標
		, windowW                   // 実画面の幅
		, windowH                   // 実画面の高さ
		, s_virtualScreenHandle     // 仮想画面のハンドル
        ,TRUE                       // 透過有効（アルファ含む）
    );
}

// 現在の仮想画面の幅を取得
int VirtualScreenManager::GetVirtualWidth() { return s_virtualWidth; }

// 現在の仮想画面の高さを取得
int VirtualScreenManager::GetVirtualHeight() { return s_virtualHeight; }

// 実画面上のマウス座標を、仮想画面上の座標に変換して返す
// 将来的にマウス仕様の変更に対応するため
POINT VirtualScreenManager::ConvertMousePositionToVirtual()
{
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    int windowW, windowH;
    GetWindowSize(&windowW, &windowH);

    POINT result;

    // 仮想画面のスケーリング比率に基づいて座標変換
    result.x = static_cast<LONG>(mouseX * s_virtualWidth / static_cast<float>(windowW));
    result.y = static_cast<LONG>(mouseY * s_virtualHeight / static_cast<float>(windowH));

    return result;
}