#pragma once
#include "DxLib.h"

// 2Dベクトル構造体
// UIや2Dオブジェクトの位置・スケールを表すために使用
struct VECTOR2
{
    float x;
    float y;
};

// UIや2D描画用オブジェクトに共通するTransform情報を管理するクラス
class Transform2D
{
private:
    VECTOR2 m_position;  // 位置（左上を基準としたX, Y座標）
    VECTOR2 m_scale;     // スケール（拡大率: 1.0f = 等倍）
    float   m_rotation;  // 回転角（ラジアン単位、時計回り）

public:
    // コンストラクタ
    Transform2D();

    // 位置の設定
    void SetPosition(const VECTOR2& pos);  // 位置を一括で設定
    // 位置を取得
    VECTOR2 GetPosition() const;           

    // スケールの設定
    void SetScale(const VECTOR2& scale);  // スケールを一括で設定
    // スケールを取得
    VECTOR2 GetScale() const;             

    // 回転の設定（ラジアン単位）
    void SetRotation(float rot); 
	// 回転を取得（ラジアン単位）
    float GetRotation() const;

    // 個別のX座標・Y座標の取得（操作しやすさ重視）
    float GetX() const { return m_position.x; }
    float GetY() const { return m_position.y; }

	// 個別のX座標・Y座標の設定
    void SetX(float x) { m_position.x = x; }
    void SetY(float y) { m_position.y = y; }
};