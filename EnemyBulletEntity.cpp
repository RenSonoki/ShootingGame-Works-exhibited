#include "EnemyBulletEntity.h"
#include "EnemyBulletRenderComponent.h"

// コンストラクタ：弾の発射位置（startPos）と方向（dir）を受け取り、EnemyBulletEntity を初期化
// startPos は弾の発射位置、dir は弾の移動方向を表すベクトル
EnemyBulletEntity::EnemyBulletEntity(VECTOR startPos, VECTOR dir)
{
    // TransformComponent を作成し、弾の初期位置を設定
    m_enemyBulletTransform = std::make_shared<TransformComponent>(startPos);

    // 方向ベクトル（dir）をスケールして移動速度を設定
    m_enemyBulletTransform->velocity = VScale(dir, 0.3f);  // 弾の移動方向と速度を設定（0.3f は弾の速度）

    // TransformComponent をエンティティに追加
    AddComponent(m_enemyBulletTransform);

    // 弾の描画コンポーネント（EnemyBulletRenderComponent）を追加
    // transform（位置情報）を渡して描画を行う
    AddComponent(std::make_shared<EnemyBulletRenderComponent>(m_enemyBulletTransform));  // 描画処理用コンポーネントの追加
}
