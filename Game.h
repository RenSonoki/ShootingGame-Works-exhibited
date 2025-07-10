#pragma once
#include <memory>      // スマートポインタ（std::unique_ptr）を使用するためのヘッダーファイル
#include "Scene.h"

// ゲームを管理するクラス
class Game
{
public:
    // コンストラクタ
    Game(int playerModel, int enemyModel);

    // ゲームの更新処理：プレイヤーや敵の動き、状態を更新
    void Update();

    // ゲームの描画処理：画面に描画を行う
    void Draw();

    // シーンの変更処理：現在のシーンを新しいシーンに切り替える
    void ChangeScene(std::unique_ptr<Scene> newScene);

private:
    // 現在のシーンを保持するスマートポインタ（動的メモリ管理を自動で行う）
    std::unique_ptr<Scene> currentScene;

    // Tips
	// unique_ptrは所有権を持つスマートポインタで、
    // 動的に確保したメモリを自動で解放するため、メモリリークを防ぐことができる
	// std::make_uniqueを使用すると、例外安全で効率的にオブジェクトを生成できる
	//      注)いつも使っていないので重点的におさらい
};