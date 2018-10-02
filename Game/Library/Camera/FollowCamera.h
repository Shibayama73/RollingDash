//============================================================//
//*���@�O	FollowCamera.h
//*���@�e	�ǔ��J����
//*���@�t	2017.7.11
//*�X�@�V	2017.7.11
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <Windows.h>
#include "..\Keyboards\Keyboards.h"
#include "Camera.h"
#include "..\..\..\Game\Game\Objects\Player.h"

class FollowCamera :public Camera
{
public:
	//	���@�ƃJ�����̋���
	static const float CAMERA_DISTANCE;
	//	�R���X�g���N�^
	FollowCamera(int width, int height);
	//	�X�V
	void Update() override;
	//	�Ǐ]�Ώۂ̍��W���Z�b�g
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos);
	//	�Ǐ]�Ώۂ̉�]�p���Z�b�g
	void SetTargetAngle(float targetAngle);
	//	�L�[�{�[�h���Z�b�g
	void SetKeyboard(Keyboards* keyboard);

protected:
	//	�Ǐ]�Ώۂ̍��W
	DirectX::SimpleMath::Vector3 m_targetPos;
	//	�Ǐ]�Ώۂ̉�]�p
	float m_targetAngle;

private:
	//	FPS�t���O
	bool m_isFPS;

};
