//============================================================//
//*���@�O	Cube.h
//*���@�e	������
//*���@�t	2017.5.29
//*�X�@�V	2017.5.29
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "..\..\Library\Collision\OBB\OBB.h"
#include "..\..\Library\Collision\OBB\GroundNode.h"
#include "..\..\Library\Collision\OBB\OBBNode.h"
#include "..\..\Library\Collision\OBB2OBB\OBBCollision.h"

class Cube
{
public:
	Cube();
	~Cube();

	//	������
	void Initialize(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 scale, float angle);
	//	�X�V
	void Update(OBBNode& obb);
	//	�`��
	void Draw();

	//	��]������
	void StartRot();
	//	��]���~�߂�
	void StopRot();

	//	�����̓����蔻��
	OBBNode m_obbNode;

private:
	//	�����̃��f��
	Object3D m_model;
	//	��]�p�x
	float m_angle;
	//	��]�p�x�̒l
	float m_angleValue;
	//	��]�t���O
	bool m_isRot;
	//	����]
	bool m_isRotLeft;

};
