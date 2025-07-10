#pragma once
#include "Transform2D.h"

// Transform2Dを使用してUI要素の位置、回転、スケールを管理するためのインターフェース
// UIの基底クラス（全てのUI要素の親）
// 他の抽象クラスよりも具体的な実装を持っている
// メリット: UI要素の共通機能を提供し、Transform2Dを利用して位置や回転、スケールを管理できる
class UIComponent
{
protected:
	bool m_visible;             // 表示状態
	Transform2D m_transform;    // 2D変形情報（位置、回転、スケールなど）

public:
    UIComponent();
    virtual ~UIComponent() = default;

    // 毎フレーム描画処理（継承先で実装）
    virtual void Draw() = 0;

    // 表示／非表示切り替え
    virtual void SetVisible(bool visible) = 0;
    virtual bool IsVisible() const = 0;

    // Transform2D の取得・設定
    Transform2D& GetTransform();
    const Transform2D& GetTransform() const;
};

// 現状インターフェースとしては、
// 処理を持ちすぎているため、抽象クラスとしての役割を果たしていない
// 修正案としては、UIComponentを抽象クラスにして、
// 別のクラスでTransform2Dを管理するようにすることが考えられる