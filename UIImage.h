#pragma once
#include "SpriteRenderer.h"

// UI画像を表示するコンポーネントクラス（ボタン・アイコン・ロゴなどに使用）
// ボタン・アイコン・ロゴ・装飾など、静的なUI画像表示を担う
class UIImage : public SpriteRenderer
{
public:
    // コンストラクタ：画像パスを指定
    UIImage(const std::wstring& imagePath);

    // 必要に応じてUIImage固有の処理を追加可能
};