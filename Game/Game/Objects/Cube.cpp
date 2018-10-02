//============================================================//
//*���@�O	Cube.cpp
//*���@�e	������
//*���@�t	2017.5.29
//*�X�@�V	2017.5.29
//*�����	N.Shibayama
//============================================================//
#include "Cube.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::Initialize(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 scale, float angle)
{
	m_model.LoadModel(L"Resources/cubeStage.cmo");

	Vector3 position = pos;// Vector3(10.0f, 15.0f, 0.0f);
	Vector3 scalse = scale;// Vector3(1.0f, 1.0f, 1.0f);
	Vector3 rot = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 radius = scale * 5.0f;// Vector3(5.0f, 5.0f, 5.0f);
	m_angleValue = angle;

	//	�����ʒu�̐ݒ�
	m_model.SetTranslation(position);
	m_model.SetScale(scalse);
	m_model.SetRotation(rot);

	//	�����̂̓����蔻�菉����(OBB)
	m_obbNode.Initialize();
	m_obbNode.SetParent(&m_model);
	m_obbNode.SetLocalCenter(position);
	m_obbNode.SetRadius(radius);
	m_obbNode.SetLocalRotation(rot);

	//	��]�p�x�̏�����
	m_angle = 0.0f;

	//	��]�t���O�̏�����
	m_isRot = false;
	//	����]�t���O�̏�����
	m_isRotLeft = false;

}

void Cube::Update(OBBNode& obb)
{
	m_model.Update();
	m_obbNode.Update();

	//	OBB���m�̓����蔻��
	OBBCollision obbCollision;

	//	OBB�ɏՓ˂�����
	if (obbCollision.IsOBB2OBBCollision(m_obbNode, obb))
	{
		//	��]������ς���
		if (m_isRotLeft) m_isRotLeft = false;
		else m_isRotLeft = true;
	}

	if (m_isRot)
	{
		//	��]�����ɉ�]������
		if (m_isRotLeft) m_angle -= m_angleValue;
		else m_angle += m_angleValue;
	}

	m_model.SetRotation(Vector3(0, 0, m_angle));
	m_obbNode.SetLocalRotation(Vector3(0, 0, m_angle));

}

void Cube::Draw()
{
	m_model.Draw();
	m_obbNode.Draw();
}

void Cube::StartRot()
{
	m_isRot = true;
}

void Cube::StopRot()
{
	m_isRot = false;
}
