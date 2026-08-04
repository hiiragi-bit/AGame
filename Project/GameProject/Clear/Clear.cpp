#include "Clear.h"
#include "Game/Game.h"
#include "Game/Gamedata.h"
#include "Title/Title.h"
#include "Game/Text.h"

Clear::Clear()
	:Base(eClear)
{
	m_img = COPY_RESOURCE("Clear", CImage);
	m_cnt = 0;
}

void Clear::Update()
{
	//Zキーでクリア画面破棄
	if (m_cnt++ > 2 && PUSH(CInput::eButton1)) {
		//全てのオブジェクトを破壊
		Base::KillALL();
		//タイトルシーンへ
		Base::Add(new Title);
		Base::Add(new TitleText);
		Gamedata::h_hp = 0;
		Gamedata::n_num = 5;
		Gamedata::b_boss = 0;
		Gamedata::c_clear = 0;
	}
}

void Clear::Draw()
{
	m_img.SetSize(1920, 1080);
	m_img.Draw();
}
