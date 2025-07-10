#include "SoundResourceSet.h"
#include "DxLib.h"

SoundResourceSet::~SoundResourceSet()
{
    Clear();
}

// サウンドの読み込み
int SoundResourceSet::Load(const std::wstring& path)
{
    auto it = m_soundHandles.find(path);
    if (it != m_soundHandles.end())
    {
        return it->second;
    }

    int handle = LoadSoundMem(path.c_str());
    if (handle != -1)
    {
        m_soundHandles[path] = handle;
    }

    return handle;
}

// 指定サウンドのアンロード
void SoundResourceSet::Unload(const std::wstring& path)
{
    auto it = m_soundHandles.find(path);
    if (it != m_soundHandles.end())
    {
        DeleteSoundMem(it->second);
        m_soundHandles.erase(it);
    }
}

// 全てのサウンドを解放
void SoundResourceSet::Clear()
{
    for (const auto& pair : m_soundHandles)
    {
        DeleteSoundMem(pair.second);
    }
    m_soundHandles.clear();
}