// CameraComponent.cpp
#include "CameraComponent.h"

CameraComponent::CameraComponent()
    : m_position(VGet(0, 0, -10)), m_target(VGet(0, 0, 0)), m_upVector(VGet(0, 1, 0)) {
}

void CameraComponent::SetPosition(const VECTOR& pos) { m_position = pos; }
void CameraComponent::SetTarget(const VECTOR& target) { m_target = target; }
void CameraComponent::SetUpVector(const VECTOR& up) { m_upVector = up; }

VECTOR CameraComponent::GetPosition() const { return m_position; }
VECTOR CameraComponent::GetTarget() const { return m_target; }
VECTOR CameraComponent::GetUpVector() const { return m_upVector; }

void CameraComponent::ApplyToDxLibCamera() const
{
    SetCameraPositionAndTargetAndUpVec(m_position, m_target, m_upVector);
}

void CameraComponent::Update() {}
void CameraComponent::Draw() {}

//#include "CameraComponent.h"
//
//// コンストラクタ
//CameraComponent::CameraComponent()
//    : m_cameraPosition(VGet(0.0f, 5.0f, -10.0f))
//    , m_target(VGet(0.0f, 0.0f, 0.0f))
//    , m_up(VGet(0.0f, 1.0f, 0.0f))
//    , m_fov(DX_PI_F / 4.0f)     // 約45度
//    , m_nearClip(1.0f)
//    , m_farClip(1000.0f)
//{
//}
//
//// カメラの位置設定
//void CameraComponent::SetPosition(const VECTOR& pos)
//{
//    m_cameraPosition = pos;
//}
//
//// 注視点の設定
//void CameraComponent::SetTarget(const VECTOR& tgt)
//{
//    m_target = tgt;
//}
//
//// 上方向ベクトルの設定
//void CameraComponent::SetUpVector(const VECTOR& upVec)
//{
//    m_up = upVec;
//}
//
//// DxLibにこのカメラの情報を適用
//void CameraComponent::ApplyToDxLibCamera() const
//{
//    SetCameraPositionAndTarget_UpVecY(m_cameraPosition, m_target);
//    SetCameraNearFar(m_nearClip, m_farClip);
//	// 将来的にはFOVの設定も追加するかも
//}
//
//// Component の純粋仮想関数の空実装
//void CameraComponent::Draw()
//{
//    // カメラ自体は描画対象ではないため、ここは空でOK
//}