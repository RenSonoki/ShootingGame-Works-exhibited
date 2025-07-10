#include "UIComponent.h"

// コンストラクタ
// 初期状態では表示フラグを true（表示）にする
UIComponent::UIComponent()
    : m_visible(true)
{

}

// 表示・非表示を切り替える
// true：表示
// false：非表示（Draw() 側判定に使用）
void UIComponent::SetVisible(bool visible)
{
    m_visible = visible;
}

// 現在の表示状態を取得
// true：表示中
// false：非表示
bool UIComponent::IsVisible() const
{
    return m_visible;
}

// UIコンポーネントの Transform2D への参照を返す（読み書き可能）
// 位置・スケーリング・回転などの情報を操作できる
Transform2D& UIComponent::GetTransform()
{
    return m_transform;
}

// UIコンポーネントの Transform2D への参照を返す（読み取り専用）
// 外部から Transform 情報を参照したい場合に使う
const Transform2D& UIComponent::GetTransform() const
{
    return m_transform;
}