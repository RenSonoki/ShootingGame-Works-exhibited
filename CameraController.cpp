// CameraController.cpp
#include "CameraController.h"

CameraController::CameraController(std::shared_ptr<CameraComponent> camera)
    : m_camera(camera)
{
}

void CameraController::SetTarget(std::shared_ptr<TransformComponent> target)
{
    m_target = target;
}

//void CameraController::Update()
//{
//    if (!m_target) return;
//
//    // �^�[�Q�b�g�̈ʒu
//    VECTOR targetPos = m_target->position;
//
//    // �J�����̕����x�N�g���i�O���j������FZ���}�C�i�X�������u�O�v�Ƃ���
//    VECTOR forward = VGet(0.0f, 0.0f, 1.0f);  // ���͌Œ�����i���Transform��]���g���Ȃ�X�V�j
//
//    // �J�����ʒu = �^�[�Q�b�g�̌���iforward�̋t�j�{�����
//    VECTOR cameraOffset = VAdd(
//        VScale(forward, -m_distance),   // ���
//        VGet(10.0f, m_height, 0.0f)       // �����
//    );
//
//    VECTOR cameraPos = VAdd(targetPos, cameraOffset);
//
//    // �����_ = �^�[�Q�b�g�̏����O�{������
//    VECTOR lookAhead = VAdd(
//        targetPos,
//        VAdd(VScale(forward, m_lookAheadDistance), VGet(0.0f, -m_lookDownOffset, 0.0f))
//    );
//
//    // �J�����X�V
//    SetCameraPositionAndTarget_UpVecY(cameraPos, lookAhead);
//    SetCameraNearFar(1.0f, 500.0f);
//}


void CameraController::Update()
{
    if (!m_camera || !m_target) return;

    VECTOR targetPos = m_target->position;

    // �v���C���[�̉E������E�΂ߏォ�猩���낷�ʒu�i�����\�j
    VECTOR offset = VGet(0.0f, 20.0f, -40.0f);

    VECTOR cameraPos = VAdd(targetPos, offset);

    // �J�����ʒu�E�����_���X�V
    m_camera->SetPosition(cameraPos);
    m_camera->SetTarget(targetPos);

    // �j�A�^�t�@�[�N���b�v�𖈃t���[���K�p�i�K�v�ɉ����ď������������ɂ��Ă�OK�j
    SetCameraNearFar(1.0f, 500.0f);

    // DxLib�ɓK�p
    m_camera->ApplyToDxLibCamera();
}

