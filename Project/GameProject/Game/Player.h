#pragma once
#include "../Base/Base.h"

class Player :public Base {
private:
	//モデルオブジェクト定義
	
	//プレイヤーのモデル
	CModelA3M m_model;
	//剣のモデル
	CModelObj m_sword_model;
	//剣のワールド行列
	CMatrix m_sword_matrix;

public:
	Player(const CVector3D& pos);
	void Update()override;
	void Render()override;
	void Collision(Base* b)override;
};