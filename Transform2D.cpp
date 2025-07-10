#include "Transform2D.h"

Transform2D::Transform2D()
    : m_position({ 0.0f, 0.0f })  // 初期位置は原点 (0, 0)
    , m_scale({ 1.0f, 1.0f })     // スケールは等倍 (1, 1)
    , m_rotation(0.0f)            // 回転角は 0 ラジアン（回転なし）
{
}

// 位置を設定（ベクトルで一括指定）
void Transform2D::SetPosition(const VECTOR2& pos)
{
    m_position = pos;
}

// 現在の位置を取得
VECTOR2 Transform2D::GetPosition() const
{
    return m_position;
}

// スケールを設定（ベクトルで一括指定）
void Transform2D::SetScale(const VECTOR2& scale)
{
    m_scale = scale;
}

// 現在のスケールを取得
VECTOR2 Transform2D::GetScale() const
{
    return m_scale;
}

// 回転角を設定（ラジアン単位、時計回りが正）
void Transform2D::SetRotation(float rot)
{
    m_rotation = rot;
}

// 現在の回転角を取得
float Transform2D::GetRotation() const
{
    return m_rotation;
}