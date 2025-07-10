// CameraComponent.h
#pragma once

#include "Component.h"
#include "DxLib.h"

// カメラの位置・注視点・アップベクトルを管理するコンポーネント
class CameraComponent : public Component
{
public:
    CameraComponent();

    void SetPosition(const VECTOR& pos);
    void SetTarget(const VECTOR& target);
    void SetUpVector(const VECTOR& up);

    VECTOR GetPosition() const;
    VECTOR GetTarget() const;
    VECTOR GetUpVector() const;

    void ApplyToDxLibCamera() const;

    void Update() override;
    void Draw() override;

private:
    VECTOR m_position;
    VECTOR m_target;
    VECTOR m_upVector;
};

//#pragma once
//#include "Component.h"
//#include "DxLib.h"
//
//// カメラの状態（位置・注視点・視野など）を保持するコンポーネント
//class CameraComponent : public Component
//{
//public:
//	// カプセル化の観点から将来的にメンバ変数はprivateにする
//
//    // カメラの位置
//    VECTOR m_cameraPosition;
//
//    // 注視点（カメラが見る方向の座標）
//    VECTOR m_target;
//
//    // 上方向ベクトル（通常 VGet(0, 1, 0)）
//    VECTOR m_up;
//
//    // 視野角（ラジアン単位）
//    float m_fov;
//
//    // クリップ距離
//    float m_nearClip;
//    float m_farClip;
//
//    // コンストラクタ
//    CameraComponent();
//
//    // 各種設定
//    void SetPosition(const VECTOR& pos);
//    void SetTarget(const VECTOR& tgt);
//    void SetUpVector(const VECTOR& upVec);
//
//    // DxLibのカメラに反映
//    void ApplyToDxLibCamera() const;
//
//    // Component の純粋仮想関数を実装（空実装）
//    void Draw() override;
//};