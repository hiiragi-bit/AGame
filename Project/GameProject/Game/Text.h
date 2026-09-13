#pragma once
#include "Base/Base.h"

class Titlelogo :public Base {
	CImage m_img;
public:
	Titlelogo();
	void Draw();
};

class TitleText :public Base {
	CImage m_img;
public:
	TitleText();
	void Draw();
};

class GameoverText :public Base {
	CImage m_img;
public:
	GameoverText();
	void Draw();
};

class GameoverText2 :public Base {
	CImage m_img;
public:
	GameoverText2();
	void Draw();
};

class GameoverText3 :public Base {
	CImage m_img;
public:
	GameoverText3();
	void Draw();
};

class ClearText :public Base {
	CImage m_img;
public:
	ClearText();
	void Draw();
};

class ClearText2 :public Base {
	CImage m_img;
public:
	ClearText2();
	void Draw();
};

class Leftstick :public Base {
	CImage m_img;
public:
	Leftstick();
	void Draw();
};

class Button2 :public Base {
	CImage m_img;
public:
	Button2();
	void Draw();
};

class Button3 :public Base {
	CImage m_img;
public:
	Button3();
	void Draw();
};

class Button4Attack :public Base {
	CImage m_img;
public:
	Button4Attack();
	void Draw();
};

class Button4Jumpattack :public Base {
	CImage m_img;
public:
	Button4Jumpattack();
	void Draw();
};

class W :public Base {
	CImage m_img;
public:
	W();
	void Draw();
};

class A :public Base {
	CImage m_img;
public:
	A();
	void Draw();
};

class S :public Base {
	CImage m_img;
public:
	S();
	void Draw();
};

class D :public Base {
	CImage m_img;
public:
	D();
	void Draw();
};

class SPACE :public Base {
	CImage m_img;
public:
	SPACE();
	void Draw();
};

class LeftmouseAttack :public Base {
	CImage m_img;
public:
	LeftmouseAttack();
	void Draw();
};

class LeftmouseJumpattack :public Base {
	CImage m_img;
public:
	LeftmouseJumpattack();
	void Draw();
};

class GuideText :public Base {
	//文字表示オブジェクト
	CFont m_Guide_text;
public:
	GuideText();
	void Draw();
};