#pragma once

#include "Component.h"
#include "DxLib.h"
#include "TransformComponent.h"
#include <memory>
#include <string>

// 2Dスプライト画像を描画するためのコンポーネント
// 現在はUIシステムによる置き換えを予定、将来的には廃止(UIシステム実装前に作成されたため)
class SpriteRendererComponent : public Component
{
private:
    int m_graphHandle;  // DxLibで取得した画像のハンドル（LoadGraph 等で取得）

    // 画像の描画位置やスケーリング、回転を管理するTransform
    // UI専用Transformとして流用
    std::shared_ptr<TransformComponent> m_spriteTransform;

    float m_scale = 1.0f;     // スプライトのスケーリング倍率（1.0で等倍）
    bool m_centered = false;  // trueならスプライトの中心を基準に描画（falseなら左上基準）
    int m_alpha = 255;        // スプライトの透明度（0 = 完全透明, 255 = 不透明）

public:
    // コンストラクタ
    SpriteRendererComponent(int handle, std::shared_ptr<TransformComponent> tf);

    // 描画倍率（スケール）を設定
    void SetScale(float scale) { m_scale = scale; }

    // スプライトを中央基準で描画するかどうかを設定
    void SetCentered(bool centered) { m_centered = centered; }

    // スプライトの透明度（アルファ値）を設定（0?255）
    void SetAlpha(int alpha) { m_alpha = alpha; }

    // スプライトは2D表示で動的変化が少ないため、通常は更新処理は不要
    void Update() override {}

    // スプライトを画面に描画する（位置・スケール・中心揃え・透明度を反映）
    void Draw() override;
};