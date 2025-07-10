// Componentを持つEntityクラス
// これにより、可変長配列でComponentを自由に追加できるようになります
#include "Entity.h"

// AddComponent メソッド：新しいコンポーネントをエンティティに追加
// std::shared_ptr<Component> を引数として受け取り、エンティティのコンポーネントリストに追加する
void Entity::AddComponent(std::shared_ptr<Component> component)
{
    // componentsベクターに新しいコンポーネントを追加
    m_components.push_back(component);
}

// Update メソッド：全てのコンポーネントを更新
void Entity::Update()
{
    // componentsリストの各コンポーネントに対してUpdateを呼び出す
    for (auto& comp : m_components)
    {
        comp->Update();  // 各コンポーネントのUpdate処理を実行
    }
}

// Draw メソッド：全てのコンポーネントを描画
void Entity::Draw()
{
    // componentsリストの各コンポーネントに対してDrawを呼び出す
    for (auto& comp : m_components)
    {
        comp->Draw();  // 各コンポーネントのDraw処理を実行
    }
}