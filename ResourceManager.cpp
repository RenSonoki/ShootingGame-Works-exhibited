#include "ResourceManager.h"

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

int ResourceManager::GetImage(const std::wstring& path)
{
    return m_imageSet.Load(path);
}

int ResourceManager::GetSound(const std::wstring& path)
{
    return m_soundSet.Load(path);
}

int ResourceManager::GetModel(const std::wstring& path)
{
    return m_modelSet.Load(path);
}

void ResourceManager::ClearAll()
{
    m_imageSet.Clear();
    m_soundSet.Clear();
    m_modelSet.Clear();
}