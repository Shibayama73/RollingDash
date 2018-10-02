//============================================================//
//*名　前	Shield.cpp
//*内　容	シールド
//*日　付	2018.5.22
//*更　新	2018.5.22
//*制作者	N.Shibayama
//============================================================//
#include "Shield.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void Shield::Initialize(Vector3 pos)
{
	this->m_model.LoadModel(L"Resources/cubeStage.cmo");

	Vector3 trans = pos;
	Vector3 scalse = Vector3(0.2f, 0.04f, 0.2f);
	Vector3 rot = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 radius = Vector3(1.0f, 0.2f, 1.0f);

	//	初期位置の設定
	this->m_model.SetTranslation(trans);
	this->m_model.SetScale(scalse);
	this->m_model.SetRotation(rot);

	//	立方体の当たり判定初期化(OBB)
	m_obbNode.Initialize();
	m_obbNode.SetParent(&m_model);
	m_obbNode.SetLocalCenter(trans);
	m_obbNode.SetRadius(radius);
	m_obbNode.SetLocalRotation(rot);

}

void Shield::Update()
{
	m_model.Update();
	m_obbNode.Update();

}

void Shield::Draw()
{
	m_model.Draw();
	m_obbNode.Draw();
}
