#pragma once

#include <string>
#include "UIComponent.h"
#include "Transform2D.h"

// UI 上に文字列を描画するためのコンポーネント
// HUD、メニュー、スコア表示などに使用可能
class UIText : public UIComponent
{
public:
    // コンストラクタ：表示するテキストと初期色を指定
    UIText(const std::wstring& text, unsigned int color);

    // テキストを描画する（フォントサイズ、色、位置に基づいて描画）
    void Draw() override;

    // 表示するテキスト内容を変更
    void SetText(const std::wstring& text);

    // 文字色を変更する（DxLib の GetColor 関数などで取得した RGB 値）
    void SetColor(unsigned int color);

    // フォントサイズを変更する（描画サイズに影響）
    void SetFontSize(int size);

    // テキストの位置・拡大率・回転などを取得／変更するための Transform
    Transform2D& GetTransform();

    // 表示フラグを設定（true = 表示、false = 非表示）
    void SetVisible(bool visible) override;

    // 現在の表示状態を取得
    bool IsVisible() const override;

private:
    std::wstring m_text;      // 表示する文字列（Unicode対応）
    unsigned int m_color;     // 描画する文字の色（RGB値）
    int m_fontSize;           // フォントサイズ（ピクセル単位）
    bool m_visible;           // 表示フラグ

    Transform2D m_transform;  // テキストの位置・スケール・回転など
};