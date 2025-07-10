#include "EntitySystem.h"


void EntitySystem::AddEntity(std::shared_ptr<Entity> entity)
{
    // エンティティリストに新しいエンティティを追加
    m_entities.push_back(entity);
}

void EntitySystem::Update()
{
    // エンティティリスト内のすべてのエンティティに対して更新処理を実行
    for (auto& entity : m_entities)
    {
        if (entity->active)
        {
            // active フラグが true のエンティティのみ更新
            entity->Update();
        }
    }
}

void EntitySystem::Draw()
{
    // エンティティリスト内のすべてのエンティティに対して描画処理を実行
    for (auto& entity : m_entities)
    {
        if (entity->active)
        {
            // active フラグが true のエンティティのみ描画
            entity->Draw();
        }
    }
}