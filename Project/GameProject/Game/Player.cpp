#include "Player.h"

Player::Player(const CVector3D& pos)
	:Base(ePlayer)
{
	//モデルの複製
	m_model = COPY_RESOURCE("Boy", CModelA3M);
	//アニメ調にする
	m_model.SetToon(true);
	//プレイヤーの座標
	m_pos = pos;
	//当たり判定用球の半径
	m_rad = 0.3f;
}

void Player::Update()
{
	float cam_ang = 0;
	if (Base* b = Base::FindObject(eCamera)) {
		//カメラの回転値を取得
		cam_ang = b->m_rot.y;
		//キャラクターの回転値をカメラの回転値に合わせる
		m_rot.y = b->m_rot.y;
	}

	//キャラクターの移動量
	const float move_speed = 0.1f;

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
		m_model.ChangeAnimation(1);
	}
	else {
		m_model.ChangeAnimation(0);
	}
	
	//重力落下
	//m_vec.y -= GRAVITY;
	m_pos += m_vec;

	//アニメーション更新
	m_model.UpdateAnimation();
}

void Player::Render()
{
	m_model.SetPos(m_pos);
	m_model.SetRot(m_rot);
	m_model.SetScale(1.0f, 1.0f, 1.0f);
	m_model.Render();
}

void Player::Collision(Base* b)
{
	switch (b->GetType()) {
		case eField:
		//モデルとの判定(球)(カプセル)
		{
			//押し戻し量
			CVector3D v(0, 0, 0);
			//
		}
	}
}
