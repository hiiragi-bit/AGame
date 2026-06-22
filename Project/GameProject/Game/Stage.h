#pragma once
#include "../Base/Base.h"

class Stage :public Base {
private:
	//モデルオブジェクト定義

	//ステージのモデル
	CModelObj* mp_model;

public:
	Stage();
	void Update()override;
	void Render()override;
	CModel* GetModel()override;
};

class SkyBox :public Base {
private:
	//モデルオブジェクト定義

	//スカイボックスのモデル
	CModelObj m_model;

public:
	SkyBox();
	void Render()override;
};