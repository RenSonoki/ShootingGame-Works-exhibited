#include "UISystem.h"

void UISystem::AddComponent(std::shared_ptr<UIComponent> component)
{
    m_components.push_back(component);
}

void UISystem::Draw()
{
    for (const auto& component : m_components)
    {
        if (component->IsVisible())
        {
            component->Draw();
        }
    }
}

const std::vector<std::shared_ptr<UIComponent>>& UISystem::GetComponents() const
{
    return m_components;
}

std::shared_ptr<UIComponent> UISystem::GetComponent(size_t index) const
{
    if (index < m_components.size())
    {
        return m_components[index];
    }
    return nullptr;
}

//#include "UISystem.h"
//
//// UIComponent をシステムに追加
//// 描画順は追加順となる（後に追加されたものほど上に描画される）
//void UISystem::AddComponent(const std::shared_ptr<UIComponent>& component)
//{
//    m_components.push_back(component);
//}
//
//// 登録されている UIComponent をすべて描画する
//// 非表示（IsVisible() == false）のものは描画しない
//void UISystem::Draw()
//{
//    for (const auto& component : m_components)
//    {
//        // null チェックと表示フラグを確認
//        if (component && component->IsVisible())
//        {
//            component->Draw();  // 実際の描画処理を呼び出し
//        }
//    }
//}
//
//// 登録されたすべての UIComponent を削除する
//// シーン遷移や UI 再構築時に使用
//void UISystem::Clear()
//{
//    m_components.clear();  // 内部 vector を空にする
//}
//
//// 指定されたインデックスの UIComponent を取得する
//// 範囲外アクセスを防止し、安全に nullptr を返す
//std::shared_ptr<UIComponent> UISystem::GetComponent(size_t index) const
//{
//    if (index < m_components.size())
//    {
//        return m_components[index];  // 有効なインデックスなら返す
//    }
//    return nullptr;  // 無効な場合は null を返す
//}