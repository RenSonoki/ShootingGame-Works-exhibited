#include "ImageResourceSet.h"
#include "DxLib.h"

ImageResourceSet::~ImageResourceSet()
{
    Clear();
}

// 画像のロード（重複読み込みを防ぐ）
int ImageResourceSet::Load(const std::wstring& path)
{
    auto it = m_imageHandles.find(path);
    if (it != m_imageHandles.end())
    {
        return it->second;
    }

    int handle = LoadGraph(path.c_str());
    if (handle != -1)
    {
        m_imageHandles[path] = handle;
    }

    return handle;
}

// 指定画像のアンロード
void ImageResourceSet::Unload(const std::wstring& path)
{
    auto it = m_imageHandles.find(path);
    if (it != m_imageHandles.end())
    {
        DeleteGraph(it->second);
        m_imageHandles.erase(it);
    }
}

// 全画像の解放
void ImageResourceSet::Clear()
{
    for (const auto& pair : m_imageHandles)
    {
        DeleteGraph(pair.second);
    }
    m_imageHandles.clear();
}