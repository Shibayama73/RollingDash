//============================================================//
//*���@�O	CollisionNode.cpp
//*���@�e	�������蔻��m�[�h
//*���@�t	2017.9.20
//*�X�@�V	2018.5.10
//*�����	N.Shibayama
//============================================================//
#include "CollisionNode.h"

//	�����o�ϐ��̎���
bool CollisionNode::m_debugVisible = true;

void CollisionNode::SetParent(Object3D * parent)
{
	m_object.SetObjParent(parent);
}
