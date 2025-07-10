#pragma once

#include <string>
#include <unordered_map>

// サウンドリソースを一括管理するクラス（Flyweight パターン）
class SoundResourceSet
{
public:
    ~SoundResourceSet();

    int Load(const std::wstring& path);         // サウンドの読み込み
    void Unload(const std::wstring& path);      // 単体アンロード
    void Clear();                               // すべてのサウンドを解放

private:
    std::unordered_map<std::wstring, int> m_soundHandles;
};