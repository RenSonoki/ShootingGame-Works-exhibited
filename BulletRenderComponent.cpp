// BulletRenderComponent.cpp
#include "BulletRenderComponent.h"
#include "DxLib.h"

BulletRenderComponent::BulletRenderComponent(std::shared_ptr<TransformComponent> transform, float radius)
    : m_transform(transform), m_radius(radius) {
}

void BulletRenderComponent::Draw() {
    if (m_transform) {
        DrawSphere3D(m_transform->position, m_radius, 8, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);
    }
}

//#include "BulletRenderComponent.h"
//#include "DxLib.h"
//
//BulletRenderComponent::BulletRenderComponent(std::shared_ptr<TransformComponent> transform, int modelHandle)
//    : m_transform(transform), m_modelHandle(modelHandle)
//{
//}
//
//void BulletRenderComponent::Draw()
//{
//    if (m_modelHandle != -1)
//    {
//        MV1SetPosition(m_modelHandle, m_transform->position);
//        MV1DrawModel(m_modelHandle);
//    }
//}
