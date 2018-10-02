//============================================================//
//*名　前	OBB.h
//*内　容	OBB情報
//*日　付	2017.10.23
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <d3d11_1.h>
#include <simplemath.h>

class OBB
{
public:
	//	投影距離の算出
	float GetCalcProjectionDistance(DirectX::SimpleMath::Vector3 Crossproduct);

protected:
	OBB();
	//	中心座標
	DirectX::SimpleMath::Vector3 m_center;
	//	半径
	DirectX::SimpleMath::Vector3 m_radius;
	//	分離軸
	DirectX::SimpleMath::Vector3 m_separationAxisX;
	DirectX::SimpleMath::Vector3 m_separationAxisY;
	DirectX::SimpleMath::Vector3 m_separationAxisZ;

};

