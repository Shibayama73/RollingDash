//============================================================//
//*名　前	OBB2SphereCollision.h
//*内　容	OBBと球体の当たり判定
//*日　付	2017.11.22
//*更　新	2017.11.22
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <simplemath.h>
#include "..\OBB\OBBNode.h"
#include "..\Sphere\SphereNode.h"

class OBB2SphereCollision
{
public:
	//	OBBと球体の当たり判定
	bool IsOBB2SphereCollision(OBBNode& obb, SphereNode& sphere);
	//	OBBと点の最短距離算出
	float GetCalOBB2CenterDistance(OBBNode& obb, SphereNode& sphere);
	//	ベクトルの長さ算出
	float CalVec3Length(DirectX::SimpleMath::Vector3* vec);

	//	OBBと点の最短距離ベクトル算出
	DirectX::SimpleMath::Vector3 GetCalDistance(OBBNode& obb, SphereNode& sphere);

};
