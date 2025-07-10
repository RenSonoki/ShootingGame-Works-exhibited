#pragma once
#include "Component.h"
#include "TransformComponent.h"  
#include <memory>                // std::shared_ptr を使用するためのヘッダーファイル

// 敵の弾の描画を担当するコンポーネント
// 敵の弾が持つ位置情報（Transform）を使って、弾を描画します。
class EnemyBulletRenderComponent : public Component
{
public:
    std::shared_ptr<TransformComponent> m_enemyBulletRenderTransform; // 弾の位置情報を保持する TransformComponent

    // コンストラクタ
	// 引数には弾の位置情報を持つ TransformComponent のスマートポインタを受け取る
    EnemyBulletRenderComponent(std::shared_ptr<TransformComponent> tf);

    // 毎フレームの更新処理
	// このクラスでは描画に関連する処理のみのため空実装
    void Update() override;

    // 敵の弾を描画
    void Draw() override;
};
