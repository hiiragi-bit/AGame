#pragma once
//ダメージインターフェイス
class IDamage {
public:
	int m_hp;
	virtual void TakeDamage(const CVector3D& vec) = 0;
};