//============================================================//
//*¼@O	OBB.cpp
//*à@e	OBBîñ
//*ú@t	2017.10.23
//*X@V	2018.7.20
//*§ìÒ	N.Shibayama
//============================================================//
#include "..\..\..\Library\Framework\pch.h"
#include "OBB.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

OBB::OBB()
{
	m_radius = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
}

//	e£ÌZo
float OBB::GetCalcProjectionDistance(Vector3 Crossproduct)
{
	//	ª£²ãÅÅà¢¸_ÜÅÌ£
	float len = fabsf(m_separationAxisX.Dot(Crossproduct)*m_radius.x)
		+ fabsf(m_separationAxisY.Dot(Crossproduct)*m_radius.y)
		+ fabsf(m_separationAxisZ.Dot(Crossproduct)*m_radius.z);

	return len;
}
