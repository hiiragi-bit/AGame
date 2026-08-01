#include "Text.h"

TitleText::TitleText() :Base(eText)
{
}

void TitleText::Draw()
{
	//文字表示
	m_Title_text.Draw(800, 812, 255, 255, 255, "Zキーでスタート");
	m_Title_text.SetFontSize(46);
}



GameoverText::GameoverText() :Base(eText)
{
}

void GameoverText::Draw()
{
	//文字表示
	m_Gameover_text.Draw(800, 904, 255, 255, 255, "Rキーでリトライ");
	m_Gameover_text.Draw(800, 982, 255, 255, 255, "Zキーでタイトルへ");
	m_Gameover_text.SetFontSize(46);
}

ClearText::ClearText() :Base(eText)
{
}

void ClearText::Draw()
{
	//文字表示
	m_Clear_text.Draw(800, 982, 255, 255, 255, "Zキーでタイトルへ");
	m_Clear_text.SetFontSize(46);
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
