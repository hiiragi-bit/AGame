#pragma once
#include "../Base/Base.h"
#include "IDamage.h"

class Enemy :public Base, public IDamage {
private:
	//アニメーション番号
	enum {
		eAnim_Idle,
		eAnim_Run,
		eAnim_Step = 12,
		eAnim_Attack = 20,
		eAnim_Damage = 15,
		eAnim_Down,
	};

	//状態
	enum {
		eState_Idle,
		eState_Step,
		eState_Attack,
		eState_Damage,
		eState_Down,
	};

	//状態変数
	int m_state;

	//通常状態
	void StateIdle();

	//ステップ状態
	void StateStep();

	//攻撃状態
	void StateAttack();

	//ダメージ状態
	void StateDamage();

	//ダウン状態
	void StateDown();

	//敵のモデル
	CModelA3M m_model;

	int m_hp;				//敵のHP
	bool m_attck_flag;		//攻撃フラグ
	CCapsule m_attack_cap;	//攻撃のカプセル
	int m_state_step;		//各状態の工程
	int m_attack_time;		//攻撃のクールタイム
	int m_move_cnt;			//移動用時間計測カウンタ
	bool m_is_ground;		//接地フラグ
	float m_target_rot;

public:
	Enemy(const CVector3D& pos);
	void Update()override;
	void Render()override;
	void Collision(Base* b)override;
	void TakeDamage(const CVector3D& vec);
};