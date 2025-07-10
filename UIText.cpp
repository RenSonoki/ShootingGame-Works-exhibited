#include "UIText.h"
#include "DxLib.h"

// コンストラクタ
UIText::UIText(const std::wstring& text, unsigned int color)
	: m_text(text)      // 初期表示するテキスト
	, m_color(color)    // 初期表示する文字色（RGB値を想定）
    , m_fontSize(20)    // デフォルトのフォントサイズを 20 に設定
    , m_visible(true)   // 初期状態では表示状態にする
{
}

// テキスト描画処理
// フォントサイズと位置・色を考慮して文字列を描画
void UIText::Draw()
{
    if (!m_visible) return;  // 非表示フラグが立っている場合は何も描画しない

    // 現在のフォントサイズを保存（他UIと干渉しないように）
    int oldSize = GetFontSize();
    SetFontSize(m_fontSize);  // 指定されたフォントサイズに一時変更

    // 文字列を描画（Transform で指定された位置に表示）
    DrawString
    (
        static_cast<int>(m_transform.GetX()),  // X座標
        static_cast<int>(m_transform.GetY()),  // Y座標
        m_text.c_str(),                         // 描画するテキスト
        m_color                                 // 文字色
    );

    // フォントサイズを元に戻す（副作用防止）
    SetFontSize(oldSize);
}

// 表示テキストを変更する
void UIText::SetText(const std::wstring& text)
{
    m_text = text;
}

// テキストカラーを変更する（RGB値を想定）
void UIText::SetColor(unsigned int color)
{
    m_color = color;
}

// フォントサイズを変更する（ピクセル単位）
void UIText::SetFontSize(int size)
{
    m_fontSize = size;
}

// Transform2D を取得：位置・スケール・回転などの操作用
Transform2D& UIText::GetTransform()
{
    return m_transform;
}

// 表示フラグを設定（false にすると Draw は無視される）
void UIText::SetVisible(bool visible)
{
    m_visible = visible;
}

// 現在の表示状態を取得（true = 表示中）
bool UIText::IsVisible() const
{
    return m_visible;
}