#include "Game.h"
#include "Player.h"
#include "Mutant.h"
#include "Pumpkinhulk.h"
#include "Warrok.h"
#include "TPSCamera.h"
#include "Stage.h"
#include "UI.h"
#include "Title/Gameover.h"
#include "Clear/Clear.h"
#include "Text.h"
#include "Gamedata.h"
#include "Effekseer/EffekseerManager.h"

Game::Game()
	:Base(eGame)
{
	Base::Add(new Player(CVector3D(0, 0, 0)));
	Base::Add(new Mutant(CVector3D(-5, 0, -20)));
	Base::Add(new Mutant(CVector3D(5, 0, -20)));
	Base::Add(new Pumpkinhulk(CVector3D(0, 0, -20)));
	Base::Add(new TPSCamera());
	Base::Add(new Stage());
	Base::Add(new SkyBox());
	Base::Add(new HPbar());
	Base::Add(new PotionRed());
	Base::Add(new Number());
	Base::Add(new EffekseerManager());
	Base::Add(new GuideText());
}

void Game::Update()
{
	//Pumpkinhulkを倒すとボス出現
	if (Gamedata::b_boss == 1) {
		Gamedata::b_boss = 2;
		Base::Add(new Warrok(CVector3D(0, 0, -20)));
	}

	//プレイヤーが倒されるとゲームオーバー
	Base* b = Base::FindObject(ePlayer);
	if (!b) {
		//全てのオブジェクトを破壊
		Base::KillALL();
		//ゲームシーンへ
		Base::Add(new Gameover);
		Base::Add(new GameoverText);
		Base::Add(new GameoverText2);
		Base::Add(new GameoverText3);
	}

	//ボスを倒すとゲームクリアー
	if (Gamedata::c_clear == 1) {
		//全てのオブジェクトを破壊
		Base::KillALL();
		//ゲームシーンへ
		Base::Add(new Clear);
		Base::Add(new ClearText);
		Base::Add(new ClearText2);
	}
}
