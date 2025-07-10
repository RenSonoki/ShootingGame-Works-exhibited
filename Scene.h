#pragma once

// 前方宣言（循環参照対策
// Gameクラスをこのヘッダーファイル内で使うため、ここで前方宣言しておく
class Game;  

// ゲームシーンの抽象基底クラス
class Scene
{
public:
    virtual ~Scene() = default;

	// シーン開始時の初期化処理
	// virtual void Initialize(Game& game) = 0;

    // 毎フレームの更新処理
	// Game&を引数として受け取ることで、Gameクラスのメンバ関数を呼び出せるようにする
	// このアプローチにより、Sceneの派生クラス間でもゲームの状態（スコアやライフなど）のやり取りが可能になる
    virtual void Update(Game& game) = 0;

    // 描画処理
    virtual void Draw() = 0;
};