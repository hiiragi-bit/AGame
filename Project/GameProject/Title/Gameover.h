#pragma once
#include "../Base/Base.h"

class Gameover :public Base {
private:
	CImage m_img;
	//文字表示オブジェクト
	CFont m_clear_text;
	//待ち時間
	int m_cnt;
public:
	Gameover();
	void Update()override;
	void Draw()override;
};