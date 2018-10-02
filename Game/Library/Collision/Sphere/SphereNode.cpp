//============================================================//
//*���@�O	SphereNode.cpp
//*���@�e	�������蔻��m�[�h
//*���@�t	2017.9.20
//*�X�@�V	2018.5.10
//*�����	N.Shibayama
//============================================================//
#include "SphereNode.h"
using namespace DirectX::SimpleMath;

SphereNode::SphereNode()
{
	//	���a�̏�����(1m)
	m_localRadius = 1.0f;
}

void SphereNode::Initialize()
{
	//	�f�o�b�O�\���p���f���Ǎ���
	m_object.LoadModel(L"Resources/sphereNode.cmo");
}

void SphereNode::Update()
{
	m_object.SetTranslation(m_trans);
	m_object.SetScale(Vector3(m_localRadius));

	m_object.Update();

	{//	���苅�̗v�f���v�Z
		const Matrix worldm = m_object.GetWorld();

		//	���f�����W�n�ł̒��S�_
		Vector3 center(0, 0, 0);
		//	���f�����W�n�ł̉E�[�̓_
		Vector3 right(1, 0, 0);

		//	���[���h���W�n�ɕϊ�
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		//	���苅�̗v�f����
		SphereCollision::m_center = center;
		SphereCollision::m_radius = Vector3::Distance(center, right);

	}

}

void SphereNode::Draw()
{
	m_object.Draw();
}
