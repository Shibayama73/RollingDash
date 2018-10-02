//============================================================//
//*���@�O	FollowCamera.cpp
//*���@�e	�ǔ��J����
//*���@�t	2017.7.11
//*�X�@�V	2017.7.11
//*�����	N.Shibayama
//============================================================//
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	�ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 12.0f;

FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	//	������===============================
	//	�Ǐ]�Ώۂ̍��W
	m_targetPos = Vector3(0, 0, 0);
	//	�Ǐ]�Ώۂ̉�]�p
	m_targetAngle = 0.0f;
	//	FPS�t���O
	m_isFPS = false;

	{//	TPS�J�����̏���
		Vector3 eyepos, refpos;
		//	�Q�Ɠ_���W�̌v�Z
		refpos = m_targetPos + Vector3(0, 2.0f, 0);
		//	���@����J�����܂ł̋���
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);

		//	���@������ɉ�荞�ނ��߂̉�]�s��
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		//	�J�����ւ̃x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		//	�J�������W���v�Z
		eyepos = refpos + cameraV;

		//	�J�����ɏ���n��
		this->SetRefPos(refpos);
		this->SetEyePos(eyepos);
	}

}

void FollowCamera::Update()
{
	auto& key = Keyboards::GetInstance();
	key.GetState();

	//	�J�����̐ݒ�i���@�ɒǏ]����J�����j
	//	���_�E�Q�Ɠ_�̍��W
	Vector3 eyepos, refpos;

	if (m_isFPS)
		//FPS�J������TPS�J�����͎Q�Ɠ_�ƃJ�����̍��W�v�Z�̏��Ԃ����ւ���̂�
	{//	FPS�J�����̏���
		Vector3 position;
		//	�J�������W�̌v�Z
		position = m_targetPos + Vector3(0, 0.2f, 0);

		//	���@����J�����܂ł̋���
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);

		//	���@������ɉ�荞�ނ��߂̉�]�s��
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		//	�J�����ւ̃x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		//	�����i�񂾐掋�_���W�̌v�Z
		eyepos = position + cameraV * 0.1f;
		//	��ɐi�񂾎Q�Ɠ_���W�̌v�Z
		refpos = position + cameraV;

	}

	else
	{//	TPS�J�����̏���
		 //	�Q�Ɠ_���W�̌v�Z
		refpos = m_targetPos + Vector3(0, 2.0f, 0);
		//	���@����J�����܂ł̋���
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);

		//	���@������ɉ�荞�ނ��߂̉�]�s��
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		//	�J�����ւ̃x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		//	�J�������W���v�Z
		eyepos = refpos + cameraV;

		//�S���Ђ��̋���
		//	���_�����݈ʒu�����Ԃ���
		//	�O��̎��_ + (���_�̖ڕW�_ - �O��̎��_) * 0.05f
		eyepos = m_eyepos + (eyepos - m_eyepos)*0.03f;

		//	�J�����̎Q�Ɠ_�����݈ʒu�����Ԃ���
		//	�O��̎Q�Ɠ_ + (�Q�Ɠ_�̖ڕW�_ - �O��̎Q�Ɠ_) * 0.05f
		refpos = m_refpos + (refpos - m_refpos)*0.3f;

	}

	//	�J�����ɏ���n��
	this->SetRefPos(refpos);
	this->SetEyePos(eyepos);

	//	�J����(���N���X)�̍X�V
	Camera::Update();

}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}

void FollowCamera::SetKeyboard(Keyboards * keyboard)
{
	//m_keyboard = keyboard;
}
