#pragma once
#include "../Base/Base.h"

class HPbar :public Base {
private:
	CImage m_img;

public:
	HPbar();
	void Draw();
};

class PotionRed :public Base {
private:
	CImage m_img;

public:
	PotionRed();
	void Draw();
};

class Number :public Base {
private:
	CImage m_img;

public:
	Number();
	void Draw();
};