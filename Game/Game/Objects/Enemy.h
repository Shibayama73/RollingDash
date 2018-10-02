//============================================================//
//*���@�O	Enemy.h
//*���@�e	�G
//*���@�t	2017.7.03
//*�X�@�V	2017.7.03
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "Object3D.h"
#include "..\..\Library\Collision\Sphere\SphereNode.h"
#include "..\..\Library\Collision\OBB�~Sphere\OBB2SphereCollision.h"

class Enemy
{
private:
	//	�߂荞�ݒ��˕Ԃ�l
	static const float REBOUND;
	//	�ړ��\�ő�l
	static const float MOVE_MAX;
	//	�ړ��\�ŏ��l
	static const float MOVE_MIN;
	//	�d�͒l
	static const DirectX::SimpleMath::Vector3 GRAVITY;
	//	�����l
	static const float DAMPIND;
	//	����
	static const float HALF;

public:
	Enemy();
	~Enemy();

	//	������
	void Initialize();
	//	�X�V
	void Update(const SphereNode& sphereNode);
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
	//	���x�̎擾
	const DirectX::SimpleMath::Vector3& GetSpeed() { return m_speed; }
	//	�G�̓����蔻��擾
	const SphereNode& GetCollisionNode() { return m_collisionNode; }
	//	�͈͕��̗���
	float GetRandomRange(float min, float max);
	//	�G��OBB�������������ǂ���
	bool IsOBBCollision(OBBNode& obb);

	//	�o�E���h����
	void Bound(OBBNode& obb);
	//	�d�͂�������
	void Gravity();

	//	�n��(OBB)�Ƃ̂߂荞�ݕ��߂�
	//void SinkRestore(OBBNode& obb);

	////	��������
	//void Escape(DirectX::SimpleMath::Vector3 targetPos);
	////	�ǐՂ���
	//void Chase(DirectX::SimpleMath::Vector3 targetPos);

	////�ړ��\�͈͓��ł̈ړ�
	//float MovePossibleRange(float pos);

private:
	//	�G�@
	Object3D m_model;
	//	���x
	DirectX::SimpleMath::Vector3 m_speed;
	//	�G�̓����蔻��
	SphereNode m_collisionNode;

	//	����
	float m_time;
	//	�o�E���h�؂�ւ�
	bool m_bound;

};
