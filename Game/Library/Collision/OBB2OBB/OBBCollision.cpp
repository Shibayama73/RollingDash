//============================================================//
//*���@�O	OBBCollision.cpp
//*���@�e	OBB���m�̓����蔻��
//*���@�t	2017.11.13
//*�X�@�V	2017.11.13
//*�����	N.Shibayama
//============================================================//
#include "..\..\..\Library\Framework\pch.h"
#include "OBBCollision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	OBB���m�̓��e�����̏Փ˔���
bool OBBCollision::IsOBB2OBBProjectionDistance(OBBNode & obb1, OBBNode & obb2, DirectX::SimpleMath::Vector3 axis, DirectX::SimpleMath::Vector3 distance)
{
	float length = fabsf(axis.Dot(distance));

	float len1 = obb1.GetCalcProjectionDistance(axis);
	float len2 = obb2.GetCalcProjectionDistance(axis);

	if (length > len1 + len2) return false;

	return true;
}

//	���S�Ԃ̋����̎Z�o
DirectX::SimpleMath::Vector3 OBBCollision::GetCalcCenter2CenterDistanceP(DirectX::SimpleMath::Vector3 centerA, DirectX::SimpleMath::Vector3 centerB)
{
	return centerA - centerB;
}

//	OBB���m�̓����蔻��
bool OBBCollision::IsOBB2OBBCollision(OBBNode & obb1, OBBNode & obb2)
{
	//	�����x�N�g��
	Vector3 subtract = GetCalcCenter2CenterDistanceP(obb1.GetLocalCenter(), obb2.GetLocalCenter());

	//	�������̔�r
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb1.GetLocalSeparationAxisX(), subtract))return false;
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb1.GetLocalSeparationAxisY(), subtract))return false;
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb1.GetLocalSeparationAxisZ(), subtract))return false;
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb2.GetLocalSeparationAxisX(), subtract))return false;
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb2.GetLocalSeparationAxisY(), subtract))return false;
	if (!IsOBB2OBBProjectionDistance(obb1, obb2, obb2.GetLocalSeparationAxisZ(), subtract))return false;

	//	���������m�̊O�ς̔�r
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
