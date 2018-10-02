//============================================================//
//*名　前	Heart.cpp
//*内　容	ゴールのハート
//*日　付	2017.5.21
//*更　新	2017.5.21
//*制作者	N.Shibayama
//============================================================//
#include "Heart.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

void Heart::Initialize()
{
	this->m_model.LoadModel(L"Resources/heart.cmo");

	m_rotation = Vector3(0, 0, 0);
	this->m_model.SetTranslation(Vector3(-20.0f, 0.0f, -20.0f));
	this->m_model.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	this->m_model.SetRotation(m_rotation);

}

void Heart::Update()
{
	m_model.Update();

	//	回転
	m_rotation.y += 0.05f;
	m_model.SetRotation(m_rotation);
}

void Heart::Draw()
{
	m_model.Draw();
}

//	座標変更
void Heart::ChangePos(Vector3 pos)
{
	m_model.SetTranslation(pos);
}
