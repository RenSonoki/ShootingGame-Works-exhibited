#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "UISystem.h"

// 複数の UISystem（UI レイヤー）を管理するクラス
// 例: "TitleUI", "HUD", "PauseMenu" など名前付きで管理
class UIManager
{
public:
    // UISystem を名前付きで登録
    void AddSystem(const std::string& name, std::shared_ptr<UISystem> system);

    // 名前で UISystem を取得（存在しなければ nullptr を返す）
    std::shared_ptr<UISystem> GetSystem(const std::string& name) const;

    // 登録されているすべての UISystem を描画
    void DrawAll();

    // 全 UISystem をクリア（シーン遷移などに）
    void Clear();

private:
	// UISystem を名前で管理するマップ
    std::unordered_map<std::string, std::shared_ptr<UISystem>> m_systems;
};