#include "SpriteRendererComponent.h"

// コンストラクタ
SpriteRendererComponent::SpriteRendererComponent(int handle, std::shared_ptr<TransformComponent> tf)
    : m_graphHandle(handle)       // 画像ハンドル（LoadGraphなどで取得した値）
    , m_spriteTransform(tf)       // スプライト描画位置・回転・スケールなどの情報を持つTransform
{
}

// 描画処理
// TransformComponent の位置をもとに、スケール・中心揃え・透明度を反映して描画
void SpriteRendererComponent::Draw()
{
    // 無効なハンドルやTransformが設定されていない場合は描画をスキップ
    if (m_graphHandle == -1 || m_spriteTransform == nullptr) return;

    int width = 0, height = 0;

    // 画像サイズを取得（元画像のピクセル幅と高さ）
    GetGraphSize(m_graphHandle, &width, &height);

    // 描画基準位置をTransformのx, y座標から取得（Z座標は2D描画では使用しない）
    int drawX = static_cast<int>(m_spriteTransform->position.x);
    int drawY = static_cast<int>(m_spriteTransform->position.y);

    // 「中心揃え」オプションが有効な場合、描画位置を画像の中心にずらす
    if (m_centered)
    {
        drawX -= static_cast<int>(width * 0.5f * m_scale);  // 半分の幅 × スケール分 左に移動
        drawY -= static_cast<int>(height * 0.5f * m_scale); // 半分の高さ × スケール分 上に移動
    }

    // アルファブレンドを有効にし、透明度を設定
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);

    // 画像をスケーリングして描画（左上と右下の座標を指定）
    DrawExtendGraph
    (
        drawX,
        drawY,
        drawX + static_cast<int>(width * m_scale),
        drawY + static_cast<int>(height * m_scale),
        m_graphHandle,
        TRUE  // 透過色を使用（白色を透過するPNGなどに対応）
    );

    // ブレンドモードを元に戻す（これをしないと他の描画にも影響が出る）
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}