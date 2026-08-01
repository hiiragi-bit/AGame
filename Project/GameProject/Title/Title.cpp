#include "Title.h"
#include "Game/Game.h"

Title::Title()
	:Base(eTitle)
{
	//m_img = COPY_RESOURCE("Title", CImage);
	m_cnt = 0;
}

void Title::Update()
{
	//Zキーでタイトル破棄
	if (m_cnt++ > 2 && PUSH(CInput::eButton1)) {
		//全てのオブジェクトを破壊
		Base::KillALL();
		//ゲームシーンへ
		Base::Add(new Game());
	}
}

void Title::Draw()
{
	//m_img.SetSize(1920, 1080);
	//m_img.Draw();
}
