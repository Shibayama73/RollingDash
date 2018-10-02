//============================================================//
//*���@�O	CollisionNode.h
//*���@�e	�������蔻��m�[�h
//*���@�t	2017.9.20
//*�X�@�V	2018.5.10
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "..\..\..\Game\Objects\Object3D.h"

class CollisionNode
{
public:
	//	�f�o�b�O�\���t���O�擾
	static bool GetDebugVisible() { return m_debugVisible; }
	//	�f�o�b�O�\���t���O�Z�b�g
	static void SetDebugVisible(bool visible) { m_debugVisible = visible; }

protected:
	//	�f�o�b�O�t���O�\��ON
	static bool m_debugVisible;

public:
	//	������
	virtual void Initialize() = 0;
	//	�X�V
	virtual void Update() = 0;
	//	�`��
	virtual void Draw() = 0;

	//	�e�q�֌W�\�z
	void SetParent(Object3D* parent);
	//	�e����̃I�t�Z�b�g
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_trans = trans; }


protected:
	//	�f�o�b�O�\���p�I�u�W�F�N�g
	Object3D m_object;
	//	�e����̃I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_trans;

};
