#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include <memory>

// ���f���̕`���S������R���|�[�l���g
class RenderModelComponent : public Component
{
private:
    int m_modelHandle;  // ���f���n���h��
    std::shared_ptr<TransformComponent> m_renderTransform;  // �ʒu�E��]���

    // --- �A�j���[�V��������p ---
    int m_attachIndex = -1;
    int m_totalTime = 0;
    int m_currentTime = 0;

public:
    RenderModelComponent(int model, std::shared_ptr<TransformComponent> tf);

    void Update() override;
    void Draw() override;
};
