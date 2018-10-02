//============================================================//
//*���@�O	DebugCamera.h
//*���@�e	�f�o�b�O�p�J����
//*���@�t	2017.7.11
//*�X�@�V	2017.7.11
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Mouse.h>

class DebugCamera
{
private:
	// �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;

	// �}�E�X�X�e�[�g
	DirectX::Mouse::State m_mouseState;
	// �}�E�X
	std::unique_ptr<DirectX::Mouse> m_mouse;
	// �{�^���X�e�[�g�g���b�J�[
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;

	// ����]
	float m_yAngle, m_yTmp;
	// �c��]
	float m_xAngle, m_xTmp;

	// �h���b�O���ꂽ���W
	int m_x, m_y;
	float m_sx, m_sy;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �X�N���[���z�C�[���l
	int m_scrollWheelValue;

private:

	void Motion(int x, int y);

public:
	// �R���X�g���N�^
	DebugCamera(int width, int height);

	// �X�V����
	void Update();
	// �J�����s��𐶐�����
	DirectX::SimpleMath::Matrix GetCameraMatrix() {
		return m_view;
	}
};
