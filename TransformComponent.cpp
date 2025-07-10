#include "TransformComponent.h"

// デフォルトコンストラクタ
TransformComponent::TransformComponent()
    : position(VGet(0, 0, 0))   // 初期位置
    , velocity(VGet(0, 0, 0))   // 初期速度
    , rotation(VGet(0, 0, 0))   // 初期回転
{
}

// 位置だけ指定するコンストラクタ
// 使用例：特定の位置から開始したい場合
TransformComponent::TransformComponent(VECTOR pos)
    : position(pos)                    // 指定された位置で初期化
    , velocity(VGet(0, 0, 0))          // 初期速度はゼロ
    , rotation(VGet(0, 0, 0))          // 初期回転もゼロ
{
}

// 毎フレーム呼び出される更新処理：
// 速度ベクトルを現在位置に加算 -> これにより速度に応じてオブジェクトの位置が更新される
void TransformComponent::Update()
{
    position = VAdd(position, velocity);
}

// （描画は他の RenderComponent 等が担当する想定）
void TransformComponent::Draw()
{
    // 空実装
}