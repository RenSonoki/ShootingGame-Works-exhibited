#pragma once

#include "UIComponent.h"
#include "Transform2D.h"
#include <string>
#include <DxLib.h>

// 設計のポイント
// 再利用性：スプライト描画機能を単体コンポーネントとして切り出すことで、UI要素に簡単に適用できる
// 拡張性  ：Transform2D による柔軟な配置・拡大縮小・回転が可能
// 一貫性  ：UIComponent を継承し、ポリモーフィズムを活かした一括描画管理を実現

// 画像を読み込み、Transform2D を通じて位置・スケール・回転を制御する抽象クラス
// UIComponent を継承することで、他のUIコンポーネントと共通のインターフェースを持ち、
// シーン全体での一括更新・描画制御を容易にする
class SpriteRenderer : public UIComponent
{
protected:
    int m_handle;             // DxLib 画像ハンドル（LoadGraph で取得）
    int m_originalWidth;      // 読み込み時の画像幅（スケーリングの基準）
    int m_originalHeight;     // 読み込み時の画像高さ
    bool m_visible;           // 表示／非表示のフラグ（UI管理用）

    Transform2D m_transform;  // 2Dトランスフォーム（位置・拡大縮小・回転）

public:
    // コンストラクタ
    // imagePath: 画像ファイルのパス（ワイド文字列）
    // 指定された画像を読み込んで初期化
    SpriteRenderer(const std::wstring& imagePath);

    // 描画処理
    // Transform2D の情報に従ってスプライトを拡大／回転して描画
    void Draw() override;

	// 表示,非表示の切り替え
    void SetVisible(bool visible) override;

	// 現在の表示状態を取得
    bool IsVisible() const override;

    // 読み込んだ画像の元の幅を取得（スケール計算などに使用）
    int GetOriginalWidth() const;

    // 読み込んだ画像の元の高さを取得（スケール計算などに使用）
    int GetOriginalHeight() const;

    // Transform2D への参照を返す
    // - 位置・スケール・回転の設定に使用
    Transform2D& GetTransform();
};

// 現状インターフェースとしては、所有している処理が多く、
// インターフェースとしては疑問が残るため、別のクラスに分離することも検討
