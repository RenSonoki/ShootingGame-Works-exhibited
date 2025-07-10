#pragma once

#include <string>
#include <unordered_map>

// 画像リソースを一元管理（Flyweight パターン）するクラス
class ImageResourceSet
{
public:
    ~ImageResourceSet();

    int Load(const std::wstring& path);         // 画像ロード
    void Unload(const std::wstring& path);      // 単体解放
    void Clear();                               // 全解放

private:
    std::unordered_map<std::wstring, int> m_imageHandles;
};