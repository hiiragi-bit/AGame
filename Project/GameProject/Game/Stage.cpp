#include "Stage.h"
#include "TPSCamera.h"
Stage::Stage()
	:Base(eField)
{
	//モデルの取得
	mp_model = GET_RESOURCE("Stage", CModelObj);
	//位置設定
	m_pos = CVector3D(0, 0, 0);
	m_rot = CVector3D(0, 0, 0);
	m_scale = CVector3D(1.0f, 1.0f, 1.0f);
}

void Stage::Update()
{
}

void Stage::Render()
{
	mp_model->SetPos(m_pos);
	mp_model->SetRot(m_rot);
	mp_model->SetScale(m_scale);
	mp_model->Render();
}

CModel* Stage::GetModel()
{
	//当たり判定用のモデルを返す
	return mp_model;
}

SkyBox::SkyBox()
	:Base(eSkyBox)
{
	//モデルの複製
	m_model = COPY_RESOURCE("Sky", CModelObj);
	for (int i = 0; i < m_model.GetMaterialSize(); i++) {
		CMaterial* m = m_model.GetMaterial(i);
		if (!m)continue;
		if (m->mp_texture) {
			//テクスチャーの貼り方変更
			m->mp_texture->SetWrapST(GL_CLAMP_TO_EDGE);
		}
		//スカイボックス用シェーダー
		m->m_shader_name = "Sky";
	}
}

void SkyBox::Render()
{
	//影描画中は何もせずに関数から抜ける
	if (CShadow::isDoShadow())return;

	//深度テストOFF
	//ここでの描画は深度バッファへ影響しない
	glDisable(GL_DEPTH_TEST);

	//スカイボックス描画
	m_model.Render();

	//元の設定に戻す
	//深度テストON
	glEnable(GL_DEPTH_TEST);
}
