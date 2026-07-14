#pragma once
#include "../Base/Base.h"
#include "IDamage.h"

class Player :public Base, public IDamage {
private:
	//アニメーション番号
	enum {
		eAnim_Idle,
		eAnim_Run,
		eAnim_AttackCombo1,
		eAnim_AttackCombo2,
	};

	//状態
	enum {
		eState_Idle,
		eState_Run,
		eState_Attack,
	};

	//状態変数
	int m_state;

	//通常状態
	void StateIdle();

	//攻撃状態
	void StateAttack();

	//モデルオブジェクト定義
	
	//プレイヤーのモデル
	CModelA3M m_model;
	//剣のモデル
	CModelObj m_sword_model;
	//剣のワールド行列
	CMatrix m_sword_matrix;

	float m_height;			//キャラクターの高さ
	bool m_attack_flag;		//攻撃フラグ
	CCapsule m_attack_cap;	//剣のカプセル
	bool m_is_ground;		//接地フラグ
	int m_state_step;		//各状態での工程
	int m_upper_body;		//腰のボーン
	void Move();

public:
	Player(const CVector3D& pos);
	void Update()override;
	void Render()override;
	void Collision(Base* b)override;
	void TakeDamage(const CVector3D& vec);
};