//============================================================//
//*���@�O	World.h
//*���@�e	�w�i���E
//*���@�t	2018.4.10
//*�X�@�V	2018.4.10
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "Object3D.h"
#include "..\..\Library\Collision\Sphere\SphereNode.h"

class World
{
private:

public:
	//	������
	void Initialize();
	//	�X�V
	void Update();
	//	�`��
	void Draw();

	//	���s�ړ�
	void SetTranslation(DirectX::SimpleMath::Vector3 trans) { m_model.SetTranslation(trans); }
	//	��]�p
	void SetRotation(DirectX::SimpleMath::Vector3 angle) { m_model.SetRotation(angle); }

	//	���s�ړ�(XYZ)
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_model.GetTranslation(); }
	//	��]�p(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_model.GetRotation(); }


private:
	Object3D m_model;

	//	�G�̈ړ����W
	DirectX::SimpleMath::Vector3 m_headPos;
	//	�G�̃��[���h�s��
	DirectX::SimpleMath::Matrix m_worldHead;

};
