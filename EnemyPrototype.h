#pragma once
#include "EnemyEntity.h"
#include "EntityPrototype.h"

// EnemyEntity(敵オブジェクト)のプロトタイプを管理するクラス
// EnemyEntity を複製するために、EntityPrototype を継承し、Clone メソッドを実装します。
class EnemyPrototype : public EnemyEntity, public EntityPrototype
{
private:
    int m_modelHandle;  // 複製時に使用するモデルハンドルを保持

public:
    // コンストラクタ：モデルハンドルと初期位置を受け取り、プロトタイプを初期化
    // modelHandle は、敵のモデルを識別するためのハンドル
    // pos は、敵の初期位置を設定
    EnemyPrototype(int modelHandle, VECTOR pos);

    // Clone メソッド：EnemyEntity を複製する
    // プロトタイプを複製して新しいインスタンスを返す
    std::shared_ptr<Entity> Clone() const override;
};
