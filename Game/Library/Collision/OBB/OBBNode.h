//============================================================//
//*���@�O	OBBNode.h
//*���@�e	OBB�m�[�h
//*���@�t	2017.10.23
//*�X�@�V	2018.7.20
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "OBB.h"
#include "GroundNode.h"

class OBBNode :public GroundNode, public OBB
{
public:
	OBBNode();
	//	������
	void Initialize();
	//	�X�V
	void Update();
	//	�`��
	void Draw();

	//	���[�J�����S���W�̐ݒ�
	void SetLocalCenter(DirectX::SimpleMath::Vector3 center);
	//	���[�J���p�x�̐ݒ�
	void SetLocalRotation(DirectX::SimpleMath::Vector3 rotation);
	//	��]�s��̐ݒ�
	DirectX::SimpleMath::Matrix SetRotation(DirectX::SimpleMath::Vector3 rotation);
	//	���a�̐ݒ�
	void SetRadius(DirectX::SimpleMath::Vector3 radius);

	//	���[�J�����S���W�̎擾
	DirectX::SimpleMath::Vector3 GetLocalCenter();
	//	���[�J���p�x�̎擾
	DirectX::SimpleMath::Vector3 GetLocalRotation();
	//	��]�s��̎擾
	DirectX::SimpleMath::Matrix GetRotation();
	//	���a�̎擾
	DirectX::SimpleMath::Vector3 GetRadius();
	//	�������̎擾
	DirectX::SimpleMath::Vector3 GetLocalSeparationAxisX();
	DirectX::SimpleMath::Vector3 GetLocalSeparationAxisY();
	DirectX::SimpleMath::Vector3 GetLocalSeparationAxisZ();
	//	���S���W�̎擾
	DirectX::SimpleMath::Vector3 GetCenter();

private:
	//	���[�J�����S���W
	DirectX::SimpleMath::Vector3 m_localCenter;
	//	���[�J���p�x
	DirectX::SimpleMath::Vector3 m_localRotation;
	//	��]�s��
	DirectX::SimpleMath::Matrix m_rotation;

};
