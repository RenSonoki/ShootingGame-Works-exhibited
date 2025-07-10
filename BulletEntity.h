#pragma once

#include "Entity.h"
#include "TransformComponent.h"
#include <memory>

// 弾エンティティ：球体で描画される
class BulletEntity : public Entity
{
public:
    BulletEntity();

    void Update() override;
    void Draw() override;

    std::shared_ptr<TransformComponent> transform;
};

//#pragma once
//
//#include "Entity.h"
//#include "TransformComponent.h"
//#include <memory>
//
//// 弾エンティティ（プレイヤー・敵共用）
//class BulletEntity : public Entity
//{
//public:
//    BulletEntity(int modelHandle);
//
//    std::shared_ptr<TransformComponent> transform;
//
//    void Update() override;
//
//private:
//    int m_modelHandle; // モデルの描画用ハンドル
//};
