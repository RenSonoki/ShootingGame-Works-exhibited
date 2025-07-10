// BulletPrototype.cpp
#include "BulletPrototype.h"
#include "BulletEntity.h"

BulletPrototype::BulletPrototype(VECTOR basePosition)
    : m_basePosition(basePosition)
{
}

std::shared_ptr<Entity> BulletPrototype::Clone() const
{
    auto bullet = std::make_shared<BulletEntity>();
    bullet->transform->position = m_basePosition;
    return bullet;
}

//#include "BulletPrototype.h"
//
//BulletPrototype::BulletPrototype(int modelHandle, VECTOR spawnOffset)
//    : m_modelHandle(modelHandle), m_spawnOffset(spawnOffset)
//{
//}
//
//std::shared_ptr<Entity> BulletPrototype::Clone() const
//{
//    auto bullet = std::make_shared<BulletEntity>(m_modelHandle);
//    bullet->transform->position = m_spawnOffset;
//    bullet->transform->velocity = VGet(0, 0, 0.7f);
//    return bullet;
//}
