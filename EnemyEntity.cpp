#include "EnemyEntity.h"
#include "EnemyBulletEntity.h"
#include <cmath>                 // 数学的な計算を行うためのヘッダーファイル

// コンストラクタ
// modelHandle は敵モデルの識別用ハンドル、pos は敵の初期位置
EnemyEntity::EnemyEntity(int modelHandle, VECTOR pos)
{
    active = true;  // エンティティをアクティブ状態に設定

    // TransformComponent を作成し、位置を設定
    m_enemyTransform = std::make_shared<TransformComponent>(pos);

    // TransformComponent をエンティティに追加
    AddComponent(m_enemyTransform);

    // RenderModelComponent を作成し、敵モデルを設定
    AddComponent(std::make_shared<RenderModelComponent>(modelHandle, m_enemyTransform));

    // 弾発射タイマーを初期化
    m_shotTimer = 0;
}

// UpdateAI メソッド：敵のAIを更新し、ターゲット（通常はプレイヤー）の位置に基づいて動作を決定
void EnemyEntity::UpdateAI(VECTOR target, std::vector<std::shared_ptr<EnemyBulletEntity>>& bullets)
{
    // ターゲット（プレイヤー）との位置ベクトルを計算
    VECTOR dir = VSub(target, m_enemyTransform->position);

    // ベクトルの長さ（距離）を計算
    float len = VSize(dir);

    // ターゲットとの距離が十分であれば、ターゲット方向に向かう速度を設定
    if (len > 0.01f)
    {
        // ベクトルを正規化（単位ベクトルにする）
        dir = VScale(dir, 1.0f / len);
        // 敵の速度を設定（速度ベクトルをターゲット方向に設定）
        m_enemyTransform->velocity = VScale(dir, 0.6f);  // 0.2f は移動速度
    }
    else
    {
        // ターゲットに近すぎる場合は停止
        m_enemyTransform->velocity = VGet(0, 0, 0);
    }

    // 弾発射タイマーを進める
    if (++m_shotTimer > 120)
    {
        m_shotTimer = 0;  // タイマーをリセット
        // 弾発射方向を計算（ターゲット方向）
        VECTOR shotDir = VSub(target, m_enemyTransform->position);
		// 弾発射方向の長さを計算
        float sLen = VSize(shotDir);

        // ターゲットに向けて弾を発射
        if (sLen > 0.01f)
        {
            // 弾の発射方向を正規化
            shotDir = VScale(shotDir, 1.0f / sLen);
            // 弾を生成し、弾のリストに追加
            bullets.push_back(std::make_shared<EnemyBulletEntity>(m_enemyTransform->position, shotDir));
        }
    }
}