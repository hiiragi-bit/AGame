#pragma once
#include "../Base/Base.h"
#include "IDamage.h"

class Player :public Base, public IDamage {
private:
	//アニメーション番号
	enum {
		eAnim_Idle,			//待機アニメーション
		eAnim_FrontRun,		//前に走るアニメーション
		eAnim_RightRun,		//右に走るアニメーション
		eAnim_LeftRun,		//左に走るアニメーション
		eAnim_BackRun,		//後ろに走るアニメーション
		eAnim_FrontDodge,	//前に回避するアニメーション
		eAnim_RightDodge,	//右に回避するアニメーション
		eAnim_LeftDodge,	//左に回避するアニメーション
		eAnim_BackDodge,	//後ろに回避するアニメーション
		eAnim_AttackCombo1,	//攻撃コンボ1アニメーション
		eAnim_AttackCombo2,	//攻撃コンボ2アニメーション
		eAnim_AttackCombo3,	//攻撃コンボ3アニメーション
		eAnim_JumpAttack,	//ジャンプ攻撃アニメーション
		eAnim_Damage,		//ダメージアニメーション
		eAnim_Death,		//死亡アニメーション
	};

	//状態
	enum {
		eState_Idle,
		eState_Run,
		eState_Attack,
		eState_JumpAttack,
		eState_BackDodge,
		eState_Damage,
		eState_Death,
	};

	//状態変数
	int m_state;

	//通常状態
	void StateIdle();

	//攻撃状態
	void StateAttack();

	//ジャンプ攻撃状態
	void StateJumpAttack();

	//後ろ回避状態
	void StateBackDodge();

	//ダメージ状態
	void StateDamage();

	//死亡状態
	void StateDeath();

	//モデルオブジェクト定義
	
	//プレイヤーのモデル
	CModelA3M m_model;
	//剣のモデル
	CModelObj m_sword_model;
	//剣のワールド行列
	CMatrix m_sword_matrix;

	float m_height;			//キャラクターの高さ
	bool m_attack_flag;		//攻撃フラグ
	bool m_attackJ_flag;	//ジャンプ攻撃フラグ
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