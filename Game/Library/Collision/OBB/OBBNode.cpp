//============================================================//
//*���@�O	OBBNode.cpp
//*���@�e	OBB�m�[�h
//*���@�t	2017.10.23
//*�X�@�V	2018.7.20
//*�����	N.Shibayama
//============================================================//
#include "OBBNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

OBBNode::OBBNode()
{
	//	���S���W
	m_localCenter = Vector3(0.0f, 0.0f, 0.0f);
	//	�p�x
	m_localRotation = Vector3(0.0f, 0.0f, 0.0f);
	//	��]�s��̍X�V
	SetRotation(m_localRotation);
	//	�n�ʂƂ̓�����t���O
//	m_groundFlag = false;
	//	��]�s��
	m_rotation = Matrix::Identity;

}

void OBBNode::Initialize()
{
	this->m_model.LoadModel(L"Resources/cubeStage.cmo");
}

void OBBNode::Update()
{
	//	�����ʒu�̐ݒ�
	this->m_model.SetTranslation(m_center);

	//	��]�s��̍X�V
	m_rotation = SetRotation(m_localRotation);

	//	�������̍X�V
	m_separationAxisX = Vector3::TransformNormal(Vector3(1.0f, 0.0f, 0.0f), m_rotation);
	m_separationAxisY = Vector3::TransformNormal(Vector3(0.0f, 1.0f, 0.0f), m_rotation);
	m_separationAxisZ = Vector3::TransformNormal(Vector3(0.0f, 0.0f, 1.0f), m_rotation);

	//	���f���̍X�V
	this->m_model.Update();

}

void OBBNode::Draw()
{
	this->m_model.Draw();
}

//=======================================================================//

//	���[�J�����S���W�̐ݒ�
void OBBNode::SetLocalCenter(DirectX::SimpleMath::Vector3 center)
{
	m_localCenter = center;
}

//	���[�J���p�x�̐ݒ�
void OBBNode::SetLocalRotation(DirectX::SimpleMath::Vector3 rotation)
{
	m_localRotation = rotation;
}

//	��]�s��̐ݒ�
DirectX::SimpleMath::Matrix OBBNode::SetRotation(DirectX::SimpleMath::Vector3 rotation)
{
	Matrix matrix;
	Matrix matrixX = matrix.CreateRotationX(rotation.x);
	Matrix matrixY = matrix.CreateRotationY(rotation.y);
	Matrix matrixZ = matrix.CreateRotationZ(rotation.z);

	return matrixZ*matrixX*matrixY;
}

//	���a�̐ݒ�
void OBBNode::SetRadius(DirectX::SimpleMath::Vector3 radius)
{
	m_radius = radius;
}

////	�n�ʂƂ̓�����t���O�擾
//bool OBBNode::IsGroundFlag()
//{
//	return m_groundFlag;
//}

//=======================================================================//
//	���[�J�����S���W�̎擾
DirectX::SimpleMath::Vector3 OBBNode::GetLocalCenter()
{
	return m_localCenter;
}

//	���[�J���p�x�̎擾
DirectX::SimpleMath::Vector3 OBBNode::GetLocalRotation()
{
	return m_localRotation;
}

//	��]�s��̎擾
DirectX::SimpleMath::Matrix OBBNode::GetRotation()
{
	return m_rotation;
}

//	���a�̎擾
DirectX::SimpleMath::Vector3 OBBNode::GetRadius()
{
	return m_radius;
}

//	������X
DirectX::SimpleMath::Vector3 OBBNode::GetLocalSeparationAxisX()
{
	return m_separationAxisX;
}

//	������Y
DirectX::SimpleMath::Vector3 OBBNode::GetLocalSeparationAxisY()
{
	return m_separationAxisY;
}

//	������Z
DirectX::SimpleMath::Vector3 OBBNode::GetLocalSeparationAxisZ()
{
	return m_separationAxisZ;
}

//	���S���W
DirectX::SimpleMath::Vector3 OBBNode::GetCenter()
{
	return m_center;
}

////	�n�ʂƂ̓�����t���O�ݒ�
//void OBBNode::SetGroundFlag(bool flag)
//{
//	m_groundFlag = flag;
//}
