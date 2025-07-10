#pragma once
#include "CameraComponent.h"
#include <vector>
#include <memory>

// カメラコンポーネントを管理し、現在アクティブなカメラを適用するシステム
// このシステムは、複数のカメラを管理し、必要に応じてアクティブなカメラを切り替えることができます。
class CameraSystem
{
public:
    // カメラを登録
    void AddCamera(const std::shared_ptr<CameraComponent>& camera);

    // アクティブカメラを切り替える
    void SetActiveCamera(int index);

    // アクティブカメラを取得
    std::shared_ptr<CameraComponent> GetActiveCamera() const;

    // DxLib カメラに現在のカメラを適用
    void ApplyActiveCamera();

    // 登録済みのカメラ数
    int GetCameraCount() const;

private:
    std::vector<std::shared_ptr<CameraComponent>> m_cameras;
    int m_activeCameraIndex = -1; // -1 は未選択状態
};

// Camera関連クラスの動作
//[CameraController] --->位置の更新（TransformComponent）
//↓
//[CameraEntity] ------->CameraComponent に値を渡し、ApplyCamera()
//↓
//[CameraComponent] --->SetCameraPositionAndTarget_UpVecY などで DxLib に適用
//↓
//[CameraSystem]   ---- > （複数あれば）どの CameraEntity を描画時に適用するか決定