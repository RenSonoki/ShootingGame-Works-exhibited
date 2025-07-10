#pragma once
#include "Entity.h"
#include <vector>            // std::vector を使用するためのヘッダーファイル
#include <memory>            // std::shared_ptr を使用するためのヘッダーファイル

// エンティティ(ゲーム内のオブジェクト)の管理と更新・描画処理を行うクラス
class EntitySystem
{
private:
	// エンティティリスト：ゲーム内で管理される全てのエンティティを格納する可変長配列
    std::vector<std::shared_ptr<Entity>> m_entities;

public:
    // 新しいエンティティをシステムに追加
    // 受け取ったエンティティを entities リストに追加する
    void AddEntity(std::shared_ptr<Entity> entity);

    // 全てのエンティティの更新処理を行う
    // エンティティが持つ Update メソッドを呼び出して、状態を更新
    void Update();

    // 全てのエンティティの描画処理を行う
    // エンティティが持つ Draw メソッドを呼び出して、画面に描画
    void Draw();
};