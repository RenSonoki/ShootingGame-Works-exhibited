#include "ModelFactory.h"
#include <tchar.h>

// シングルトンパターンを使用して、ModelFactory クラスのインスタンスにアクセスする
ModelFactory& ModelFactory::Instance()
{
    // static 変数 instance を使用して、唯一のインスタンスを生成（最初の呼び出し時のみ）
    static ModelFactory instance;
    return instance;
}

// 指定された名前のモデルを取得する
int ModelFactory::GetModel(const std::string& name)
{
    // モデル名がすでにキャッシュされているか確認
    auto it = m_models.find(name);
    if (it != m_models.end())
    {
        // キャッシュされている場合は、そのハンドル（ID）を返す
        return it->second;
    }

    // キャッシュされていない場合、モデルをロードしてキャッシュに追加
    // std::string を std::wstring に変換して TCHAR* に対応させる
    std::wstring wname(name.begin(), name.end());
    // モデルを読み込み、ハンドル（ID）を取得
    int handle = MV1LoadModel(wname.c_str());
    // モデル名とそのハンドルをキャッシュに保存
    m_models[name] = handle;
    return handle;
}

// すべてのキャッシュされたモデルを解放
void ModelFactory::Clear()
{
    // models の各エントリ（モデル名とモデルハンドル）に対して
    for (const auto& pair : m_models)
    {
        // 各モデルの解放
        MV1DeleteModel(pair.second);
    }
    // キャッシュをクリア
    m_models.clear();
}

// デストラクタ
ModelFactory::~ModelFactory()
{
    Clear();
}