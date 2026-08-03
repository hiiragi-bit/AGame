#pragma once
#include "Base/Base.h"

class TitleText :public Base {
	//文字表示オブジェクト
	CFont m_Title_text;
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

class GuideText :public Base {
	//文字表示オブジェクト
	CFont m_Guide_text;
public:
	GuideText();
	void Draw();
};