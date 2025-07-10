#include "DxLib.h"
#include "Game.h"
#include "ModelFactory.h"
#include "VirtualScreenManager.h"
#include <ctime>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ログ出力無効化
    SetOutApplicationLogValidFlag(FALSE);

    // 仮想画面の想定サイズ
    const int VIRTUAL_WIDTH = 1280;
    const int VIRTUAL_HEIGHT = 720;

    // 解像度を仮想画面と同じにして初期化
    SetGraphMode(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, 32);

	// 各種設定
    ChangeWindowMode(TRUE);             // ウィンドウモード（任意）
    SetUseZBuffer3D(TRUE);              // Zバッファ有効（3D用）
    SetWriteZBuffer3D(TRUE);            // 書き込み有効
	SetDrawScreen(DX_SCREEN_BACK);      // 描画先をバックバッファへ
	SetBackgroundColor(0, 255, 255);    // 背景色を青緑色に設定
    DxLib_Init();

    // 乱数初期化
	// 使用先-> Game.cpp (敵のランダム生成など)
    srand(static_cast<unsigned int>(time(NULL)));

    // モデルの読み込み
    int playerModel = ModelFactory::Instance().GetModel("Assets/Models/player.mv1");
    int enemyModel  = ModelFactory::Instance().GetModel("Assets/Models/enemy.pmx");

    // ゲームインスタンス生成
	// シーン遷移やゲームの状態管理を行う
    Game game(playerModel, enemyModel);

    // 仮想画面初期化（Zバッファ付き）
    VirtualScreenManager::Init(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

    // メインループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // 仮想画面に描画開始（描画先を仮想画面に + 完全初期化）
        VirtualScreenManager::BeginDraw();

        // ゲーム更新・描画（仮想画面内で行われる）
        game.Update();
        game.Draw();

        // 仮想画面 → 実画面にスケーリング描画
        VirtualScreenManager::EndDraw();

        // 裏画面 → 表画面へ反映
		// ここで仮想画面の内容を実画面にスケーリングして表示
        ScreenFlip();
    }

    // モデル解放
    ModelFactory::Instance().Clear();

    // DxLib終了
    DxLib_End();
    return 0;
}