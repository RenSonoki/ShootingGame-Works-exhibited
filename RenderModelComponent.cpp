#include "RenderModelComponent.h"
#include "DxLib.h"

// �R���X�g���N�^
RenderModelComponent::RenderModelComponent(int model, std::shared_ptr<TransformComponent> tf)
    : m_modelHandle(model), m_renderTransform(tf)
{    // ���[�V����0�Ԃ��A�^�b�`
    m_attachIndex = MV1AttachAnim(m_modelHandle, 0, -1, FALSE);
    m_totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex);

    // "�Z���^�[" �t���[���̈ړ��𖳌����iPMX/PMD�����j
    int centerFrame = MV1SearchFrame(m_modelHandle, _T("�Z���^�["));
    if (centerFrame != -1) {
        MV1SetFrameUserLocalMatrix(m_modelHandle, centerFrame, MGetIdent());
    }
}

// ���f���̈ʒu�E��] + �A�j���[�V�����X�V
void RenderModelComponent::Update()
{
    if (m_attachIndex != -1) {
        ++m_currentTime;
        if (m_currentTime >= m_totalTime) {
            m_currentTime = 0;
        }
        MV1SetAttachAnimTime(m_modelHandle, m_attachIndex, m_currentTime);
    }

    // �ʒu�E��]�̍X�V
    MV1SetPosition(m_modelHandle, m_renderTransform->position);
    MV1SetRotationXYZ(m_modelHandle, m_renderTransform->rotation);
}

// ���f���̕`��
void RenderModelComponent::Draw()
{
    MV1SetPosition(m_modelHandle, m_renderTransform->position);
    MV1SetRotationXYZ(m_modelHandle, m_renderTransform->rotation);
    MV1DrawModel(m_modelHandle);
}