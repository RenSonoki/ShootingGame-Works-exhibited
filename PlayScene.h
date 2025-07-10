#pragma once

#include "Scene.h"
#include "Game.h"
#include "EntitySystem.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "BulletEntity.h"
#include "CameraController.h"
#include "CameraComponent.h"
#include "UIManager.h"
#include "EnemyPrototype.h"
#include "BulletPrototype.h"
#include "SoundManager.h"
#include <memory>
#include <vector>

class PlayScene : public Scene
{
private:
    // エンティティとUI
    EntitySystem m_entitySystem;
    std::shared_ptr<PlayerEntity> m_player;
    std::vector<std::shared_ptr<EnemyEntity>> m_enemies;
    std::vector<std::shared_ptr<BulletEntity>> m_playerBullets;
    std::vector<std::shared_ptr<EnemyBulletEntity>> m_enemyBullets;

    // スコア・タイマーなど
    int m_enemyTimer;
    int m_score;
    int m_bulletCooldown;

    // モデルハンドル
    int m_playerModelHandle;
    int m_enemyModelHandle;

    // カメラ
    std::shared_ptr<CameraComponent> m_cameraComponent;
    std::unique_ptr<CameraController> m_cameraController;

    // UI
    std::unique_ptr<UIManager> m_uiManager;

    // プロトタイプ
    std::shared_ptr<EnemyPrototype> m_enemyPrototype;
    std::shared_ptr<BulletPrototype> m_bulletPrototype;

    // 背景画像ハンドル
    int m_backgroundHandle;

	// スコア背景画像ハンドル
	int m_scoreBackgroundHandle;

	// 地面の画像ハンドル
	int m_groundTextureHandle;

    int m_shootSEHandle;  // 弾発射音SEハンドル

    // サウンド
    SoundManager m_soundManager;

public:
    PlayScene(int playerModel, int enemyModel);
    void Update(Game& game) override;
    void Draw() override;
};