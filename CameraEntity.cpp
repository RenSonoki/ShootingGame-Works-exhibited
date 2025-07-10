#include "CameraEntity.h"

CameraEntity::CameraEntity()
{
    m_cameraComponent = std::make_shared<CameraComponent>();
    m_cameraController = std::make_shared<CameraController>(m_cameraComponent);

    AddComponent(m_cameraComponent);
}

void CameraEntity::Update()
{
    if (m_cameraController)
    {
        m_cameraController->Update();  // ‚±‚±‚ÅƒJƒƒ‰î•ñ‚ğ DxLib ‚É”½‰f
    }
}

//#include "CameraEntity.h"
//
//CameraEntity::CameraEntity()
//{
//    m_cameraComponent = std::make_shared<CameraComponent>();
//    AddComponent(m_cameraComponent);
//
//    m_cameraController = std::make_shared<CameraController>(m_cameraComponent);
//}
//
//std::shared_ptr<CameraController> CameraEntity::GetCameraController()
//{
//    return m_cameraController;
//}

//// CameraEntity.cpp
//#include "CameraEntity.h"
//
//CameraEntity::CameraEntity()
//{
//    m_cameraComponent = std::make_shared<CameraComponent>();
//    AddComponent(m_cameraComponent);
//}
//
//std::shared_ptr<CameraComponent> CameraEntity::GetCameraComponent() const
//{
//    return m_cameraComponent;
//}
