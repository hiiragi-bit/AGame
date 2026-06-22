#include "TPSCamera.h"

TPSCamera::TPSCamera()
	:Base(eCamera)
	, m_dist(4.0f)
{
	//カメラ回転値
	m_rot = CVector3D(DtoR(30), DtoR(-125), 0);
}

void TPSCamera::Update()
{
	//回転速度係数
	float cam_speed = 0.002f;
	//マウスの移動量
	CVector2D mouse_vec = CInput::GetMouseVec();
	//マウス移動からカメラを回転
	//マウス移動Y→X軸回転(上下)
	//マウス移動X→Y軸回転(左右)
	m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0) * cam_speed;
	//上下角制限
	m_rot.x = min(DtoR(45), max(DtoR(-45), m_rot.x));
	//-180～180に正規化
	m_rot.y = Utility::NormalizeAngle(m_rot.y);
	//距離制限
	m_dist = min(10.0f, max(2.0f, m_dist + CInput::GetMouseWheel()));
}

void TPSCamera::Render()
{
	//影描画中は何もせずに関数から抜ける
	if (CShadow::isDoShadow())return;

	//プレイヤーの取得
	if (Base* b = Base::FindObject(ePlayer)) {
		//キャラクターの右肩ごしにカメラを設置する
		CMatrix cam_matrix = CMatrix::MTranselate(b->m_pos)
			* CMatrix::MTranselate(CVector3D(0, 1.1, 0))
			* CMatrix::MRotation(m_rot)
			* CMatrix::MTranselate(CVector3D(-0.5, 0.4, -2));
		//カメラのワールド行列でカメラを設定
		CCamera::GetCurrent()->SetTranseRot(cam_matrix);
	}
}
