//============================================================//
//*名　前	CubeStage.cpp
//*内　容	立方体のステージ
//*日　付	2018.6.27
//*更　新	2018.6.27
//*制作者	N.Shibayama
//============================================================//
#include "CubeStage.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	回転値
const float CubeStage::ROTATE = 0.003f;
//	半径値
const float CubeStage::RADIUS = 5.0f;

CubeStage::CubeStage()
{
}

CubeStage::~CubeStage()
{
}

void CubeStage::Initialize(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 sca)
{
	m_model.LoadModel(L"Resources/cubeStage.cmo");

	//	座標
//	const Vector3 pos(0.0f, -25.0f, 0.0f);	//def:(y)-5.0f
	const Vector3 position = pos;
	//	回転
	const Vector3 rot(0.0f, 0.0f, 0.0f);
	//const Vector3 rot(XM_PI, 0.0f, 0.0f);

	//	スケール
	//Vector3(5.0f, 5.0f, 5.0f)
	const Vector3 scale = sca;

	//	初期位置の設定
	m_model.SetTranslation(position);
	m_model.SetScale(scale);	//def:1.0f
	m_model.SetRotation(rot);

	//	立方体の当たり判定初期化(OBB)
	m_obbNode.Initialize();
	m_obbNode.SetParent(&m_model);
	m_obbNode.SetLocalCenter(position);
	m_obbNode.SetRadius(scale * RADIUS);	//def:5.0f (radius=scale*5)
	m_obbNode.SetLocalRotation(rot);

	//	回転角度の初期化
	m_rotation = 0.0f;
	//	回転方向フラグの初期化
	m_isRot = false;
	//	衝突フラグの初期化
	m_isCollision = false;

}

void CubeStage::Update()
{
	m_model.Update();
	m_obbNode.Update();

	//	衝突していたら
	if(m_isCollision)
	{
		//	回転方向を変える
		if (m_isRot) m_isRot = false;
		else m_isRot = true;
		m_isCollision = false;
	}

	//	回転方向に回転させる
	if (m_isRot) m_rotation -= ROTATE;
	else m_rotation += ROTATE;

	m_model.SetRotation(Vector3(0, 0, m_rotation));
	m_obbNode.SetLocalRotation(Vector3(0, 0, m_rotation));

}

void CubeStage::Draw()
{
	m_model.Draw();
	m_obbNode.Draw();
}

void CubeStage::OnCollision()
{
	m_isCollision = true;
}
