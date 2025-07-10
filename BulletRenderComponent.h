// BulletRenderComponent.h
#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include <memory>

class BulletRenderComponent : public Component {
public:
    BulletRenderComponent(std::shared_ptr<TransformComponent> transform, float radius = 0.5f);
    void Update() override {}
    void Draw() override;

private:
    std::shared_ptr<TransformComponent> m_transform;
    float m_radius;
};

//#pragma once
//
//#include "Component.h"
//#include "TransformComponent.h"
//#include <memory>
//
//class BulletRenderComponent : public Component
//{
//public:
//    BulletRenderComponent(std::shared_ptr<TransformComponent> transform, int modelHandle);
//
//    void Update() override {}
//    void Draw() override;
//
//private:
//    std::shared_ptr<TransformComponent> m_transform;
//    int m_modelHandle;
//};