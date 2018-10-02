//============================================================//
//*名　前	CollisionNode.cpp
//*内　容	球当たり判定ノード
//*日　付	2017.9.20
//*更　新	2018.5.10
//*制作者	N.Shibayama
//============================================================//
#include "CollisionNode.h"

//	メンバ変数の実態
bool CollisionNode::m_debugVisible = true;

void CollisionNode::SetParent(Object3D * parent)
{
	m_object.SetObjParent(parent);
}
