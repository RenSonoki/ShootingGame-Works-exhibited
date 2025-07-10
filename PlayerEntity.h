#pragma once
#include "Entity.h"
#include "TransformComponent.h"
#include "RenderModelComponent.h"
#include <memory>

// プレイヤーのオブジェクトを表すクラス
class PlayerEntity : public Entity
{
public:
	// プレイヤーの位置を表す列挙型
	std::shared_ptr<TransformComponent> m_playerTransform;

	int m_hp;                   // プレイヤーのHP
	int m_invincibleTimer;      // 無敵時間のタイマー

	// コンストラクタ
	PlayerEntity(int modelHandle);

	void HandleInput();			// 入力を処理する
	void Update() override;		// 更新処理を行う
};