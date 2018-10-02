//============================================================//
//*���@�O	Camera.cpp
//*���@�e	�J����
//*���@�t	2017.7.11
//*�X�@�V	2017.7.11
//*�����	N.Shibayama
//============================================================//
#include "..\..\Library\Framework\pch.h"
#include "Camera.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace DirectX::SimpleMath;

Camera::Camera(int width, int height)
{
	//	������==========================================
	//	�J�����̈ʒu�i���_���W�j
	m_eyepos = Vector3(0, 0, 20.0f);
	//	�J�����̌��Ă����i�����_�E�Q�Ɠ_�j
	m_refpos = Vector3(0, 0, 10);
	//	�J�����̏�����x�N�g��
	m_upvec = Vector3(0, 1.0f, 0);

	//	������������p
	m_fovY = XMConvertToRadians(60.0f);
	//	�A�X�y�N�g��i��ʔ䗦�j
	m_aspect = (float)width / height;
	//	�j�A�N���b�v�i��O�̕\�����E�����j
	m_nearclip = 0.1f;
	//	�t�@�[�N���b�v�i���̕\�����E�����j
	m_farclip = 1000.0f;

	//=======================================================
	//	�r���[�s��̐���
	m_upvec.Normalize();	//������1�ɒ�������
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//	�ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

Camera::~Camera()
{
}

//	�X�V
void Camera::Update()
{
	//	�r���[�s��̐���
	m_upvec.Normalize();	//������1�ɒ�������
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//	�ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

//	�r���[�s��̎擾
const DirectX::SimpleMath::Matrix& Camera::GetViewMatrix()
{
	////	�r���[�s��̐���
	//m_upvec.Normalize();	//������1�ɒ�������
	//m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	return m_view;
}

//	�ˉe�s��̎擾
const DirectX::SimpleMath::Matrix& Camera::GetProjectionMatrix()
{
	////	�ˉe�s��̐���
	//m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

	return m_proj;
}

//	���_���W�̃Z�b�g
void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& eyepos)
{
	//	���_���W��eyepos
	m_eyepos = eyepos;
}

//	�����_�E�Q�Ɠ_�Z�b�g
void Camera::SetRefPos(const DirectX::SimpleMath::Vector3& refpos)
{
	m_refpos = refpos;
}

//	�J�����̌����̃Z�b�g
void Camera::SetUpvec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;
}

//	������������p�̃Z�b�g
void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

//	�A�X�y�N�g��̃Z�b�g
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

//	�j�A�N���b�v�̃Z�b�g
void Camera::SetNearclip(float nearclip)
{
	m_nearclip = nearclip;
}

//	�t�@�[�N���b�v�̃Z�b�g
void Camera::SetFarclip(float farclip)
{
	m_farclip = farclip;
}

// �r���{�[�h�s��̌v�Z
void Camera::CalcBillboard()
{
	// ��������
	Vector3 eyeDir = m_eyepos - m_refpos;
	// Y��
	Vector3 Y = Vector3::UnitY;
	// X��
	Vector3 X = Y.Cross(eyeDir);
	X.Normalize();
	// Z��
	Vector3 Z = X.Cross(Y);
	Z.Normalize();
	// Y������r���{�[�h�s��i�E��n�̈�Z�������]�j
	m_billboardConstrainY = Matrix::Identity;
	m_billboardConstrainY.m[0][0] = X.x;
	m_billboardConstrainY.m[0][1] = X.y;
	m_billboardConstrainY.m[0][2] = X.z;
	m_billboardConstrainY.m[1][0] = Y.x;
	m_billboardConstrainY.m[1][1] = Y.y;
	m_billboardConstrainY.m[1][2] = Y.z;
	m_billboardConstrainY.m[2][0] = -Z.x;
	m_billboardConstrainY.m[2][1] = -Z.y;
	m_billboardConstrainY.m[2][2] = -Z.z;

	Y = eyeDir.Cross(X);
	Y.Normalize();
	eyeDir.Normalize();
	// �r���{�[�h�s��i�E��n�̈�Z�������]�j
	m_billboard = Matrix::Identity;
	m_billboard.m[0][0] = X.x;
	m_billboard.m[0][1] = X.y;
	m_billboard.m[0][2] = X.z;
	m_billboard.m[1][0] = Y.x;
	m_billboard.m[1][1] = Y.y;
	m_billboard.m[1][2] = Y.z;
	m_billboard.m[2][0] = -eyeDir.x;
	m_billboard.m[2][1] = -eyeDir.y;
	m_billboard.m[2][2] = -eyeDir.z;
}
