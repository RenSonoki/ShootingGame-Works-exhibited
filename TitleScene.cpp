#include "TitleScene.h"
#include "DxLib.h"
#include "PlayScene.h"
#include "VirtualScreenManager.h"
#include "UIImage.h"
#include "UISystem.h"
#include "ResourceManager.h"
#include <cmath>

TitleScene::TitleScene(int playerModel, int enemyModel)
    : m_playerModelHandle(playerModel)
    , m_enemyModelHandle(enemyModel)
    , m_animTimer(0)
{
    // カメラ初期化
    m_cameraComponent = std::make_shared<CameraComponent>();
    m_cameraComponent->SetPosition(VGet(0, 0, -10));
    m_cameraComponent->SetTarget(VGet(0, 0, 0));
    m_cameraController = std::make_unique<CameraController>(m_cameraComponent);

    // UI構築
    m_uiManager = std::make_unique<UIManager>();
    auto mainUI = std::make_shared<UISystem>();

    // ロゴ
    auto logo = std::make_shared<UIImage>(L"Assets/UI/titleLogo.png");
	logo->GetTransform().SetPosition({ 500, 150 });
    logo->GetTransform().SetScale({ 0.8f, 0.8f });

    m_soundManager.Load();
	m_soundManager.TitleBGM();

    // ボタン
    auto button = std::make_shared<UIImage>(L"Assets/UI/startButton.png");
    button->GetTransform().SetPosition({ 500, 400 });
    button->GetTransform().SetScale({ 0.5f, 0.5f });

    mainUI->AddComponent(logo);
    mainUI->AddComponent(button);

    m_uiManager->AddSystem("main", mainUI);
}

void TitleScene::Update(Game& game)
{
    m_animTimer++;
    m_cameraController->Update();

    // ロゴの縦揺れ演出
    auto system = m_uiManager->GetSystem("main");
    if (system)
    {
        auto comps = system->GetComponents();
        if (!comps.empty())
        {
            auto logo = std::dynamic_pointer_cast<UIImage>(comps[0]);
            if (logo)
            {
                VECTOR2 pos = logo->GetTransform().GetPosition();
                pos.y = 150 + std::sin(m_animTimer * 0.05f) * 10;
                logo->GetTransform().SetPosition(pos);
            }
        }
    }

    if (CheckHitKey(KEY_INPUT_RETURN))
    {
		m_soundManager.StopTitleBGM();


        game.ChangeScene(std::make_unique<PlayScene>(m_playerModelHandle, m_enemyModelHandle));
    }
}

void TitleScene::Draw()
{
    m_cameraComponent->ApplyToDxLibCamera();

    // 背景（リソースマネージャーで共有）
    int bgHandle = ResourceManager::GetInstance().GetImage(L"Assets/UI/background_title.png");
    int screenW = VirtualScreenManager::GetVirtualWidth();
    int screenH = VirtualScreenManager::GetVirtualHeight();
    DrawExtendGraph(0, 0, screenW, screenH, bgHandle, TRUE);

    // UI描画
    if (m_uiManager) m_uiManager->DrawAll();
}


//#include "TitleScene.h"
//#include "DxLib.h"
//#include "PlayScene.h"
//#include "VirtualScreenManager.h"
//#include "UIImage.h"
//#include "UISystem.h"
//
//// コンストラクタ
//// モデルハンドルを受け取り、カメラ・UIの初期化を行う
//TitleScene::TitleScene(int playerModel, int enemyModel)
//    : m_playerModelHandle(playerModel)
//    , m_enemyModelHandle(enemyModel)
//    , m_animTimer(0)
//{
//    // カメラの初期設定（演出用カメラ）
//	// make_sharedを使用してスマートポインタで管理
//    m_cameraComponent = std::make_shared<CameraComponent>();
//        m_cameraComponent->SetPosition(VGet(0, 0, -10));                            // 奥から中央を見る
//        m_cameraComponent->SetTarget(VGet(0, 0, 0));                                // 注視点は原点
//        m_cameraController = std::make_unique<CameraController>(m_cameraComponent);
//
//    // UI管理クラスの生成とメインUIレイヤーの作成
//    m_uiManager = std::make_shared<UIManager>();
//
//	// メインUIシステムの生成
//    // auto = 型推論を利用するメリット: 
//    // もともとの UISystem は std::shared_ptr<UISystem> であったが、
//    // auto を使うことで明示的な型指定が不要になり、コードが簡潔になる
//	auto mainUI = std::make_shared<UISystem>();
//
//    // 仮想画面サイズを取得（ウィンドウ・フルスクリーンどちらにも対応可能）
//    int screenW = VirtualScreenManager::GetVirtualWidth();
//    int screenH = VirtualScreenManager::GetVirtualHeight();
//
//    // 背景画像の生成・配置（画面全体にフィットするようにスケーリング）
//    auto background = std::make_shared<UIImage>(_T("Assets/UI/background_title.png"));
//    background->GetTransform().SetPosition({ screenW / 2.0f, screenH / 2.0f }); // 中央配置
//    background->GetTransform().SetScale(
//        {
//        screenW / static_cast<float>(background->GetOriginalWidth()),
//        screenH / static_cast<float>(background->GetOriginalHeight())
//        });
//    mainUI->AddComponent(background); // 背景をUIシステムに追加
//
//    // タイトルロゴの生成・配置（やや上に配置して後にアニメーション対象にする）
//    auto logo = std::make_shared<UIImage>(_T("Assets/UI/titleLogo.png"));
//    logo->GetTransform().SetPosition({ screenW / 2.0f, 150.0f });           // 上部中央
//    logo->GetTransform().SetScale({ 0.5f, 0.5f });                          // 50%に縮小
//    mainUI->AddComponent(logo);
//
//    // スタートボタンの生成・配置（下部に固定）
//    auto startButton = std::make_shared<UIImage>(_T("Assets/UI/startButton.png"));
//    startButton->GetTransform().SetPosition({ screenW / 2.0f, 400.0f });            // 中央下あたり
//    startButton->GetTransform().SetScale({ 0.5f, 0.5f });
//    mainUI->AddComponent(startButton);
//
//    // UIマネージャーに「main」レイヤーとして登録
//    m_uiManager->AddSystem("main", mainUI);
//}
//
//// 毎フレーム呼ばれる更新処理
//void TitleScene::Update(Game& game)
//{
//    m_animTimer++;                  // ロゴ揺れアニメーション用タイマー
//    m_cameraController->Update();   // カメラ演出の更新
//
//    // タイトルロゴを縦に揺らす演出
//    auto system = m_uiManager->GetSystem("main");
//    if (system)
//    {
//        // ロゴはインデックス1に格納されている前提
//        auto logo = std::dynamic_pointer_cast<UIImage>(system->GetComponent(1));
//        if (logo)
//        {
//            auto pos = logo->GetTransform().GetPosition();
//            pos.y = 150.0f + std::sin(m_animTimer * 0.05f) * 10.0f; // sin波で上下に揺らす
//            logo->GetTransform().SetPosition(pos);
//        }
//    }
//
//    // Enterキーが押されたらプレイシーンに遷移
//    if (CheckHitKey(KEY_INPUT_RETURN))
//    {
//        // 保持していたモデルハンドルを次のシーンに引き継ぐ
//        game.ChangeScene(std::make_unique<PlayScene>(m_playerModelHandle, m_enemyModelHandle));
//    }
//}
//
//// 描画処理：3Dカメラの適用とUIの描画
//void TitleScene::Draw()
//{
//    m_cameraComponent->ApplyToDxLibCamera(); // DXライブラリにカメラ情報を適用
//    m_uiManager->DrawAll();                  // UI全体を描画
//}
