//============================================================//
//*���@�O	Player.h
//*���@�e	�v���C���[
//*���@�t	2018.5.22
//*�X�@�V	2018.7.23
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "Object3D.h"
#include <keyboard.h>
#include "..\..\Library\Collision\Sphere\SphereNode.h"
#include "..\..\Library\Keyboards\Keyboards.h"
#include "..\..\Library\Collision\OBB2Sphere\OBB2SphereCollision.h"
#include "..\..\Game\Objects\CubeStage.h"
#include "..\..\Game\Objects\Shield.h"

class Player
{
private:
	//	�O�i����l
	const float FORWARD_Z = 0.4f;
	//	��ނ���l
	const float BACKWARD_Z = 0.3f;
	//	�����񂷂�l
	const float LEFTTURN_Y = 0.05f;
	//	�E���񂷂�l
	const float RIGHTTURN_Y = 0.05f;
	//	�߂荞�ݒ��˕Ԃ�l
	const float REBOUND = 0.1f;
	//	�d�͒l
	const DirectX::SimpleMath::Vector3 GRAVITY = DirectX::SimpleMath::Vector3(0.0f, -0.098f, 0.0f);

	//	�X�e�[�W�̈�𒴂������E�n
	const float AREA_OVER_Y = -25.0f;

public:
	//	������
	void Initialize();
	//	�X�V
	void Update();
	//	�`��
	void Draw();

	//	���s�ړ��̐ݒ�
	void SetTranslation(DirectX::SimpleMath::Vector3 trans) { m_model.SetTranslation(trans); }
	//	��]�p�̐ݒ�
	void SetRotation(DirectX::SimpleMath::Vector3 angle) { m_model.SetRotation(angle); }
	//	���s�ړ��̎擾
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_model.GetTranslation(); }
	//	��]�p�̎擾
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_model.GetRotation(); }
	//	���@�̓����蔻��擾
	const SphereNode& GetCollisionNode() { return m_collisionNode; }
	//	���@��OBB�������������ǂ���
	bool IsOBBCollision(OBBNode& obb);

	//	�O�i
	void Forward();
	//	���
	void Backward();
	//	������
	void LeftTurn();
	//	�E����
	void RightTurn();

	//	OBB�I�u�W�F�N�g�ƏՓ˂��Ă�����߂荞�ݖ߂�������
	void ObbColSinkRestore(OBBNode& obb);
	//	�X�e�[�W�ƏՓ˂��Ă�����߂荞�ݖ߂�������
	void StageColSinkRestore(CubeStage& obb);
	//	�n��(OBB)�Ƃ̂߂荞�ݕ��߂�
	void SinkRestore(OBBNode& obb);
	//	�V�[���h�ƏՓ˂��Ă�����߂荞�ݖ߂�������
	void ShieldColSinkRestore(OBBNode& obb);
	//	�V�[���h�Ƃ̂߂荞�ݕ��߂�
	void ShieldSinkRestore(OBBNode& obb);
	//	�d�͂�������
	void Gravity();
	//	�Q�[���I�[�o�[�G���A���z���邩�ǂ���
	bool IsAreaOver(OBBNode& obb);
	//	������g�p��~����
	void StopControl();

private:
	//	���@
	Object3D m_model;
	//	���@�̓����蔻��
	SphereNode m_collisionNode;

	//	�������Ă��邩�ǂ���
	bool m_isCollision;

};
