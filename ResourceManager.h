#pragma once

#include "ImageResourceSet.h"
#include "SoundResourceSet.h"
#include "ModelResourceSet.h"

// リソースを読み込んで管理するクラス
// シングルトンパターンを使用して、アプリケーション全体で一つのインスタンスを共有する
class ResourceManager
{
public:
    // シングルトンアクセス用メソッド
    static ResourceManager& GetInstance();

    // 各種リソース取得
    int GetImage(const std::wstring& path);
    int GetSound(const std::wstring& path);
    int GetModel(const std::wstring& path);

    // 全リソース解放
    void ClearAll();

private:
    ResourceManager() = default;                      // コンストラクタ非公開
    ResourceManager(const ResourceManager&) = delete; // コピー禁止
    ResourceManager& operator=(const ResourceManager&) = delete;

    ImageResourceSet m_imageSet;
    SoundResourceSet m_soundSet;
    ModelResourceSet m_modelSet;
};