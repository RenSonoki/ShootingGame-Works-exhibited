#pragma once
#include <string>

// すべてのリソースセットが実装すべき共通インターフェース
class IResourceSet
{
public:
    virtual ~IResourceSet() = default;

    // 指定したパスのリソースをロードし、そのハンドルを返す
    virtual int Load(const std::string& path) = 0;

    // 特定のリソースをアンロードする
    virtual void Unload(const std::string& path) = 0;

    // 登録されたすべてのリソースを解放
    virtual void Clear() = 0;
};