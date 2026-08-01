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
	//文字表示オブジェクト
	CFont m_Gameover_text;
public:
	GameoverText();
	void Draw();
};

class ClearText :public Base {
	//文字表示オブジェクト
	CFont m_Clear_text;
public:
	ClearText();
	void Draw();
};

class GuideText :public Base {
	//文字表示オブジェクト
	CFont m_Guide_text;
public:
	GuideText();
	void Draw();
};