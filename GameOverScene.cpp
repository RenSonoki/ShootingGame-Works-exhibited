#include "GameOverScene.h"
#include "DxLib.h"
#include "Game.h"
#include "TitleScene.h"
#include "ResourceManager.h"
#include "UIText.h"
#include "UISystem.h"
#include <tchar.h>

// コンストラクタ
GameOverScene::GameOverScene(int finalScore, int playerModel, int enemyModel)
    : m_score(finalScore)
    , m_playerModelHandle(playerModel)
    , m_enemyModelHandle(enemyModel)
{
    // 背景画像の読み込み
    m_backgroundHandle = ResourceManager::GetInstance().GetImage(L"Assets/UI/background_title.png");

    // BGM再生（必要に応じて）
    m_soundManager.Load();
    m_soundManager.PlayGameOver();

    // UI 初期化
    m_uiManager = std::make_unique<UIManager>();
    auto uiSystem = std::make_shared<UISystem>();

    // "GAME OVER" テキスト
    auto gameOverText = std::make_shared<UIText>(L"GAME OVER", GetColor(255, 0, 0));
    gameOverText->GetTransform().SetPosition({ 500, 250 });
    uiSystem->AddComponent(gameOverText);

    // スコア表示
	// 色：黒色
    auto scoreText = std::make_shared<UIText>(
        L"Final Score: " + std::to_wstring(m_score),
		GetColor(0, 0, 0)); // 黒色でスコアを表示
    scoreText->GetTransform().SetPosition({ 400, 300 });
    uiSystem->AddComponent(scoreText);

    // メッセージ表示
    auto promptText = std::make_shared<UIText>(L"Press ENTER to return to Title", GetColor(0,0,0));
    promptText->GetTransform().SetPosition({ 400, 350 });
    uiSystem->AddComponent(promptText);

    m_uiManager->AddSystem("gameOverUI", uiSystem);
}

// 更新処理
void GameOverScene::Update(Game& game)
{
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        m_soundManager.StopBGM();  // 音を止めて
        game.ChangeScene(std::make_unique<TitleScene>(m_playerModelHandle, m_enemyModelHandle));
    }
}

// 描画処理
void GameOverScene::Draw()
{
    int screenW = 1280;
    int screenH = 720;

    DrawExtendGraph(0, 0, screenW, screenH, m_backgroundHandle, TRUE);
    m_uiManager->DrawAll();
}

//#include "GameOverScene.h"
//#include "DxLib.h"        
//#include "Game.h"         
//#include "TitleScene.h"   
//#include <tchar.h>            // _T マクロを使用するためのヘッダーファイル
//
//// コンストラクタ
//GameOverScene::GameOverScene(int finalScore, int playerModel, int enemyModel)
//    : m_score(finalScore)
//    , m_playerModelHandle(playerModel)
//    , m_enemyModelHandle(enemyModel)
//{
//    // 最終スコアとモデルのハンドルを初期化
//}
//
//
//void GameOverScene::Update(Game& game)
//{
//    // Enterキーが押された場合、タイトルシーンに遷移
//    if (CheckHitKey(KEY_INPUT_RETURN))
//    {
//        // タイトルシーンに遷移（新しい TitleScene を生成してゲームのシーンを変更）
//        game.ChangeScene(std::make_unique<TitleScene>(m_playerModelHandle, m_enemyModelHandle));
//    }
//}
//
//
//void GameOverScene::Draw()
//{
//    // "GAME OVER" の文字列を赤色で表示
//    DrawString(500, 250, _T("GAME OVER"), GetColor(255, 0, 0));
//
//    // 最終スコアを白色で表示
//    DrawFormatString(480, 300, GetColor(255, 255, 255), _T("Final Score: %d"), m_score);
//
//    // "Press ENTER to return to Title" のメッセージを表示
//    DrawString(420, 350, _T("Press ENTER to return to Title"), GetColor(255, 255, 255));
//}
