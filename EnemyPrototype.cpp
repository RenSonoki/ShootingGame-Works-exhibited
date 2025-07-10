#include "EnemyPrototype.h"
#include "TransformComponent.h"
#include "RenderModelComponent.h"

// コンストラクタ
// EnemyEntity のプロトタイプを初期化
// modelHandle は敵モデルの識別用ハンドル、pos は初期位置
// EnemyEntity のコンストラクタを呼び出し、モデルハンドルと位置を設定
EnemyPrototype::EnemyPrototype(int modelHandle, VECTOR pos)
    : EnemyEntity(modelHandle, pos)
    , m_modelHandle(modelHandle)
{

}

// Clone メソッド：EnemyEntity のプロトタイプを複製して返す
std::shared_ptr<Entity> EnemyPrototype::Clone() const
{
    // 新しい EnemyEntity のインスタンスを作成
	// make_sharedはメモリ管理を自動化し、スマートポインタを使用して安全にオブジェクトを管理する関数
    auto clone = std::make_shared<EnemyEntity>(m_modelHandle, VGet(0, 0, 0));

    // 複製したエンティティの初期化
    clone->m_enemyTransform->velocity = VGet(0, 0, 0);  // 速度を初期化（移動しない状態で生成）
    clone->m_shotTimer = 0;                        // 弾発射タイマーをリセット
    clone->active = true;                        // アクティブ状態に設定

    return clone; // 複製したエンティティを返す
}

