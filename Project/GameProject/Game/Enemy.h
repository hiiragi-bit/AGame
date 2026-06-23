#pragma once
#include "../Base/Base.h"

class Enemy :public Base {
private:
	CModelA3M m_model;

public:
	Enemy(const CVector3D& pos);
	void Update()override;
	void Render()override;
	void Collision(Base* b)override;
	void TakeDamage(const CVector3D& vec);
};