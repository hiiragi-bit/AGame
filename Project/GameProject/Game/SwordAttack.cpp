#include "SwordAttack.h"
#include "Enemy.h"

SwordAttack::SwordAttack()
	:Base(ePlayer_Attack)
{
	m_sword_s = m_sword_matrix * CVector4D(0, 0, 20, 1);
	m_sword_e = m_sword_matrix * CVector4D(0, 0, 150, 1);
	m_rad = 0.1f;
}

void SwordAttack::Update()
{
	m_capusle = CCapsule(m_sword_s, m_sword_e, m_rad);
	Utility::DrawCapsule(m_sword_s, m_sword_e, m_rad, CVector4D(1, 0, 0, 0.5));
}

void SwordAttack::Collision(Base* b)
{
	switch (b->GetType()) {
		//敵との判定
		case eEnemy:
		{
			CVector3D c1, d1;
			float dist;
			//カプセル同士の判定
			if (CCollision::CollisionCapsule(m_capusle, b->m_capusle, &dist, &c1, &d1)) {
				if (Enemy* e = dynamic_cast<Enemy*>(b)) {
					CVector3D dir = m_dir;
					//敵のダメージを受ける関数を呼び出す
					//引数には吹っ飛ぶベクトルを与える
					e->TakeDamage(CVector3D(dir.x, 1, dir.y) * 0.4f);
				}
			}
		}
		break;
	}
}
