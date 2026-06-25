#include "Enemy.h"

Enemy::Enemy(const CVector3D& pos)
	:Base(eEnemy)
{
	//モデルの複製
	m_model = COPY_RESOURCE("Golem", CModelA3M);
	//位置設定
	m_pos = pos;
	//回転値
	m_rot = CVector3D(0, 0, 0);
	//スケール
	m_scale = CVector3D(0.01f, 0.01f, 0.01f);
	//当たり判定の半径
	m_rad = 0.8f;
}

void Enemy::Update()
{
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

void Enemy::Render()
{
	m_model.SetPos(m_pos);
	m_model.SetRot(m_rot);
	m_model.SetScale(m_scale);
	m_model.Render();
}

void Enemy::Collision(Base* b)
{
	switch (b->GetType()) {
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

void Enemy::TakeDamage(const CVector3D& vec)
{
	SetKill();
}
