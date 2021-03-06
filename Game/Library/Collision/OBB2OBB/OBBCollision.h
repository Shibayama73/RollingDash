//============================================================//
//*¼@O	OBBCollision.h
//*à@e	OBB¯mÌ½è»è
//*ú@t	2017.11.13
//*X@V	2017.11.13
//*§ìÒ	N.Shibayama
//============================================================//
#pragma once
#include <simplemath.h>
#include "..\OBB\OBBNode.h"

class OBBCollision
{
public:
	//	OBB¯mÌe£ÌÕË»è
	bool IsOBB2OBBProjectionDistance(OBBNode& obb1, OBBNode& obb2, DirectX::SimpleMath::Vector3 axis, DirectX::SimpleMath::Vector3 distance);
	//	SÔÌ£ÌZo
	DirectX::SimpleMath::Vector3 GetCalcCenter2CenterDistanceP(DirectX::SimpleMath::Vector3 centerA, DirectX::SimpleMath::Vector3 centerB);
	//	OBB¯mÌ½è»è
	bool IsOBB2OBBCollision(OBBNode& obb1, OBBNode& obb2);

};
