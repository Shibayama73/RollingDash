//============================================================//
//*���@�O	GroundNode.h
//*���@�e	OBB�e�q�֌W�\�z
//*���@�t	2017.10.23
//*�X�@�V	2018.7.20
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "..\..\..\Game\Objects\Object3D.h"

class GroundNode
{
public:
	//	������
	virtual void Initialize() = 0;
	//	�X�V
	virtual void Update() = 0;
	//	�`��
	virtual void Draw() = 0;

	//	�e�q�֌W�\�z
	void SetParent(Object3D* parent);

protected:
	//	�f�o�b�O�\���p�I�u�W�F�N�g
	Object3D m_model;

};
