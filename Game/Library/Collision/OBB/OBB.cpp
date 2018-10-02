//============================================================//
//*名　前	OBB.cpp
//*内　容	OBB情報
//*日　付	2017.10.23
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#include "..\..\..\Library\Framework\pch.h"
#include "OBB.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

OBB::OBB()
{
	m_radius = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
}

//	投影距離の算出
float OBB::GetCalcProjectionDistance(Vector3 Crossproduct)
{
	//	分離軸上で最も遠い頂点までの距離
	float len = fabsf(m_separationAxisX.Dot(Crossproduct)*m_radius.x)
		+ fabsf(m_separationAxisY.Dot(Crossproduct)*m_radius.y)
		+ fabsf(m_separationAxisZ.Dot(Crossproduct)*m_radius.z);

	return len;
}
