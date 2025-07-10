#include "BulletEntity.h"
#include "DxLib.h"

BulletEntity::BulletEntity()
{
    active = true;
    transform = std::make_shared<TransformComponent>();
    AddComponent(transform);
}

void BulletEntity::Update()
{
    // 速度によって位置を更新
    transform->position = VAdd(transform->position, transform->velocity);

    //範囲外で無効化
    if (transform->position.z > 500.0f || transform->position.z < -500.0f ||
        transform->position.x < -500.0f || transform->position.x > 500.0f)
    {
        active = false;
    }
}

void BulletEntity::Draw()
{
	// 球を描画 (位置、半径、セグメント数、色1、色2、線形描画フラグ)
	// ここでは赤色の球を描画
    DrawSphere3D(transform->position, 1.0f, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
}

//#include "BulletEntity.h"
//#include "BulletRenderComponent.h"
//
//BulletEntity::BulletEntity(int modelHandle)
//    : m_modelHandle(modelHandle)
//{
//    active = true;
//
//    // Transform を追加
//    transform = std::make_shared<TransformComponent>();
//    AddComponent(transform);
//
//    // モデル描画コンポーネントを追加
//    AddComponent(std::make_shared<BulletRenderComponent>(transform, m_modelHandle));
//}
//
//void BulletEntity::Update()
//{
//    transform->position = VAdd(transform->position, transform->velocity);
//
//    if (transform->position.z > 100.0f || transform->position.z < -50.0f ||
//        transform->position.x < -50.0f || transform->position.x > 50.0f)
//    {
//        active = false;
//    }
//}
