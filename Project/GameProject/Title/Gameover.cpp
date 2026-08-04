#include "Gameover.h"
#include "Game/Game.h"
#include "Game/Gamedata.h"
#include "Title/Title.h"
#include "Game/Text.h"

Gameover::Gameover()
	:Base(eGameover)
{
	m_img = COPY_RESOURCE("Gameover", CImage);
	m_cnt = 0;
}

void Gameover::Update()
{
	//Rキーでゲームオーバー画面破棄
	if (m_cnt++ > 2 && PUSH(CInput::eButton7)) {
		//全てのオブジェクトを破壊
		Base::KillALL();
		//ゲームシーンへ
		Base::Add(new Game());
		Gamedata::h_hp = 0;
		Gamedata::n_num = 5;
		Gamedata::b_boss = 0;
		Gamedata::c_clear = 0;
	}
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

void Gameover::Draw()
{
	m_img.SetSize(1920, 1080);
	m_img.Draw();
}
