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
//    // ターゲットの位置
//    VECTOR targetPos = m_target->position;
//
//    // カメラの方向ベクトル（前方）を仮定：Z軸マイナス方向を「前」とする
//    VECTOR forward = VGet(0.0f, 0.0f, 1.0f);  // 今は固定方向（後でTransform回転を使うなら更新可）
//
//    // カメラ位置 = ターゲットの後方（forwardの逆）＋上方向
//    VECTOR cameraOffset = VAdd(
//        VScale(forward, -m_distance),   // 後方
//        VGet(10.0f, m_height, 0.0f)       // 上方向
//    );
//
//    VECTOR cameraPos = VAdd(targetPos, cameraOffset);
//
//    // 注視点 = ターゲットの少し前＋少し下
//    VECTOR lookAhead = VAdd(
//        targetPos,
//        VAdd(VScale(forward, m_lookAheadDistance), VGet(0.0f, -m_lookDownOffset, 0.0f))
//    );
//
//    // カメラ更新
//    SetCameraPositionAndTarget_UpVecY(cameraPos, lookAhead);
//    SetCameraNearFar(1.0f, 500.0f);
//}


void CameraController::Update()
{
    if (!m_camera || !m_target) return;

    VECTOR targetPos = m_target->position;

    // プレイヤーの右肩後方・斜め上から見下ろす位置（調整可能）
    VECTOR offset = VGet(0.0f, 20.0f, -40.0f);

    VECTOR cameraPos = VAdd(targetPos, offset);

    // カメラ位置・注視点を更新
    m_camera->SetPosition(cameraPos);
    m_camera->SetTarget(targetPos);

    // ニア／ファークリップを毎フレーム適用（必要に応じて初期化時だけにしてもOK）
    SetCameraNearFar(1.0f, 500.0f);

    // DxLibに適用
    m_camera->ApplyToDxLibCamera();
}

