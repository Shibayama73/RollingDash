//============================================================//
//*���@�O	Shield.cpp
//*���@�e	�V�[���h
//*���@�t	2018.5.22
//*�X�@�V	2018.5.22
//*�����	N.Shibayama
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

	//	�����ʒu�̐ݒ�
	this->m_model.SetTranslation(trans);
	this->m_model.SetScale(scalse);
	this->m_model.SetRotation(rot);

	//	�����̂̓����蔻�菉����(OBB)
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
