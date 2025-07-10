#pragma once

#include <string>
#include <unordered_map>

// モデルリソースを管理するクラス（Flyweight パターン）
class ModelResourceSet
{
public:
    ~ModelResourceSet();

    int Load(const std::wstring& path);          // モデルの読み込み
    void Unload(const std::wstring& path);       // 単体アンロード
    void Clear();                                // 全てのモデルを解放

private:
    std::unordered_map<std::wstring, int> m_modelHandles;
};