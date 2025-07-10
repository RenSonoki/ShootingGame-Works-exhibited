#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include <memory>

// モデルの描画を担当するコンポーネント
class RenderModelComponent : public Component
{
private:
    int m_modelHandle;  // モデルハンドル
    std::shared_ptr<TransformComponent> m_renderTransform;  // 位置・回転情報

    // --- アニメーション制御用 ---
    int m_attachIndex = -1;
    int m_totalTime = 0;
    int m_currentTime = 0;

public:
    RenderModelComponent(int model, std::shared_ptr<TransformComponent> tf);

    void Update() override;
    void Draw() override;
};
