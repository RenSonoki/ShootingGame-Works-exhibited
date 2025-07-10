#include "EnemyBulletRenderComponent.h"
#include "DxLib.h"

// コンストラクタ
EnemyBulletRenderComponent::EnemyBulletRenderComponent(std::shared_ptr<TransformComponent> tf)
	: m_enemyBulletRenderTransform(tf)      // TransformComponentを受け取る
{
    // TransformComponent（弾の位置）を設定
}

// 毎フレームの更新処理
// このクラスでは位置の更新などは行わず、TransformComponent によって管理
void EnemyBulletRenderComponent::Update()
{
    // 位置の更新は TransformComponent が担当
}

// 敵の弾を描画
// TransformComponent の位置を使って弾を描画
void EnemyBulletRenderComponent::Draw()
{
    // 弾を3D空間に描画（球体を使用）
	// DXライブラリの DrawSphere3D 関数を使用
    DrawSphere3D
    (
		m_enemyBulletRenderTransform->position      // TransformComponentから位置を取得
		, 0.2f, 6, GetColor(255, 50, 50)            // 半径0.2、分割数6、色を指定
		, GetColor(255, 0, 0)                       // 色を赤系統に設定
		, TRUE                                      // 透明度を有効にする
    );
}
