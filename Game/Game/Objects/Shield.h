//============================================================//
//*���@�O	Shield.h
//*���@�e	�V�[���h
//*���@�t	2018.5.22
//*�X�@�V	2018.5.22
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "..\..\Library\Collision\OBB\OBB.h"
#include "..\..\Library\Collision\OBB\GroundNode.h"
#include "..\..\Library\Collision\OBB\OBBNode.h"
#include "..\..\Library\Collision\OBB2OBB\OBBCollision.h"

class Shield
{
public:
	//	������
	void Initialize(DirectX::SimpleMath::Vector3 pos);
	//	�X�V
	void Update();
	//	�`��
	void Draw();

	//	�����̓����蔻��
	OBBNode m_obbNode;

private:
	//	�����̃��f��
	Object3D m_model;

};
