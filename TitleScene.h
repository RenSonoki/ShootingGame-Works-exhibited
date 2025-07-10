#pragma once

#include "Scene.h"
#include "Game.h"
#include "CameraController.h"
#include "CameraComponent.h"
#include "SoundManager.h"
#include "UIManager.h"
#include <memory>

// タイトルシーン
class TitleScene : public Scene
{
private:
    int m_playerModelHandle;
    int m_enemyModelHandle;

    std::shared_ptr<CameraComponent> m_cameraComponent;
    std::unique_ptr<CameraController> m_cameraController;

    std::unique_ptr<UIManager> m_uiManager;
    int m_animTimer;

    // サウンド
    SoundManager m_soundManager;

public:
    TitleScene(int playerModel, int enemyModel);
    void Update(Game& game) override;
    void Draw() override;
};

//#pragma once
//
//#include "Scene.h"
//#include "Game.h"
//#include "CameraController.h"
//#include "CameraComponent.h"
//#include "UIManager.h"
//#include <memory>
//
//// タイトルシーン
//class TitleScene : public Scene
//{
//private:
//	// モデルは現状使用していないが将来的に使用する可能性があるため
//
//    // プレイヤーキャラクターの3Dモデルハンドル
//    int m_playerModelHandle;
//
//    // 敵キャラクターの3Dモデルハンドル
//    int m_enemyModelHandle;
//
//    // 以下の変数の型は長くなるため、cpp内では短縮目的として
//	// autoの型推論を用いている
//
//    // タイトル用カメラのコンポーネント
//    // Transformを通してカメラ位置・向きの制御を行う
//    std::shared_ptr<CameraComponent> m_cameraComponent;
//
//    // カメラ制御クラス
//    // ゆっくり回転させるなどの演出に使用
//    std::unique_ptr<CameraController> m_cameraController;
//
//    // UIの管理クラス（ボタンやロゴの表示を担当）
//    std::shared_ptr<UIManager> m_uiManager;
//
//    // アニメーション用タイマー（ロゴの揺れなどに使用）
//    int m_animTimer;
//
//public:
//    // コンストラクタ：プレイヤー・敵モデルのハンドルを受け取る
//    TitleScene(int playerModel, int enemyModel);
//
//    // シーン更新処理（入力処理やアニメーション進行など）
//    void Update(Game& game) override;
//
//    // 描画処理（3Dモデル、カメラ、UIなどを描画）
//    void Draw() override;
//};