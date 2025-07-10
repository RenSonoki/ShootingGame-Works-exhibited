#pragma once
#include <memory>

class Entity;

// プロトタイプのインターフェース
class IPrototype
{
public:
    virtual ~IPrototype() = default;

    // エンティティのクローンを返す
    virtual std::shared_ptr<Entity> Clone() const = 0;
};
