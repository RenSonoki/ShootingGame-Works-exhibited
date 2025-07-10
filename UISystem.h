#pragma once

#include <vector>
#include <memory>
#include "UIComponent.h"

// UIComponent を保持・描画するレイヤー的な役割を担うクラス
class UISystem
{
public:
    // コンポーネントを追加
    void AddComponent(std::shared_ptr<UIComponent> component);

    // 全てのUIコンポーネントを描画（Visibleフラグを考慮）
    void Draw();

    // コンポーネント一覧を取得（アニメーションなどでアクセス用）
    const std::vector<std::shared_ptr<UIComponent>>& GetComponents() const;

    std::shared_ptr<UIComponent> GetComponent(size_t index) const;

private:
    std::vector<std::shared_ptr<UIComponent>> m_components; // UI要素のリスト
};

//#pragma once
//#include <vector>
//#include <memory>
//#include "UIComponent.h"
//
//// 単一の UI レイヤー（HUD や タイトル画面 UI など）を表現するクラス
//// UIComponent を複数保持し、描画や一括制御を可能
//class UISystem
//{
//public:
//    // UIComponent をリストに追加
//    // 描画順は追加順になる（上に積み重なるように）
//    void AddComponent(const std::shared_ptr<UIComponent>& component);
//
//    // 登録されているすべての UIComponent を順番に描画
//    // 通常は毎フレーム呼び出す
//    void Draw();
//
//    // すべての UIComponent を削除
//    // シーン切り替えや UI リセット時に使用
//    void Clear();
//
//    // 指定インデックスの UIComponent を取得
//    // 存在しないインデックスを指定した場合は nullptr を返す
//    std::shared_ptr<UIComponent> GetComponent(size_t index) const;
//
//private:
//    // 登録されている UIComponent のリスト（保持順に描画）
//    std::vector<std::shared_ptr<UIComponent>> m_components;
//};