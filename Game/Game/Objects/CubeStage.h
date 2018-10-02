//============================================================//
//*���@�O	CubeStage.h
//*���@�e	�����̂̃X�e�[�W
//*���@�t	2018.6.27
//*�X�@�V	2018.6.27
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "..\..\Library\Collision\OBB\OBB.h"
#include "..\..\Library\Collision\OBB\GroundNode.h"
#include "..\..\Library\Collision\OBB\OBBNode.h"
#include "..\..\Library\Collision\OBB�~OBB\OBBCollision.h"

class CubeStage
{
private:
	//	��]�l
	static const float ROTATE;
	//	���a�l
	static const float RADIUS;

public:
	CubeStage();
	~CubeStage();

	//	������
	void Initialize(DirectX::SimpleMath::Vector3 pos,DirectX::SimpleMath::Vector3 sca);
	//	�X�V
	void Update();
	//	�`��
	void Draw();
	//	�Փ˂������Ƃ�`����
	void OnCollision();

	//	�Փ˂��Ă��邩�ǂ���
	bool IsCollision() { return m_isCollision; }

	//	���W�擾
	DirectX::SimpleMath::Vector3 GetTranslation() { return m_model.GetTranslation(); }
	//	�p�x�擾(���W�A��)
	DirectX::SimpleMath::Vector3 GetRotation() { return m_model.GetRotation(); }

	//	����]
	void LeftRot() { m_isRot = false; }
	//	�E��]
	void RightRot() { m_isRot = true; }

	//	�����̓����蔻��
	OBBNode m_obbNode;

private:
	//	�����̃��f��
	Object3D m_model;
	//	��]�p�x
	float m_rotation;
	//	��]�����t���O
	bool m_isRot;
	//	�Փ˃t���O
	bool m_isCollision;

};
