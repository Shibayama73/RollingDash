//============================================================//
//*���@�O	GroundNode.cpp
//*���@�e	OBB�e�q�֌W�\�z
//*���@�t	2017.10.23
//*�X�@�V	2018.7.20
//*�����	N.Shibayama
//============================================================//
#include "GroundNode.h"

//	�e�q�֌W�\�z
void GroundNode::SetParent(Object3D* parent)
{
	m_model.SetObjParent(parent);
}
