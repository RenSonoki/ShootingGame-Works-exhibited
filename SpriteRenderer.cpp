#include "SpriteRenderer.h"

// コンストラクタ
SpriteRenderer::SpriteRenderer(const std::wstring& imagePath)
	: m_handle(-1)          // 画像ハンドルの初期値（無効な状態）
	, m_originalWidth(0)    // 元の画像幅の初期値
	, m_originalHeight(0)   // 元の画像高さの初期値
	, m_visible(true)       // 初期状態は表示
{
    // 画像の読み込み（ファイルパス指定）
	// LoadGraph は画像ファイルを読み込み、グラフィックハンドルを返す
	// c_str() で std::wstring から const wchar_t* に変換
    m_handle = LoadGraph(imagePath.c_str());

    // 読み込み成功時に画像サイズを取得して保存
    if (m_handle != -1)
    {
        GetGraphSize(m_handle, &m_originalWidth, &m_originalHeight);
    }
}

// 描画処理
void SpriteRenderer::Draw()
{
    // 非表示または画像ハンドルが無効な場合は描画をスキップ
    if (!m_visible || m_handle == -1)
        return;

    // 位置・スケール・回転情報を取得
    VECTOR2 pos = m_transform.GetPosition();
    VECTOR2 scale = m_transform.GetScale();
    float rotation = m_transform.GetRotation();

    // 画像の中心点（回転・スケールの基準）
    int centerX = m_originalWidth / 2;
    int centerY = m_originalHeight / 2;

    // 中心回転付きのスプライト描画
	// DXライブラリの DrawRotaGraph2 関数を使用
    DrawRotaGraph2
    (
        static_cast<int>(pos.x),     // 描画中心位置 X
        static_cast<int>(pos.y),     // 描画中心位置 Y
        centerX,                     // 回転・拡大の基準点 X（画像の中心）
        centerY,                     // 回転・拡大の基準点 Y（画像の中心）
        scale.x,                     // スケーリング X（Y方向は使っていない）
        rotation,                    // 回転角（ラジアン）
        m_handle,                    // グラフィックハンドル
        TRUE                         // 透過描画ON
    );
}

// 表示フラグを設定
void SpriteRenderer::SetVisible(bool visible)
{
    m_visible = visible;
}

// 表示フラグを取得
bool SpriteRenderer::IsVisible() const
{
    return m_visible;
}

// 元の画像幅を取得
int SpriteRenderer::GetOriginalWidth() const
{
    return m_originalWidth;
}

// 元の画像高さを取得
int SpriteRenderer::GetOriginalHeight() const
{
    return m_originalHeight;
}

// Transform2D オブジェクトへの参照を取得
// 外部から位置・スケール・回転の制御が可能
Transform2D& SpriteRenderer::GetTransform()
{
    return m_transform;
}