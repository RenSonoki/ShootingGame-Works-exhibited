#include "UIManager.h"

// UIシステム（UISystem）を名前で登録する
// 同一名があれば上書きされる
void UIManager::AddSystem(const std::string& name, std::shared_ptr<UISystem> system)
{
	m_systems[name] = system;       // 名前をキーにしてシステムを登録
}

// 指定された名前のUIシステムを取得する
// 見つからない場合は nullptr を返す
std::shared_ptr<UISystem> UIManager::GetSystem(const std::string& name) const
{
    auto it = m_systems.find(name);  // 名前で検索
    if (it != m_systems.end())
    {
        return it->second;           // 見つかった場合はシステムを返す
    }
    return nullptr;                  // 見つからなければ null
}

// 登録されているすべてのUIシステムに対して描画処理を行う
void UIManager::DrawAll()
{
    for (const auto& pair : m_systems)
    {
        if (pair.second)  // nullチェック（nullptrでもクラッシュしないように）
        {
            pair.second->Draw();  // 各UIシステムに描画を依頼
        }
    }
}

// 登録されているすべてのUIシステムを削除する
// → シーン遷移などでUIを一括リセットしたいときに使用
void UIManager::Clear()
{
    m_systems.clear();
}
