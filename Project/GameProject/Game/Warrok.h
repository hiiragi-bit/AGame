#pragma once
#include "../Base/Base.h"
#include "IDamage.h"

class Warrok :public Base, public IDamage {
private:
	//アニメーション番号
	enum {
		eAnim_Idle,
		eAnim_Run,
		eAnim_Step,
		eAnim_SlamAttack,
		eAnim_ComboAttack1,
		eAnim_ComboAttack2,
		eAnim_JumpAttack,
		eAnim_Damage,
		eAnim_Death,
	};

	//状態
	enum {
		eState_Idle,
		eState_Step,
		eState_Attack,
		eState_Damage,
		eState_Death,
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
	void StateDeath();

	//敵のモデル
	CModelA3M m_model;

	bool m_attackR_flag;	//右攻撃フラグ
	bool m_attackL_flag;	//左攻撃フラグ
	CCapsule m_attackR_cap;	//右攻撃のカプセル
	CCapsule m_attackL_cap;	//左攻撃のカプセル
	int m_state_step;		//各状態の工程
	int m_attack_time;		//攻撃のクールタイム
	int m_move_cnt;			//移動用時間計測カウンタ
	bool m_is_ground;		//接地フラグ
	float m_target_rot;
	int m_attack_change;	//攻撃切り替え

public:
	Warrok(const CVector3D& pos);
	void Update()override;
	void Render()override;
	void Collision(Base* b)override;
	void TakeDamage(const CVector3D& vec);
};