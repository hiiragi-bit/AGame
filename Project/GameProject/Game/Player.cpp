#include "Player.h"

Player::Player(const CVector3D& pos)
	:Base(ePlayer)
{
	//プレイヤーモデルの複製
	m_model = COPY_RESOURCE("Boy", CModelA3M);
	//剣モデルの複製
	m_sword_model = COPY_RESOURCE("Sword", CModelObj);
	//アニメ調にする
	m_model.SetToon(true);
	//プレイヤーの座標
	m_pos = pos;
	//当たり判定用球の半径
	m_rad = 0.3f;
	m_state = eState_Idle;
	m_height = 2.0f;
	m_attack_flag = false;
	//接地フラグ
	m_is_ground = true;
	m_state_step = 0;

	//腰のボーン
	m_upper_body = 4;
	//上半身終わり
	const int upper_body_end = 81;
	for (int i = m_upper_body; i <= upper_body_end; i++) {
		m_model.GetNode(i)->SetAnimationLayer(1);
	}
}

void Player::Move()
{
	float cam_ang = 0;
	if (Base* b = Base::FindObject(eCamera)) {
		//カメラの回転値を取得
		cam_ang = b->m_rot.y;
		//キャラクターの回転値をカメラの回転値に合わせる
		m_rot.y = b->m_rot.y;
		//m_rot.x = b->m_rot.x;
	}

	//キャラクターの移動量
	const float move_speed = 0.1f;

	if (m_is_ground && PUSH(CInput::eButton5)) {
		m_vec.y = 0.2;
		m_is_ground = false;
	}

	//方向キーのベクトル
	CVector3D key_dir(0, 0, 0);
	//キーの方向ベクトルを設定
	//Wキー
	if (HOLD(CInput::eUp))
		key_dir.z = 1;
	//Sキー
	if (HOLD(CInput::eDown))
		key_dir.z = -1;
	//Aキー
	if (HOLD(CInput::eLeft))
		key_dir.x = 1;
	//Dキー
	if (HOLD(CInput::eRight))
		key_dir.x = -1;

	//移動処理
	//入力があれば
	if (key_dir.LengthSq() > 0) {
		//■移動処理 回転行列×キー方向
		//方向ベクトル
		CVector3D dir = CMatrix::MRotationY(m_rot.y) * key_dir;
		//移動
		m_pos += dir * move_speed;
		//ジャンプ中なら
		/*if (!m_is_ground) {

		}*/
		//走るアニメーション
		m_model.ChangeAnimation(0, eAnim_Run);
	}
	else {
		//待機アニメーション
		m_model.ChangeAnimation(0, eAnim_Idle);
	}
}

void Player::StateIdle()
{
	Move();
	m_model.ChangeAnimation(1, m_model.GetAnimationJam(0));

	//マウス左クリックで攻撃状態へ
	if (PUSH(CInput::eMouseL)) {
		m_state = eState_Attack;
	}
}

void Player::StateAttack()
{
	Move();
	m_model.ChangeAnimation(1, eAnim_AttackCombo1, false);
	switch (m_state_step) {
	case 0:
		if (m_model.GetAnimationFrame(1) > 15) {
			m_attack_flag = true;
			m_state_step++;
		}
		break;
	case 1:
		if (m_model.GetAnimationFrame(1) > 18) {
			m_attack_flag = false;
			m_state_step++;
		}
		break;
	case 2:
		if (25 < m_model.GetAnimationFrame(1) > 18) {
			if (PUSH(CInput::eMouseL)) {
				m_model.ChangeAnimation(1, eAnim_AttackCombo2, false);
				m_attack_flag = true;
				m_state_step++;
			}
		}
		else if (m_model.GetAnimationFrame(1) > 26) {
			m_state_step = 4;
		}
		break;
	case 4:
		if (m_model.isAnimationEnd(1)) {
			m_state_step = 0;
			m_state = eState_Idle;
		}
		break;
	}
}

void Player::Update()
{
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Attack:
		StateAttack();
		break;
	}	
	
	//重力落下
	m_vec.y -= GRAVITY;
	m_pos += m_vec;

	//カプセルを設定
	m_capusle = CCapsule(m_pos + CVector3D(0, m_height - m_rad, 0),	//始点（頭）
		m_pos + CVector3D(0, m_rad, 0),								//終点（足元）
		m_rad);

	//アニメーション更新
	m_model.UpdateAnimation();
}

void Player::Render()
{
	m_model.BindFrameMatrix(m_upper_body, CMatrix::MRotation(m_rot));
	m_model.SetPos(m_pos);
	m_model.SetRot(0, m_rot.y, 0);
	m_model.SetScale(0.01f, 0.01f, 0.01f);
	m_model.Render();

	//■剣の描画
	//右手のボーン
	const int hand_idx = 66;
	//武器のワールド行列=ボーンの行列
	//×武器のローカル行列（平行移動×回転×スケール）
	m_sword_matrix = m_model.GetFrameMatrix(hand_idx)
		* CMatrix::MTranselate(0.0, 0.0, -0.05)
		* CMatrix::MRotationX(DtoR(90))
		* CMatrix::MRotationY(DtoR(-90))
		* CMatrix::MRotationZ(DtoR(0))
		* CMatrix::MScale(0.005f, 0.005f, 0.005f);
	//武器の描画
	m_sword_model.Render(m_sword_matrix);
	//剣のカプセル描画
	CVector3D sword_s, sword_e;
	float sword_rad = 0.45f;
	sword_s = m_sword_matrix * CVector4D(0, 0, 20, 1);
	sword_e = m_sword_matrix * CVector4D(0, 0, 150, 1);
	Utility::DrawCapsule(sword_s, sword_e, sword_rad, CVector4D(1, 0, 0, 0.5));
	m_attack_cap = CCapsule(sword_s, sword_e, sword_rad);
}

void Player::Collision(Base* b)
{
	switch (b->GetType()) {
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
			//攻撃との判定
			if (m_attack_flag &&
				CCollision::CollisionCapsule(m_attack_cap, b->m_capusle, &dist, &c1, &d1)) {
				if (IDamage* d = dynamic_cast<IDamage*>(b)) {
					d->TakeDamage(CVector3D(0, 0, 0));
					//多重ヒット防止
					m_attack_flag = false;
				}
			}
		}
		break;
		//ステージとの判定
		case eField:
		//モデルとの判定(球)(カプセル)
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
						m_is_ground = true;
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

void Player::TakeDamage(const CVector3D& vec)
{
}
