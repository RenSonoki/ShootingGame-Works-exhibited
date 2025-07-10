#pragma once
#include "Entity.h"
#include <memory>     // std::shared_ptr を使用するためのヘッダーファイル

// エンティティのプロトタイプを管理する基底クラス
// このクラスはエンティティ(オブジェクト)のクローン（コピー）を作成するためのインターフェースを提供
// プロトタイプパターンを使用して、エンティティを複製できるようにします。
class EntityPrototype
{
public:
    // 仮想デストラクタ：派生クラスで適切に破棄できるように仮想デストラクタを提供
    virtual ~EntityPrototype() {}

    // Clone メソッド：エンティティを複製するためのインターフェース
    // 派生クラスでクローンを作成する処理を実装する
    virtual std::shared_ptr<Entity> Clone() const = 0;
};
