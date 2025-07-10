#include "UIImage.h"

// 単純にSpriteRendererのコンストラクタを呼び出すだけで画像の初期化
UIImage::UIImage(const std::wstring& imagePath)
    : SpriteRenderer(imagePath)
{
    // UI特有の初期化が必要な場合はここに記述
}
