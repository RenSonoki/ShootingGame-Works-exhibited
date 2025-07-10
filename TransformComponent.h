#pragma once
#include "Component.h"
#include "DxLib.h"

// エンティティ(ゲームオブジェクト)の位置・速度・回転を管理する基本的な空間情報コンポーネント
// ゲームオブジェクトの移動・回転制御や描画位置の参照に使用
class TransformComponent : public Component
{
public:
    // --- 空間プロパティ ---
    // 変数はprivateにして、Get/Set関数を通じてアクセスすることが推奨される(カプセル化)
    // 将来的に作り直す
    
    // 位置ベクトル（ワールド座標上の位置を表す）
    VECTOR position;

    // 速度ベクトル（毎フレーム加算される移動量）
    VECTOR velocity;

    // 回転ベクトル（X, Y, Z軸の回転角度を表す。単位はラジアンまたは度数で統一が必要）
    VECTOR rotation;

    // デフォルトコンストラクタ
    TransformComponent();

    // 引数付きコンストラクタ：初期位置を指定して初期化
    TransformComponent(VECTOR pos);

    // 毎フレーム呼ばれる更新処理
    void Update() override;

    // デバッグ用途などで位置表示する際に呼ばれる
    void Draw() override;
};