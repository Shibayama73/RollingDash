//============================================================//
//*名　前	GroundNode.cpp
//*内　容	OBB親子関係構築
//*日　付	2017.10.23
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#include "GroundNode.h"

//	親子関係構築
void GroundNode::SetParent(Object3D* parent)
{
	m_model.SetObjParent(parent);
}
