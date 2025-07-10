// PlayScene.cpp
#include "PlayScene.h"
#include "DxLib.h"
#include "Game.h"
#include "GameOverScene.h"
#include "EnemyPrototype.h"
#include "BulletPrototype.h"
#include "VirtualScreenManager.h"
#include "ResourceManager.h"
#include "UIText.h"
#include "UIImage.h"
#include "CameraEntity.h"

PlayScene::PlayScene(int playerModel, int enemyModel)
    : m_enemyTimer(0), m_score(0), m_bulletCooldown(0),
    m_playerModelHandle(playerModel), m_enemyModelHandle(enemyModel)
{
    m_player = std::make_shared<PlayerEntity>(m_playerModelHandle);
    m_entitySystem.AddEntity(m_player);

    auto cameraEntity = std::make_shared<CameraEntity>();
    cameraEntity->GetCameraController()->SetTarget(m_player->m_playerTransform);
    cameraEntity->GetCameraComponent()->SetPosition(VAdd(m_player->m_playerTransform->position, VGet(2, 2, -10))); // Adjust camera position
    m_entitySystem.AddEntity(cameraEntity);

    SetCameraPositionAndTarget_UpVecY(
        m_player->m_playerTransform->position,  // Assuming m_playerTransform has a position of type VECTOR
        cameraEntity->GetCameraComponent()->GetPosition() // Assuming GetCameraComponent()->GetPosition() returns a VECTOR
    );

    m_uiManager = std::make_unique<UIManager>();
    auto mainUI = std::make_shared<UISystem>();

    auto scoreText = std::make_shared<UIText>(L"Score: 0", GetColor(0, 0, 0));
    scoreText->GetTransform().SetPosition({ 40, 40 });
    mainUI->AddComponent(scoreText);

    auto hpText = std::make_shared<UIText>(L"HP: 3", GetColor(255, 0, 0));
    hpText->GetTransform().SetPosition({ 40, 60 });
    mainUI->AddComponent(hpText);

	auto turialText = std::make_shared<UIText>(L"Press Z to shoot", GetColor(255, 255, 255));
    // 画面中央下
	turialText->GetTransform().SetPosition({ 600, 400});
	mainUI->AddComponent(turialText);

	auto tutorialtext2 = std::make_shared<UIText>(L"矢印キーで移動", GetColor(255, 255, 255));
	// 画面中央下
	tutorialtext2->GetTransform().SetPosition({ 600, 450});
	mainUI->AddComponent(tutorialtext2);

    m_uiManager->AddSystem("main", mainUI);

    m_soundManager.Load();
    m_soundManager.PlayBGM();

    m_backgroundHandle = ResourceManager::GetInstance().GetImage(L"Assets/UI/background_title.png");
    m_scoreBackgroundHandle = ResourceManager::GetInstance().GetImage(L"Assets/UI/statusBackground.png");
    m_groundTextureHandle = ResourceManager::GetInstance().GetImage(L"Assets/UI/ground.png");

    m_shootSEHandle = ResourceManager::GetInstance().GetSound(L"Assets/SE/fire.mp3");

    m_enemyPrototype = std::make_shared<EnemyPrototype>(m_enemyModelHandle, VGet(0, 0, 60));
    m_bulletPrototype = std::make_shared<BulletPrototype>(VGet(0, 2.0f, 0));
}

void PlayScene::Update(Game& game)
{
    m_player->HandleInput();

    if (m_bulletCooldown > 0) m_bulletCooldown--;

    if (CheckHitKey(KEY_INPUT_Z) && m_bulletCooldown == 0)
    {
        auto bullet = std::dynamic_pointer_cast<BulletEntity>(m_bulletPrototype->Clone());
        bullet->transform->position = m_player->m_playerTransform->position;
        bullet->transform->velocity = VGet(0, 0, 0.7f);
        bullet->active = true;
        m_playerBullets.push_back(bullet);
        m_entitySystem.AddEntity(bullet);
        m_bulletCooldown = 10;

        // 弾発射音の再生
        PlaySoundMem(m_shootSEHandle, DX_PLAYTYPE_BACK);
    }

    //if (CheckHitKey(KEY_INPUT_Z) && m_bulletCooldown == 0)
    //{
    //    auto bullet = std::dynamic_pointer_cast<BulletEntity>(m_bulletPrototype->Clone());
    //    bullet->transform->position = m_player->m_playerTransform->position;
    //    bullet->transform->velocity = VGet(0, 0, 0.7f);
    //    bullet->active = true;
    //    m_playerBullets.push_back(bullet);
    //    m_entitySystem.AddEntity(bullet);
    //    m_bulletCooldown = 10;
    //}

    if (++m_enemyTimer > 1)
    {
        m_enemyTimer = 0;
        auto enemy = std::dynamic_pointer_cast<EnemyEntity>(m_enemyPrototype->Clone());
        enemy->m_enemyTransform->position = VGet(rand() % 20 - 10, 0, 80);
        m_enemies.push_back(enemy);
        m_entitySystem.AddEntity(enemy);
    }

    //for (auto& e : m_enemies)
        for (auto& e : m_enemies)  
        {  
            if (e->active)  
            {  
                std::vector<std::shared_ptr<EnemyBulletEntity>> enemyBullets; // EnemyBulletEntity 型のベクターを使用  
                for (auto& bullet : m_enemyBullets)  
                {  
                    auto enemyBullet = std::dynamic_pointer_cast<EnemyBulletEntity>(bullet);  
                    if (enemyBullet)  
                    {  
                        enemyBullets.push_back(enemyBullet);  
                    }  
                }  
                e->UpdateAI(m_player->m_playerTransform->position, enemyBullets);  
            }  
        }
    //{
    //    if (e->active)
    //    {
    //        e->UpdateAI(m_player->m_playerTransform->position, m_enemyBullets);
    //    }
    //}
    for (auto& eb : m_enemyBullets) m_entitySystem.AddEntity(eb);
    m_enemyBullets.clear();

    m_entitySystem.Update();

    for (auto& b : m_playerBullets)
    {
        if (!b->active) continue;

        for (auto& e : m_enemies)
        {
            if (!e->active) continue;

            // 距離判定で当たり判定
            if (VSize(VSub(b->transform->position, e->m_enemyTransform->position)) < 1.0f)
            {
                b->active = false;     // 弾を消す
                e->active = false;     // 敵を消す
                m_score += 10;         // スコア加算
                break;                 // 弾1発につき1体のみヒット
            }
        }
    }

    for (auto& e : m_enemies)
    {
        if (e->active && VSize(VSub(e->m_enemyTransform->position, m_player->m_playerTransform->position)) < 1.0f)
        {
            if (m_player->m_invincibleTimer <= 0) {
                m_player->m_hp--;
                m_player->m_invincibleTimer = 60;
            }

            // 敵も非アクティブ（削除）にする
            e->active = false;
        }
    }

    for (auto& eb : m_enemyBullets)
    {
        if (eb->active && VSize(VSub(eb->m_enemyBulletTransform->position, m_player->m_playerTransform->position)) < 1.0f)
        {
            if (m_player->m_invincibleTimer <= 0) {
                eb->active = false;
                m_player->m_hp--;
                m_player->m_invincibleTimer = 60;
            }
        }
    }

    auto ui = m_uiManager->GetSystem("main");
    if (ui)
    {
        auto hpText = std::dynamic_pointer_cast<UIText>(ui->GetComponent(1));
        auto scoreText = std::dynamic_pointer_cast<UIText>(ui->GetComponent(0));
        if (hpText) hpText->SetText(L"HP: " + std::to_wstring(m_player->m_hp));
        if (scoreText) scoreText->SetText(L"Score: " + std::to_wstring(m_score));
    }

    if (m_player->m_hp <= 0)
    {
        m_soundManager.StopBGM();
        m_soundManager.PlayGameOver();
        game.ChangeScene(std::make_unique<GameOverScene>(m_score, m_playerModelHandle, m_enemyModelHandle));
    }
}

void PlayScene::Draw()
{
    int screenW = VirtualScreenManager::GetVirtualWidth();
    int screenH = VirtualScreenManager::GetVirtualHeight();

    DrawExtendGraph(0, 0, screenW, screenH, m_backgroundHandle, TRUE);
    DrawExtendGraph(0, 0, 150, 150, m_scoreBackgroundHandle, TRUE);

    VERTEX3D groundVertices[6];

    // 頂点とUV設定（2枚の三角形）
    groundVertices[0].pos = VGet(-500.0f, 0.0f, -500.0f);
    groundVertices[0].u = 0.0f; groundVertices[0].v = 0.0f;

    groundVertices[1].pos = VGet(500.0f, 0.0f, -500.0f);
    groundVertices[1].u = 1.0f; groundVertices[1].v = 0.0f;

    groundVertices[2].pos = VGet(500.0f, 0.0f, 500.0f);
    groundVertices[2].u = 1.0f; groundVertices[2].v = 1.0f;

    groundVertices[3].pos = VGet(-500.0f, 0.0f, -500.0f);
    groundVertices[3].u = 0.0f; groundVertices[3].v = 0.0f;

    groundVertices[4].pos = VGet(500.0f, 0.0f, 500.0f);
    groundVertices[4].u = 1.0f; groundVertices[4].v = 1.0f;

    groundVertices[5].pos = VGet(-500.0f, 0.0f, 500.0f);
    groundVertices[5].u = 0.0f; groundVertices[5].v = 1.0f;

    // 色・法線（単純設定）
    for (int i = 0; i < 6; ++i) {
        groundVertices[i].dif = GetColorU8(255, 255, 255, 255);
        groundVertices[i].norm = VGet(0.0f, 1.0f, 0.0f);
    }

    // テクスチャ付きポリゴン描画
    DrawPolygon3D(groundVertices, 6, m_groundTextureHandle, TRUE);

    //VECTOR ground[4] = {
    //    VGet(-100.0f, 0.0f, -100.0f), VGet(100.0f, 0.0f, -100.0f),
    //    VGet(100.0f, 0.0f,  100.0f), VGet(-100.0f, 0.0f,  100.0f)
    //};
    //DrawTriangle3D(ground[0], ground[1], ground[2], GetColor(0, 255, 0), TRUE);
    //DrawTriangle3D(ground[0], ground[2], ground[3], GetColor(0, 255, 0), TRUE);

    if (m_player->m_invincibleTimer > 0)
        DrawString(10, 70, _T("Invincible!"), GetColor(255, 0, 0));

    m_entitySystem.Draw();
    m_uiManager->DrawAll();
}

//#include "PlayScene.h"
//#include "DxLib.h"
//#include "Game.h"
//#include "GameOverScene.h"
//#include "EnemyPrototype.h"
//#include "BulletPrototype.h"
//#include "VirtualScreenManager.h"
//#include "ResourceManager.h"
//#include "UIText.h"
//#include "UIImage.h"
//#include "CameraEntity.h"
//
//PlayScene::PlayScene(int playerModel, int enemyModel)
//    : m_enemyTimer(0)
//    , m_score(0)
//    , m_bulletCooldown(0)
//    , m_playerModelHandle(playerModel)
//    , m_enemyModelHandle(enemyModel)
//{
//    // プレイヤー生成
//    m_player = std::make_shared<PlayerEntity>(m_playerModelHandle);
//    m_entitySystem.AddEntity(m_player);
//
//    // カメラエンティティ生成
//    auto cameraEntity = std::make_shared<CameraEntity>();
//    cameraEntity->GetCameraController()->SetTarget(m_player->m_playerTransform);
//    m_entitySystem.AddEntity(cameraEntity);
//
//    // UIマネージャーとUISystem構築
//    m_uiManager = std::make_unique<UIManager>();
//    auto mainUI = std::make_shared<UISystem>();
//
//    auto scoreText = std::make_shared<UIText>(L"Score: 0", GetColor(255, 255, 0));
//    scoreText->GetTransform().SetPosition({ 20, 20 });
//    mainUI->AddComponent(scoreText);
//
//    auto hpText = std::make_shared<UIText>(L"HP: 3", GetColor(255, 255, 255));
//    hpText->GetTransform().SetPosition({ 20, 50 });
//    mainUI->AddComponent(hpText);
//
//    m_uiManager->AddSystem("main", mainUI);
//
//    // BGM再生
//    m_soundManager.Load();
//    m_soundManager.PlayBGM();
//
//    // 背景画像の読み込み
//    m_backgroundHandle = ResourceManager::GetInstance().GetImage(L"Assets/UI/background_title.png");
//
//	// スコア背景画像の読み込み
//	m_scoreBackgroundHandle = ResourceManager::GetInstance().GetImage(L"Assets/UI/statusBackground.png");
//
//    // プロトタイプ生成
//    m_enemyPrototype = std::make_shared<EnemyPrototype>(m_enemyModelHandle, VGet(0, 0, 60));
//    //m_bulletPrototype = std::make_shared<BulletPrototype>(VGet(0, 0, 0));
//    m_bulletPrototype = std::make_shared<BulletPrototype>(m_playerModelHandle, VGet(0, 0, 0));
//}
//
//void PlayScene::Update(Game& game)
//{
//    m_player->HandleInput();
//    if (m_bulletCooldown > 0) m_bulletCooldown--;
//
//    if (CheckHitKey(KEY_INPUT_Z) && m_bulletCooldown == 0)
//    {
//        auto bullet = std::dynamic_pointer_cast<BulletEntity>(m_bulletPrototype->Clone());
//        bullet->transform->position = m_player->m_playerTransform->position;
//        bullet->transform->velocity = VGet(0, 0, 0.7f);
//        bullet->active = true;
//        m_playerBullets.push_back(bullet);
//        m_entitySystem.AddEntity(bullet);
//        m_bulletCooldown = 10;
//    }
//
//    if (++m_enemyTimer > 120)
//    {
//        m_enemyTimer = 0;
//        auto enemy = std::dynamic_pointer_cast<EnemyEntity>(m_enemyPrototype->Clone());
//        enemy->m_enemyTransform->position = VGet(rand() % 20 - 10, 0, 80);
//        m_enemies.push_back(enemy);
//        m_entitySystem.AddEntity(enemy);
//    }
//
//    for (auto& e : m_enemies)
//    {
//        if (e->active)
//        {
//            e->UpdateAI(m_player->m_playerTransform->position, m_enemyBullets);
//        }
//    }
//    for (auto& eb : m_enemyBullets) { m_entitySystem.AddEntity(eb); }
//    m_enemyBullets.clear();
//
//    m_entitySystem.Update();
//
//    for (auto& b : m_playerBullets)
//    {
//        if (!b->active) continue;
//        for (auto& e : m_enemies)
//        {
//            if (!e->active) continue;
//            if (VSize(VSub(b->transform->position, e->m_enemyTransform->position)) < 1.0f)
//            {
//                b->active = false;
//                e->active = false;
//                m_score += 10;
//                break;
//            }
//        }
//    }
//
//    for (auto& e : m_enemies)
//    {
//        if (e->active && VSize(VSub(e->m_enemyTransform->position, m_player->m_playerTransform->position)) < 1.0f)
//        {
//            if (m_player->m_invincibleTimer <= 0) {
//                m_player->m_hp--;
//                m_player->m_invincibleTimer = 60;
//            }
//        }
//    }
//    for (auto& eb : m_enemyBullets)
//    {
//        if (eb->active && VSize(VSub(eb->m_enemyBulletTransform->position, m_player->m_playerTransform->position)) < 1.0f)
//        {
//            if (m_player->m_invincibleTimer <= 0) {
//                eb->active = false;
//                m_player->m_hp--;
//                m_player->m_invincibleTimer = 60;
//            }
//        }
//    }
//
//    // HP・スコア更新
//    auto ui = m_uiManager->GetSystem("main");
//    if (ui)
//    {
//        auto hpText = std::dynamic_pointer_cast<UIText>(ui->GetComponent(1));
//        auto scoreText = std::dynamic_pointer_cast<UIText>(ui->GetComponent(0));
//        if (hpText) hpText->SetText(L"HP: " + std::to_wstring(m_player->m_hp));
//        if (scoreText) scoreText->SetText(L"Score: " + std::to_wstring(m_score));
//    }
//
//    if (m_player->m_hp <= 0)
//    {
//        m_soundManager.StopBGM();
//        m_soundManager.PlayGameOver();
//        game.ChangeScene(std::make_unique<GameOverScene>(m_score, m_playerModelHandle, m_enemyModelHandle));
//    }
//}
//
//void PlayScene::Draw()
//{
//    int screenW = VirtualScreenManager::GetVirtualWidth();
//    int screenH = VirtualScreenManager::GetVirtualHeight();
//
//    DrawExtendGraph(0, 0, screenW, screenH, m_backgroundHandle, TRUE);
//
//
//    DrawExtendGraph(0, 0, 150, 150, m_scoreBackgroundHandle, TRUE);
//
//    VECTOR ground[4] = 
//    {
//          VGet(-100.0f, 0.0f, -100.0f)
//        , VGet(100.0f, 0.0f, -100.0f)
//        , VGet(100.0f, 0.0f,  100.0f)
//        , VGet(-100.0f, 0.0f,  100.0f)
//    };
//    DrawTriangle3D(ground[0], ground[1], ground[2], GetColor(0, 255, 0), TRUE);
//    DrawTriangle3D(ground[0], ground[2], ground[3], GetColor(0, 255, 0), TRUE);
//
//    // 無敵状態の表示
//    if (m_player->m_invincibleTimer > 0)
//        DrawString(10, 70, _T("Invincible!"), GetColor(255, 0, 0));
//
//    m_entitySystem.Draw();
//    m_uiManager->DrawAll();
//}