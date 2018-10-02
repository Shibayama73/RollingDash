//============================================================//
//*���@�O	Heart.cpp
//*���@�e	�S�[���̃n�[�g
//*���@�t	2017.5.21
//*�X�@�V	2017.5.21
//*�����	N.Shibayama
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

	//	��]
	m_rotation.y += 0.05f;
	m_model.SetRotation(m_rotation);
}

void Heart::Draw()
{
	m_model.Draw();
}

//	���W�ύX
void Heart::ChangePos(Vector3 pos)
{
	m_model.SetTranslation(pos);
}
