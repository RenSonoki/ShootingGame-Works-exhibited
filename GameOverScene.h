#pragma once

#include "Scene.h"
#include "UIManager.h"
#include "SoundManager.h"
#include <memory>

// ゲームオーバー画面を表現するクラス
class GameOverScene : public Scene
{
private:
    // 最終スコア
    int m_score;

    // モデルハンドル（将来の拡張用）
    int m_playerModelHandle;
    int m_enemyModelHandle;

    // 背景画像
    int m_backgroundHandle;

    // UI
    std::unique_ptr<UIManager> m_uiManager;

    // サウンド
    SoundManager m_soundManager;

public:
    // コンストラクタ
    GameOverScene(int finalScore, int playerModel, int enemyModel);

    // 更新処理
    void Update(Game& game) override;

    // 描画処理
    void Draw() override;
};

//#pragma once
//#include "Scene.h"
//
//// ゲームオーバー画面を表現するクラス
//// UIシステムは未実装
//class GameOverScene : public Scene
//{
//private:
//    // ゲームオーバー画面で表示するスコア
//    int m_score;
//
//    // プレイヤーと敵のモデルハンドル（DXライブラリのモデル識別子）
//    // げんじてんでは使用されないが、将来の拡張のために保持
//    int m_playerModelHandle;
//    int m_enemyModelHandle;
//
//public:
//    // コンストラクタ：最終スコアとプレイヤー・敵のモデルハンドルを受け取ってゲームオーバー画面を初期化
//    GameOverScene(int finalScore, int playerModel, int enemyModel);
//
//    // ゲームオーバー画面の更新処理
//    void Update(Game& game) override;
//
//    // ゲームオーバー画面の描画処理
//    void Draw() override;
//};