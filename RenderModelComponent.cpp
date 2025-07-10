#include "RenderModelComponent.h"
#include "DxLib.h"

// コンストラクタ
RenderModelComponent::RenderModelComponent(int model, std::shared_ptr<TransformComponent> tf)
    : m_modelHandle(model), m_renderTransform(tf)
{    // モーション0番をアタッチ
    m_attachIndex = MV1AttachAnim(m_modelHandle, 0, -1, FALSE);
    m_totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex);

    // "センター" フレームの移動を無効化（PMX/PMD向け）
    int centerFrame = MV1SearchFrame(m_modelHandle, _T("センター"));
    if (centerFrame != -1) {
        MV1SetFrameUserLocalMatrix(m_modelHandle, centerFrame, MGetIdent());
    }
}

// モデルの位置・回転 + アニメーション更新
void RenderModelComponent::Update()
{
    if (m_attachIndex != -1) {
        ++m_currentTime;
        if (m_currentTime >= m_totalTime) {
            m_currentTime = 0;
        }
        MV1SetAttachAnimTime(m_modelHandle, m_attachIndex, m_currentTime);
    }

    // 位置・回転の更新
    MV1SetPosition(m_modelHandle, m_renderTransform->position);
    MV1SetRotationXYZ(m_modelHandle, m_renderTransform->rotation);
}

// モデルの描画
void RenderModelComponent::Draw()
{
    MV1SetPosition(m_modelHandle, m_renderTransform->position);
    MV1SetRotationXYZ(m_modelHandle, m_renderTransform->rotation);
    MV1DrawModel(m_modelHandle);
}