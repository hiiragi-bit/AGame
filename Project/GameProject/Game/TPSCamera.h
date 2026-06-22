#pragma once
#include "../Base/Base.h"

class TPSCamera :public Base {
private:
	float m_dist;

public:
	TPSCamera();
	void Update();
	void Render();
};