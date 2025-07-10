#include "ModelResourceSet.h"
#include "DxLib.h"

ModelResourceSet::~ModelResourceSet()
{
    Clear();
}

// モデルの読み込み
int ModelResourceSet::Load(const std::wstring& path)
{
    auto it = m_modelHandles.find(path);
    if (it != m_modelHandles.end())
    {
        return it->second;
    }

    int handle = MV1LoadModel(path.c_str());
    if (handle != -1)
    {
        m_modelHandles[path] = handle;
    }

    return handle;
}

// 単体モデルのアンロード
void ModelResourceSet::Unload(const std::wstring& path)
{
    auto it = m_modelHandles.find(path);
    if (it != m_modelHandles.end())
    {
        MV1DeleteModel(it->second);
        m_modelHandles.erase(it);
    }
}

// 全てのモデルを解放
void ModelResourceSet::Clear()
{
    for (const auto& pair : m_modelHandles)
    {
        MV1DeleteModel(pair.second);
    }
    m_modelHandles.clear();
}
