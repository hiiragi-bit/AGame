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
	m_img = COPY_RESOURCE("TitleText", CImage);
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
	m_img = COPY_RESOURCE("GameoverText2", CImage);
}

void GameoverText2::Draw()
{
	m_img.SetPos(590, 600);
	m_img.SetSize(720, 170);
	m_img.Draw();
}

GameoverText3::GameoverText3() :Base(eText)
{
	m_img = COPY_RESOURCE("GameoverText3", CImage);
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
	m_img = COPY_RESOURCE("ClearText2", CImage);
}

void ClearText2::Draw()
{
	m_img.SetPos(590, 700);
	m_img.SetSize(720, 170);
	m_img.Draw();
}

GuideText::GuideText() :Base(eText)
{
}

void GuideText::Draw()
{
	//文字表示
	/*m_Guide_text.Draw(84, 1044, 255, 255, 255, ":移動");
	m_Guide_text.Draw(84, 1008, 255, 255, 255, ":　　がジャンプ");
	m_Guide_text.Draw(84, 972, 255, 255, 255, ":　がジャンプ");
	m_Guide_text.Draw(84, 936, 255, 255, 255, ":　がジャンプ");
	m_Guide_text.Draw(84, 900, 255, 255, 255, ":　が赤魔法");
	m_Guide_text.Draw(84, 864, 255, 255, 255, ":　が青魔法");
	m_Guide_text.Draw(84, 828, 255, 255, 255, ":　を操作する");
	m_Guide_text.Draw(84, 792, 255, 255, 255, ":　を操作する");
	m_Guide_text.SetFontSize(36);*/
}
