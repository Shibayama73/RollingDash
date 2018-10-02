//============================================================//
//*名　前	OBBCollision.cpp
//*内　容	OBB同士の当たり判定
//*日　付	2017.11.13
//*更　新	2017.11.13
//*制作者	N.Shibayama
//============================================================//
#include "..\..\..\Library\Framework\pch.h"
#include "OBBCollision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	OBB同士の投影距離の衝突判定
bool OBBCollision::IsOBB2OBBProjectionDistance(OBBNode & obb1, OBBNode & obb2, DirectX::SimpleMath::Vector3 axis, DirectX::SimpleMath::Vector3 distance)
{
	float length = fabsf(axis.Dot(distance));

	float len1 = obb1.GetCalcProjectionDistance(axis);
	float len2 = obb2.GetCalcProjectionDistance(axis);

	if (length > len1 + len2) return false;

	return true;
}

//	中心間の距離の算出
DirectX::SimpleMath::Vector3 OBBCollision::GetCalcCenter2CenterDistanceP(DirectX::SimpleMath::Vector3 centerA, DirectX::SimpleMath::Vector3 centerB)
{
	return centerA - centerB;
}

//	OBB同士の当たり判定
bool OBBCollision::IsOBB2OBBCollision(OBBNode & obb1, OBBNode & obb2)
{
	//	差分ベクトル
	Vector3 subtract = GetCalcCenter2CenterDistanceP(obb1.GetLocalCenter(), obb2.GetLocalCenter());

	//	分離軸の比較
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb1.GetLocalSeparationAxisX(), subtract))return false;
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb1.GetLocalSeparationAxisY(), subtract))return false;
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb1.GetLocalSeparationAxisZ(), subtract))return false;
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb2.GetLocalSeparationAxisX(), subtract))return false;
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb2.GetLocalSeparationAxisY(), subtract))return false;
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb2.GetLocalSeparationAxisZ(), subtract))return false;

	//	分離軸同士の外積の比較
	Vector3 crossProduct;
	crossProduct = obb1.GetLocalSeparationAxisX().Cross(obb2.GetLocalSeparationAxisX());
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, crossProduct, subtract))return false;
	crossProduct = obb1.GetLocalSeparationAxisX().Cross(obb2.GetLocalSeparationAxisY());
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, crossProduct, subtract))return false;
	crossProduct = obb1.GetLocalSeparationAxisX().Cross(obb2.GetLocalSeparationAxisZ());
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, crossProduct, subtract))return false;

	crossProduct = obb1.GetLocalSeparationAxisY().Cross(obb2.GetLocalSeparationAxisX());
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, crossProduct, subtract))return false;
	crossProduct = obb1.GetLocalSeparationAxisY().Cross(obb2.GetLocalSeparationAxisY());
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, crossProduct, subtract))return false;
	crossProduct = obb1.GetLocalSeparationAxisY().Cross(obb2.GetLocalSeparationAxisZ());
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, crossProduct, subtract))return false;

	crossProduct = obb1.GetLocalSeparationAxisZ().Cross(obb2.GetLocalSeparationAxisX());
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, crossProduct, subtract))return false;
	crossProduct = obb1.GetLocalSeparationAxisZ().Cross(obb2.GetLocalSeparationAxisY());
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, crossProduct, subtract))return false;
	crossProduct = obb1.GetLocalSeparationAxisZ().Cross(obb2.GetLocalSeparationAxisZ());
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, crossProduct, subtract))return false;

	return true;
}
