#include "PlayerEntity.h"
#include "DxLib.h"

PlayerEntity::PlayerEntity(int modelHandle)
    : m_hp(3)
    , m_invincibleTimer(0)
{
    active = true;

    // 初期位置とTransform
    m_playerTransform = std::make_shared<TransformComponent>(VGet(0, 0, -30));
    AddComponent(m_playerTransform);

    // モデル描画コンポーネント
    AddComponent(std::make_shared<RenderModelComponent>(modelHandle, m_playerTransform));
}

void PlayerEntity::HandleInput()
{
	// 入力処理：キーボードの矢印キーで移動
	VECTOR velocity = VGet(0, 0, 0);                            // 初期化
    if (CheckHitKey(KEY_INPUT_DOWN))  velocity.z -= 0.3f;
    if (CheckHitKey(KEY_INPUT_UP))    velocity.z += 0.3f;
    if (CheckHitKey(KEY_INPUT_LEFT))  velocity.x -= 0.3f;
    if (CheckHitKey(KEY_INPUT_RIGHT)) velocity.x += 0.3f;

    // 移動処理

    m_playerTransform->velocity = velocity;

    // 回転処理：移動方向に向ける（Y軸）
    if (VSize(velocity) > 0.01f) {
        m_playerTransform->rotation.y = atan2f(velocity.x, velocity.z);
    }
}

// プレイヤーのダメージ処理
void PlayerEntity::Update()
{
    Entity::Update();
    if (m_invincibleTimer > 0) m_invincibleTimer--;
}