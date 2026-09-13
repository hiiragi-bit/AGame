#include "Text.h"

Titlelogo::Titlelogo() :Base(eText)
{
	m_img = COPY_RESOURCE("Titlelogo", CImage);
}

void Titlelogo::Draw()
{
	m_img.SetPos(500, 250);
	m_img.SetSize(920, 220);
	m_img.Draw();
}

TitleText::TitleText() :Base(eText)
{
	//m_img = COPY_RESOURCE("TitleText", CImage);
	m_img = COPY_RESOURCE("TitleTextnum", CImage);
}

void TitleText::Draw()
{
	m_img.SetPos(590, 700);
	m_img.SetSize(720, 200);
	m_img.Draw();
}



GameoverText::GameoverText() :Base(eText)
{
	m_img = COPY_RESOURCE("GameoverText", CImage);
}

void GameoverText::Draw()
{
	m_img.SetPos(500, 250);
	m_img.SetSize(920, 220);
	m_img.Draw();
}

GameoverText2::GameoverText2() :Base(eText)
{
	//m_img = COPY_RESOURCE("GameoverTextR", CImage);
	m_img = COPY_RESOURCE("GameoverText3", CImage);
}

void GameoverText2::Draw()
{
	m_img.SetPos(590, 600);
	m_img.SetSize(720, 170);
	m_img.Draw();
}

GameoverText3::GameoverText3() :Base(eText)
{
	//m_img = COPY_RESOURCE("GameoverTextZ", CImage);
	m_img = COPY_RESOURCE("GameoverText1", CImage);
}

void GameoverText3::Draw()
{
	m_img.SetPos(590, 700);
	m_img.SetSize(720, 200);
	m_img.Draw();
}

ClearText::ClearText() :Base(eText)
{
	m_img = COPY_RESOURCE("ClearText", CImage);
}

void ClearText::Draw()
{
	m_img.SetPos(500, 250);
	m_img.SetSize(920, 220);
	m_img.Draw();
}

ClearText2::ClearText2() :Base(eText)
{
	//m_img = COPY_RESOURCE("ClearText2", CImage);
	m_img = COPY_RESOURCE("ClearTextnum", CImage);
}

void ClearText2::Draw()
{
	m_img.SetPos(590, 700);
	m_img.SetSize(720, 170);
	m_img.Draw();
}

Leftstick::Leftstick() :Base(eText)
{
	m_img = COPY_RESOURCE("Leftstick", CImage);
}

void Leftstick::Draw()
{
	m_img.SetPos(1500, 850);
	m_img.SetSize(50, 50);
	m_img.Draw();
}

Button2::Button2() :Base(eText)
{
	m_img = COPY_RESOURCE("Button2", CImage);
}

void Button2::Draw()
{
	m_img.SetPos(1500, 850);
	m_img.SetSize(50, 50);
	m_img.Draw();
}

Button3::Button3() :Base(eText)
{
	m_img = COPY_RESOURCE("Button3", CImage);
}

void Button3::Draw()
{
	m_img.SetPos(1500, 900);
	m_img.SetSize(50, 50);
	m_img.Draw();
}

Button4Attack::Button4Attack() :Base(eText)
{
	m_img = COPY_RESOURCE("Button4", CImage);
}

void Button4Attack::Draw()
{
	m_img.SetPos(1500, 950);
	m_img.SetSize(50, 50);
	m_img.Draw();
}

Button4Jumpattack::Button4Jumpattack() :Base(eText)
{
	m_img = COPY_RESOURCE("Button4", CImage);
}

void Button4Jumpattack::Draw()
{
	m_img.SetPos(1500, 1000);
	m_img.SetSize(50, 50);
	m_img.Draw();
}

W::W() :Base(eText)
{
	m_img = COPY_RESOURCE("W", CImage);
}

void W::Draw()
{
	m_img.SetPos(1350, 850);
	m_img.SetSize(50, 50);
	m_img.Draw();
}

A::A() :Base(eText)
{
	m_img = COPY_RESOURCE("A", CImage);
}

void A::Draw()
{
	m_img.SetPos(1400, 850);
	m_img.SetSize(50, 50);
	m_img.Draw();
}

S::S() :Base(eText)
{
	m_img = COPY_RESOURCE("S", CImage);
}

void S::Draw()
{
	m_img.SetPos(1450, 850);
	m_img.SetSize(50, 50);
	m_img.Draw();
}

D::D() :Base(eText)
{
	m_img = COPY_RESOURCE("D", CImage);
}

void D::Draw()
{
	m_img.SetPos(1500, 850);
	m_img.SetSize(50, 50);
	m_img.Draw();
}

SPACE::SPACE() :Base(eText)
{
	m_img = COPY_RESOURCE("SPACE", CImage);
}

void SPACE::Draw()
{
	m_img.SetPos(1393, 900);
	m_img.SetSize(160, 50);
	m_img.Draw();
}

LeftmouseAttack::LeftmouseAttack():Base(eText)
{
	m_img = COPY_RESOURCE("Leftmouse", CImage);
}

void LeftmouseAttack::Draw()
{
	m_img.SetPos(1470, 920);
	m_img.SetSize(100, 100);
	m_img.Draw();
}

LeftmouseJumpattack::LeftmouseJumpattack() :Base(eText)
{
	m_img = COPY_RESOURCE("Leftmouse", CImage);
}

void LeftmouseJumpattack::Draw()
{
	m_img.SetPos(1470, 975);
	m_img.SetSize(100, 100);
	m_img.Draw();
}

GuideText::GuideText() :Base(eText)
{
}

void GuideText::Draw()
{
	//文字表示
	m_Guide_text.Draw(1550, 1044, 255, 255, 255, ":ジャンプ攻撃");
	m_Guide_text.Draw(1200, 1044, 255, 255, 255, "ジャンプ中に");
	m_Guide_text.Draw(1550, 994, 255, 255, 255, ":攻撃");
	m_Guide_text.Draw(1550, 944, 255, 255, 255, ":ジャンプ");
	m_Guide_text.Draw(1550, 894, 255, 255, 255, ":移動");
	m_Guide_text.SetFontSize(50);
}
