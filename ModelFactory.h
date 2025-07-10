#pragma once
#include <DxLib.h>
#include <string>            // std::string を使用するためのヘッダーファイル
#include <unordered_map>     // std::unordered_map を使用するためのヘッダーファイル
#include <tchar.h>           // _T マクロを使用するためのヘッダーファイル

// モデルの読み込みとキャッシュを管理するクラス
// モデル名（文字列）をキーとして、モデルのハンドル（ID）を返す
// シングルトンパターンを使用して、アプリケーション全体で一意のインスタンスを提供
class ModelFactory
{
private:
    // モデル名をキー、モデルハンドルを値として格納するハッシュマップ
    std::unordered_map<std::string, int> m_models;

    // コンストラクタとデストラクタはプライベートにすることで、外部からインスタンスを作成できないようにする
    // シングルトンインスタンスを取得するための静的メソッドを提供

    // コンストラクタ
    ModelFactory() = default;
	// デストラクタ
    ~ModelFactory();

    // コピーコンストラクタと代入演算子も削除して、インスタンスのコピーを防ぐ
    ModelFactory(const ModelFactory&) = delete;
    ModelFactory& operator=(const ModelFactory&) = delete;

public:
    // シングルトンパターンを使用して、インスタンスへのアクセスを提供
    // シングルトンパターンを使用している理由は、
	// モデルというリソースは通常、アプリケーション全体で一意であり、
	// 複数のインスタンスを作成する必要がないため
    static ModelFactory& Instance();

    // モデルを名前で取得する
    int GetModel(const std::string& name);

    // すべてのモデルを解放する
    void Clear();
};
