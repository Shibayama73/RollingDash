//============================================================//
//*¼@O	OBB.h
//*à@e	OBBîñ
//*ú@t	2017.10.23
//*X@V	2018.7.20
//*§ìÒ	N.Shibayama
//============================================================//
#pragma once
#include <d3d11_1.h>
#include <simplemath.h>

class OBB
{
public:
	//	e£ÌZo
	float GetCalcProjectionDistance(DirectX::SimpleMath::Vector3 Crossproduct);

protected:
	OBB();
	//	SÀW
	DirectX::SimpleMath::Vector3 m_center;
	//	¼a
	DirectX::SimpleMath::Vector3 m_radius;
	//	ª£²
	DirectX::SimpleMath::Vector3 m_separationAxisX;
	DirectX::SimpleMath::Vector3 m_separationAxisY;
	DirectX::SimpleMath::Vector3 m_separationAxisZ;

};

