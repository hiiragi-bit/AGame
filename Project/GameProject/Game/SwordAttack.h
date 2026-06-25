#pragma once
#include "../Base/Base.h"

class SwordAttack :public Base {
private:
	//Œ•‚Ìƒ[ƒ‹ƒhs—ñ
	CMatrix m_sword_matrix;

	CVector3D m_sword_s, m_sword_e;

public:
	SwordAttack();
	void Update()override;
	void Collision(Base* b)override;
};