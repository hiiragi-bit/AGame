#include "Warrok.h"
#include "Gamedata.h"

Warrok::Warrok(const CVector3D& pos)
	:Base(eEnemyBoss)
{
	//モデルの複製
	m_model = COPY_RESOURCE("Warrok", CModelA3M);
	//位置設定
	m_pos = pos;
	//回転値
	m_rot = CVector3D(0, 0, 0);
	//スケール
	m_scale = CVector3D(0.015f, 0.015f, 0.015f);
	//当たり判定の半径
	m_rad = 1.0f;
	//敵のHP
	m_hp = 4;
	//状態変数
	m_state = eState_Idle;
	//右攻撃フラグ
	m_attackR_flag = false;
	//左攻撃フラグ
	m_attackL_flag = false;
	//各状態の工程
	m_state_step = 0;
	//攻撃のクールタイム
	m_attack_time = 0;
	//移動用時間計測カウンタ
	m_move_cnt = 0;
	//接地フラグ
	m_is_ground = true;
	m_target_rot = m_rot.y;
	//攻撃切り替え
	m_attack_change = 0;
}

void Warrok::StateIdle()
{
	//キャラクターの移動量
	const float move_speed = 0.07f;
	m_attack_time++;
	m_move_cnt++;
	//ターゲットへのベクトル
	CVector3D vec;
	if (Base* p = Base::FindObject(ePlayer)) {
		//ターゲットへのベクトル
		vec = p->m_pos - m_pos;
		//ベクトルから回転値を逆算
		m_rot.y = atan2(vec.x, vec.z);
	}
	//回転値から方向ベクトルを計算
	m_dir = (CVector3D(sin(m_rot.y), 0, cos(m_rot.y)));
	if (vec.Length() > 1.5f) {
		//前進
		m_pos += m_dir * move_speed;
		//走るアニメーション
		m_model.ChangeAnimation(eAnim_Run);
	}
	else {
		if (m_attack_time >= 60) {
			m_state = eState_Attack;
		}
		else {
			//待機アニメーション
			m_model.ChangeAnimation(eAnim_Idle);
		}
	}
	//時間経過でステップ
	if (m_move_cnt >= 300) {
		m_state = eState_Step;
	}
}

void Warrok::StateStep()
{
	switch (m_state_step) {
	case 0:
	{
		//自身の右、後ろ、左の３方向からランダムでステップ方向を決定
		int r = rand() % 3;
		CVector3D dir[3] = { CVector3D(-1,0,0),CVector3D(0,0,-1),CVector3D(1,0,0) };
		const float jump_pow = 0.12f;
		const float step_pow = 0.06f;
		m_vec = CVector3D(CMatrix::MRotationY(m_rot.y) * CVector4D(dir[r], 0)) * step_pow;
		m_vec.y = jump_pow;
		m_is_ground = false;
	}
	m_state_step++;
	m_model.ChangeAnimation(eAnim_Step, false);
	break;
	case 1:
		//アニメーション終了で待機へ
		if (m_model.isAnimationEnd()) {
			m_move_cnt = rand() % 60;
			m_state_step = 0;
			m_is_ground = true;
			m_state = eState_Idle;
		}
		break;
	}
}

void Warrok::StateAttack()
{
	switch (m_attack_change) {
	case 0:
		m_model.ChangeAnimation(eAnim_SlamAttack, false);
		switch (m_state_step) {
		case 0:
			//一定フレーム以降に攻撃フラグON
			if (m_model.GetAnimationFrame() > 20) {
				m_attackR_flag = true;
				m_attackL_flag = true;
				m_state_step++;
			}
			break;
		case 1:
			//右腕の位置で攻撃用判定用カプセルを作成
			m_attackR_cap = CCapsule(m_model.GetFrameMatrix(37).GetPosition(),
				m_model.GetFrameMatrix(39).GetPosition(),
				0.5f);
			//左腕の位置で攻撃用判定用カプセルを作成
			m_attackL_cap = CCapsule(m_model.GetFrameMatrix(13).GetPosition(),
				m_model.GetFrameMatrix(15).GetPosition(),
				0.5f);
			//一定フレーム以降に攻撃フラグOFF
			if (m_model.GetAnimationFrame() > 24) {
				m_attackR_flag = false;
				m_attackL_flag = false;
				m_state_step++;
			}
			break;
		}
		break;
	case 1:
		m_model.ChangeAnimation(eAnim_ComboAttack1, false);
		switch (m_state_step) {
		case 0:
			//一定フレーム以降に攻撃フラグON
			if (m_model.GetAnimationFrame() > 19) {
				m_attackR_flag = true;
				m_attackL_flag = true;
				m_state_step++;
			}
			break;
		case 1:
			//右腕の位置で攻撃用判定用カプセルを作成
			m_attackR_cap = CCapsule(m_model.GetFrameMatrix(37).GetPosition(),
				m_model.GetFrameMatrix(39).GetPosition(),
				0.5f);
			//左腕の位置で攻撃用判定用カプセルを作成
			m_attackL_cap = CCapsule(m_model.GetFrameMatrix(13).GetPosition(),
				m_model.GetFrameMatrix(15).GetPosition(),
				0.5f);
			//一定フレーム以降に攻撃フラグOFF
			if (m_model.GetAnimationFrame() > 38) {
				m_attackR_flag = false;
				m_attackL_flag = false;
				m_state_step++;
			}
			break;
		}
		break;
	case 2:
		m_model.ChangeAnimation(eAnim_ComboAttack2, false);
		switch (m_state_step) {
		case 0:
			//一定フレーム以降に攻撃フラグON
			if (m_model.GetAnimationFrame() > 19) {
				m_attackR_flag = true;
				m_attackL_flag = true;
				m_state_step++;
			}
			break;
		case 1:
			//右腕の位置で攻撃用判定用カプセルを作成
			m_attackR_cap = CCapsule(m_model.GetFrameMatrix(37).GetPosition(),
				m_model.GetFrameMatrix(39).GetPosition(),
				0.5f);
			//左腕の位置で攻撃用判定用カプセルを作成
			m_attackL_cap = CCapsule(m_model.GetFrameMatrix(13).GetPosition(),
				m_model.GetFrameMatrix(15).GetPosition(),
				0.5f);
			//一定フレーム以降に攻撃フラグOFF
			if (m_model.GetAnimationFrame() > 60) {
				m_attackR_flag = false;
				m_attackL_flag = false;
				m_state_step++;
			}
			break;
		}
		break;
	case 3:
		m_model.ChangeAnimation(eAnim_JumpAttack, false);
		switch (m_state_step) {
		case 0:
			//一定フレーム以降に攻撃フラグON
			if (m_model.GetAnimationFrame() > 23) {
				m_attackR_flag = true;
				m_attackL_flag = true;
				m_state_step++;
			}
			break;
		case 1:
			//右腕の位置で攻撃用判定用カプセルを作成
			m_attackR_cap = CCapsule(m_model.GetFrameMatrix(37).GetPosition(),
				m_model.GetFrameMatrix(39).GetPosition(),
				0.5f);
			//左腕の位置で攻撃用判定用カプセルを作成
			m_attackL_cap = CCapsule(m_model.GetFrameMatrix(13).GetPosition(),
				m_model.GetFrameMatrix(15).GetPosition(),
				0.5f);
			//一定フレーム以降に攻撃フラグOFF
			if (m_model.GetAnimationFrame() > 30) {
				m_attackR_flag = false;
				m_attackL_flag = false;
				m_state_step++;
			}
			break;
		}
		break;
	}
	//アニメーション終了で待機へ
	if (m_model.isAnimationEnd()) {
		m_state_step = 0;
		m_attack_time = 0;
		if (m_attack_change == 3) {
			m_attack_change = 0;
		}
		else {
			m_attack_change++;
		}
		m_state = eState_Idle;
	}
}

void Warrok::StateDamage()
{
	m_model.ChangeAnimation(eAnim_Damage, false);
	if (m_model.isAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Warrok::StateDeath()
{
	m_model.ChangeAnimation(eAnim_Death, false);
	if (m_model.isAnimationEnd()) {
		SetKill();
	}
}

void Warrok::Update()
{
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Step:
		StateStep();
		break;
	case eState_Attack:
		StateAttack();
		break;
	case eState_Damage:
		StateDamage();
		break;
	case eState_Death:
		StateDeath();
		break;
	}

	//減速
	if (m_is_ground) {
		m_vec.x = m_vec.x * 0.9f;
		m_vec.z = m_vec.z * 0.9f;
	}

	//重力落下
	m_vec.y -= GRAVITY;
	//移動
	m_pos += m_vec;

	//カプセルを設定
	m_capusle = CCapsule(m_pos + CVector3D(0, 2.0 - m_rad, 0),	//始点（頭）
		m_pos + CVector3D(0, m_rad, 0),							//終点（足元）
		m_rad);

	//アニメーション更新
	m_model.UpdateAnimation();
}

void Warrok::Render()
{
	m_model.SetPos(m_pos);
	m_model.SetRot(m_rot);
	m_model.SetScale(m_scale);
	m_model.Render();

	if (m_attackR_flag)
		Utility::DrawCapsule(m_attackR_cap, CVector4D(1, 1, 0, 0));
	if (m_attackL_flag)
		Utility::DrawCapsule(m_attackL_cap, CVector4D(1, 1, 0, 0));
}

void Warrok::Collision(Base* b)
{
	switch (b->GetType()) {
		//プレイヤーとの判定
	case ePlayer:
	{
		CVector3D c1, d1;
		float dist;
		//カプセル同士の判定
		if (CCollision::CollisionCapsule(m_capusle, b->m_capusle, &dist, &c1, &d1)) {
			//押し戻す
			float s = (m_capusle.GetRadius() + b->m_capusle.GetRadius()) - dist;
			b->m_pos += d1 * s * 0.5f;
			m_pos -= d1 * s * 0.5f;
		}
		//攻撃の判定
		if (m_attackR_flag &&
			CCollision::CollisionCapsule(m_attackR_cap, b->m_capusle, &dist, &c1, &d1)) {
			if (IDamage* d = dynamic_cast<IDamage*>(b)) {
				d->m_hp -= 1;
				Gamedata::h_hp += 1;
				d->TakeDamage(CVector3D(0, 0, 0));
				//多重ヒット防止
				m_attackR_flag = false;
			}
		}
		//攻撃の判定
		if (m_attackL_flag &&
			CCollision::CollisionCapsule(m_attackL_cap, b->m_capusle, &dist, &c1, &d1)) {
			if (IDamage* d = dynamic_cast<IDamage*>(b)) {
				d->m_hp -= 1;
				Gamedata::h_hp += 1;
				d->TakeDamage(CVector3D(0, 0, 0));
				//多重ヒット防止
				m_attackL_flag = false;
			}
		}
	}
	break;
	//敵との判定
	case eEnemy:
	{
		CVector3D c1, d1;
		float dist;
		//カプセル同士の判定
		if (CCollision::CollisionCapsule(m_capusle, b->m_capusle, &dist, &c1, &d1)) {
			//押し戻す
			float s = (m_capusle.GetRadius() + b->m_capusle.GetRadius()) - dist;
			b->m_pos += d1 * s * 0.5f;
			m_pos -= d1 * s * 0.5f;
		}
	}
	break;
	//ステージとの判定
	case eField:
	{
		//押し戻し量
		CVector3D v(0, 0, 0);
		//カプセルとモデルの衝突
		auto tri = b->GetModel()->CollisionCapsule(m_capusle);
		//接触した面の数繰り返す
		for (auto& t : tri) {
			if (t.m_normal.y < -0.5f) {
				//面が下向き→天井に当たった
				//上昇速度を0に戻す
				if (m_vec.y > 0)
					m_vec.y = 0;
			}
			else if (t.m_normal.y > 0.8f) {
				//面が上向き→地面に当たった
				//重力落下速度を0に戻す
				if (m_vec.y < 0)
					m_vec.y = 0;
			}
			//接触した面の方向へ、めり込んだ分押し戻す
			CVector3D nv = t.m_normal * (m_rad - t.m_dist);
			//最も大きな移動量を求める
			v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
			if (t.m_normal.y < 0.8f) {
				v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
				v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
			}
		}
		//押し戻す
		m_pos += v;
	}
	break;
	}
}

void Warrok::TakeDamage(const CVector3D& vec)
{
	//敵のHPが0より大きい場合
	if (m_hp > 0) {
		m_state = eState_Damage;
	}
	else {
		m_state = eState_Death;
	}
}
