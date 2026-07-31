#pragma once
#include "../Base/Base.h"

class Title :public Base {
private:
	CImage m_img;
	//文字表示オブジェクト
	CFont m_title_text;
	//待ち時間
	int m_cnt;
public:
	Title();
	void Update()override;
	void Draw()override;
};