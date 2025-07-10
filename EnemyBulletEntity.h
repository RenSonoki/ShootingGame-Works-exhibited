#pragma once
#include "Entity.h"
#include "TransformComponent.h"
#include <memory>               // std::shared_ptr を使用するためのヘッダーファイル

// 敵の弾を管理するエンティティクラス
// 弾の位置と移動に関する情報を持ち、敵から発射される弾のデータを管理します。
class EnemyBulletEntity : public Entity
{
public:
    // 弾の位置と移動を管理する TransformComponent
    std::shared_ptr<TransformComponent> m_enemyBulletTransform;

    // コンストラクタ
    EnemyBulletEntity(VECTOR startPos, VECTOR dir);
};