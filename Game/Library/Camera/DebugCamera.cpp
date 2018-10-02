//============================================================//
//*���@�O	DebugCamera.cpp
//*���@�e	�f�o�b�O�p�J����
//*���@�t	2017.7.11
//*�X�@�V	2017.7.11
//*�����	N.Shibayama
//============================================================//
#include "DebugCamera.h"
#include "mouse.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 8.0f;

DebugCamera::DebugCamera(int width, int height)
	: m_yAngle(0.0f), m_yTmp(0.0f), m_xAngle(0.0f), m_xTmp(0.0f), m_x(0), m_y(0), m_scrollWheelValue(0)
{
	//	��ʃT�C�Y�ɑ΂���X�P�[������
	this->m_sx = 1.0f / (float)width;
	this->m_sy = 1.0f / (float)height;
	this->m_view = DirectX::SimpleMath::Matrix::Identity;

	//	�}�E�X�̏�����
	this->m_mouse = std::make_unique<Mouse>();
	this->m_mouseTracker = std::make_unique<Mouse::ButtonStateTracker>();
}

void DebugCamera::Update()
{
	//	�}�E�X���̎擾
	this->m_mouseState = this->m_mouse->GetState();
	this->m_mouseTracker->Update(this->m_mouseState);

	//	�}�E�X�̍��{�^���������ꂽ�Ƃ�
	if (this->m_mouseTracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED) {
		//	�}�E�X�̍��W���擾
		this->m_x = this->m_mouseState.x;
		this->m_y = this->m_mouseState.y;
	}
	//	�}�E�X�̍��{�^���������ꂽ�Ƃ�
	else if (this->m_mouseTracker->leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED) {
		//	���݂̉�]��ۑ�
		this->m_xAngle = this->m_xTmp;
		this->m_yAngle = this->m_yTmp;
	}
	//	�}�E�X�̃{�^����������Ă�����J�������ړ�������
	if (this->m_mouseState.leftButton) {
		Motion(this->m_mouseState.x, this->m_mouseState.y);
	}

	//	�}�E�X�z�C�[���l�̎擾
	this->m_scrollWheelValue = this->m_mouseState.scrollWheelValue;
	if (this->m_scrollWheelValue > 0) {
		//	�X�N���[���z�C�[���l�̏�����
		this->m_scrollWheelValue = 0;
		//	�}�E�X�̃X�N���[���z�C�[���l�����Z�b�g
		this->m_mouse->ResetScrollWheelValue();
	}

	//	y������]���Ƃ��Ē��_�̃Z�b�g����]�����邽�߂Ɏg�p�ł���s���Ԃ�
	Matrix rotateY = Matrix::CreateRotationY(m_yTmp);
	//	x������]���Ƃ��Ē��_�̃Z�b�g����]�����邽�߂Ɏg�p�ł���s���Ԃ�
	Matrix rotateX = Matrix::CreateRotationX(m_xTmp);

	Matrix rotate = rotateY * rotateX;

	Vector3 eye(0.0f, 0.0f, 1.0f);
	Vector3 target(0.0f, 0.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	//	�w�肳�ꂽ�s����g�p����3D�x�N�g�����g�����X�t�H�[������
	eye = Vector3::Transform(eye, rotate.Invert());

	eye = eye * (DEFAULT_CAMERA_DISTANCE - this->m_scrollWheelValue / 100);
	//	�w�肳�ꂽ�s����g�p���� 3D �x�N�g�����g�����X�t�H�[������
	up = Vector3::Transform(up, rotate.Invert());
	//	�r���[�s��𐶐�����
	this->m_view = Matrix::CreateLookAt(eye, target, up);
}

//	�s��𐶐�����
void DebugCamera::Motion(int x, int y)
{
	//	�}�E�X�|�C���^�̈ʒu�̃h���b�O�J�n�ʒu����̕ψ� (���Βl)
	float dx = (x - m_x) * this->m_sx;
	float dy = (y - m_y) * this->m_sy;

	if (dx != 0.0f || dy != 0.0f) {
		//	�x���̉�]
		float yAngle = dx * XM_PI;
		//	�w���̉�]
		float xAngle = dy * XM_PI;

		this->m_xTmp = this->m_xAngle + xAngle;
		this->m_yTmp = this->m_yAngle + yAngle;
	}
}
