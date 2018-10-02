//============================================================//
//*���@�O	SphereNode.h
//*���@�e	�������蔻��m�[�h
//*���@�t	2017.9.20
//*�X�@�V	2018.5.10
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "SphereCollision.h"
#include "CollisionNode.h"

class SphereNode :public CollisionNode, public SphereCollision
{
public:
	SphereNode();
	//	������
	void Initialize();
	//	�X�V
	void Update();
	//	�`��
	void Draw();

	//	���[�J�����a�̃Z�b�g
	void SetLocalRadius(float radius) { m_localRadius = radius; }
	//	���_�̎擾
	DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
	//	���a�̎擾
	float GetRadius() { return m_radius; }

protected:
	//	���[�J�����a
	float m_localRadius;

};
