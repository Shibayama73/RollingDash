//============================================================//
//*���@�O	OBBCollision.h
//*���@�e	OBB���m�̓����蔻��
//*���@�t	2017.11.13
//*�X�@�V	2017.11.13
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <simplemath.h>
#include "..\OBB\OBBNode.h"

class OBBCollision
{
public:
	//	OBB���m�̓��e�����̏Փ˔���
	bool IsOBB2OBBProjectionDistance(OBBNode& obb1, OBBNode& obb2, DirectX::SimpleMath::Vector3 axis, DirectX::SimpleMath::Vector3 distance);
	//	���S�Ԃ̋����̎Z�o
	DirectX::SimpleMath::Vector3 GetCalcCenter2CenterDistanceP(DirectX::SimpleMath::Vector3 centerA, DirectX::SimpleMath::Vector3 centerB);
	//	OBB���m�̓����蔻��
	bool IsOBB2OBBCollision(OBBNode& obb1, OBBNode& obb2);

};
