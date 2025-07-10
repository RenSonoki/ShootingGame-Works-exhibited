#include "CameraSystem.h"

// CameraSystemのコンストラクタ
void CameraSystem::AddCamera(const std::shared_ptr<CameraComponent>& camera)
{
	// push_backでカメラを追加
    m_cameras.push_back(camera);

    // 最初に追加されたカメラをアクティブにする
    if (m_activeCameraIndex == -1)
    {
        m_activeCameraIndex = 0;
    }
}

void CameraSystem::SetActiveCamera(int index)
{
	// インデックスが有効な範囲内であればアクティブカメラを設定
    if (index >= 0 && index < static_cast<int>(m_cameras.size()))
    {
        m_activeCameraIndex = index;
    }
}

std::shared_ptr<CameraComponent> CameraSystem::GetActiveCamera() const
{
	// アクティブなカメラが有効なインデックスであれば返す
    if (m_activeCameraIndex >= 0 && m_activeCameraIndex < static_cast<int>(m_cameras.size()))
    {
        return m_cameras[m_activeCameraIndex];
    }
    return nullptr;
}

void CameraSystem::ApplyActiveCamera()
{
	// autoキーワードを使用してアクティブなカメラを取得
    auto camera = GetActiveCamera();
    if (camera)
    {
        camera->ApplyToDxLibCamera();
    }
}

int CameraSystem::GetCameraCount() const
{
    return static_cast<int>(m_cameras.size());
}