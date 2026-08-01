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

Game::Game()
	:Base(eGame)
{
	Base::Add(new Player(CVector3D(0, 0, 0)));
	//Base::Add(new Mutant(CVector3D(0, 0, -5)));
	//Base::Add(new Pumpkinhulk(CVector3D(-5, 0, 0)));
	Base::Add(new Warrok(CVector3D(5, 0, 0)));
	Base::Add(new TPSCamera);
	Base::Add(new Stage());
	Base::Add(new SkyBox());
	Base::Add(new HPbar());
	Base::Add(new PotionRed());
	Base::Add(new Number());
}

void Game::Update()
{
	//ゲームオーバー
	Base* b = Base::FindObject(ePlayer);
	if (!b) {
		//全てのオブジェクトを破壊
		Base::KillALL();
		//ゲームシーンへ
		Base::Add(new Gameover);
		Base::Add(new GameoverText);
	}

	//ゲームクリアー
	Base* c = Base::FindObject(eEnemyBoss);
	if (!c) {
		//全てのオブジェクトを破壊
		Base::KillALL();
		//ゲームシーンへ
		Base::Add(new Clear);
		Base::Add(new ClearText);
	}
}
