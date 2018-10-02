//============================================================//
//*名　前	OBBCollision.h
//*内　容	OBB同士の当たり判定
//*日　付	2017.11.13
//*更　新	2017.11.13
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <simplemath.h>
#include "..\OBB\OBBNode.h"

class OBBCollision
{
public:
	//	OBB同士の投影距離の衝突判定
	bool IsOBB2OBBProjectionDistance(OBBNode& obb1, OBBNode& obb2, DirectX::SimpleMath::Vector3 axis, DirectX::SimpleMath::Vector3 distance);
	//	中心間の距離の算出
	DirectX::SimpleMath::Vector3 GetCalcCenter2CenterDistanceP(DirectX::SimpleMath::Vector3 centerA, DirectX::SimpleMath::Vector3 centerB);
	//	OBB同士の当たり判定
	bool IsOBB2OBBCollision(OBBNode& obb1, OBBNode& obb2);

};
