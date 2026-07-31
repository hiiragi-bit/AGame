#include "UI.h"
#include "Gamedata.h"

HPbar::HPbar()
	:Base(eUI)
{
	m_img = COPY_RESOURCE("HPbar", CImage);
}

void HPbar::Draw()
{
	int hp = Gamedata::h_hp;
	int h = hp;
	m_img.SetRect(180 * h, 0, 180 * h + 180, 24);
	m_img.SetSize(400, 40);
	m_img.SetPos(65, 75);
	m_img.Draw();
}

PotionRed::PotionRed()
	:Base(eUI)
{
	m_img = COPY_RESOURCE("PotionRed", CImage);
}

void PotionRed::Draw()
{
	m_img.SetSize(192, 192);
	m_img.SetPos(65, 85);
	m_img.Draw();
}

Number::Number()
	:Base(eUI)
{
	m_img = COPY_RESOURCE("Number", CImage);
}

void Number::Draw()
{
	int num = Gamedata::n_num;
	int n = num;
	m_img.SetRect(12 * n, 0, 12 * n + 12, 18);
	m_img.SetSize(60, 92);
	m_img.SetPos(230, 140);
	m_img.Draw();
}
