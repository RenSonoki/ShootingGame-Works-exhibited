// CameraController.h
#pragma once

#include "CameraComponent.h"
#include "TransformComponent.h"
#include <memory>

// カメラの位置や注視点を追従・制御するコントローラー
class CameraController
{
public:
    CameraController(std::shared_ptr<CameraComponent> camera);

    void SetTarget(std::shared_ptr<TransformComponent> target);
    void Update();

private:
    std::shared_ptr<CameraComponent> m_camera;
    std::shared_ptr<TransformComponent> m_target;

    float m_distance = 30.0f;
    float m_height = 20.0f;
    float m_lookAheadDistance = 5.0f;  // プレイヤー前方5mを注視
    float m_lookDownOffset = 2.0f;     // 少し下方向を見る
};

//#pragma once
//#include "CameraComponent.h"
//#include "TransformComponent.h"
//#include <memory>
//
//// Transform に追従して CameraComponent を操作するコントローラー
//// CameraComponent は「状態」
//// CameraController は「動きの制御」に分離
//class CameraController
//{
//public:
//    // カメラの操作対象（CameraComponent）を渡す
//    CameraController(std::shared_ptr<CameraComponent> camera);
//
//    // ターゲット（追従対象）を設定
//    void SetTarget(std::shared_ptr<TransformComponent> target);
//
//    // 毎フレーム呼ばれる更新処理
//    void Update();
//
//private:
//    std::shared_ptr<CameraComponent> m_camera;
//    std::shared_ptr<TransformComponent> m_target;
//};
