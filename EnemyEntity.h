#pragma once
#include "Entity.h"
#include "TransformComponent.h"
#include "RenderModelComponent.h"
#include "EnemyBulletEntity.h"
#include <memory>               // std::shared_ptr を使用するためのヘッダーファイル
#include <vector>               // std::vector を使用するためのヘッダーファイル

// 敵キャラクターのエンティティを管理するクラス
// 敵の位置、移動、攻撃、AIなどの処理を行います。
class EnemyEntity : public Entity
{
public:
    // TransformComponent は位置や速度を管理する
    std::shared_ptr<TransformComponent> m_enemyTransform;

    // 弾発射のタイマー（敵が弾を発射するタイミングを管理）
    int m_shotTimer;

    // コンストラクタ
    EnemyEntity(int modelHandle, VECTOR pos);

    // UpdateAI メソッド：敵のAIを更新し、ターゲット（プレイヤー）に基づいて動作を決定
    // target はプレイヤーの位置、bullets は敵の弾のリスト
    void UpdateAI(VECTOR target, std::vector<std::shared_ptr<EnemyBulletEntity>>& bullets);
};
