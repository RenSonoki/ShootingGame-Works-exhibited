#include "Game.h"
#include "TitleScene.h"
#include "ModelFactory.h"


// コンストラクタ
Game::Game(int playerModel, int enemyModel)
{
    // タイトルシーンを初期化し、現在のシーンとして設定
    currentScene = std::make_unique<TitleScene>(playerModel, enemyModel);
}


void Game::Update()
{
    if (currentScene)
    {
        // ゲームの状態を更新
        currentScene->Update(*this);
    }
}

// ゲームの描画処理
void Game::Draw()
{
    if (currentScene)
    {
        // 現在のシーンのDrawメソッドを呼び出し、ゲームを画面に描画
        currentScene->Draw();
    }
}

// シーンの変更処理
void Game::ChangeScene(std::unique_ptr<Scene> newScene)
{
    // 現在のシーンを新しいシーンに置き換える（std::moveで所有権を移動）
	// std::moveとは、所有権を移動するための関数で、リソースの効率的な管理を可能にします。
    currentScene = std::move(newScene);
}