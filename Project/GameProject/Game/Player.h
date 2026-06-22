#pragma once
#include "../Base/Base.h"

class Player :public Base {
private:
	//モデルオブジェクト定義
	
	//プレイヤーのモデル
	CModelA3M m_model;

public:
	Player(const CVector3D& pos);
	void Update()override;
	void Render()override;
	void Collision(Base* b)override;
};