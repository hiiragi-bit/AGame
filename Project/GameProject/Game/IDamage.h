#pragma once
//ダメージインターフェイス
class IDamage {
public:
	virtual void TakeDamage(const CVector3D& vec) = 0;
};