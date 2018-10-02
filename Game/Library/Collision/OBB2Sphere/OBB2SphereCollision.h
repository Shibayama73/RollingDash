//============================================================//
//*���@�O	OBB2SphereCollision.h
//*���@�e	OBB�Ƌ��̂̓����蔻��
//*���@�t	2017.11.22
//*�X�@�V	2017.11.22
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <simplemath.h>
#include "..\OBB\OBBNode.h"
#include "..\Sphere\SphereNode.h"

class OBB2SphereCollision
{
public:
	//	OBB�Ƌ��̂̓����蔻��
	bool IsOBB2SphereCollision(OBBNode& obb, SphereNode& sphere);
	//	OBB�Ɠ_�̍ŒZ�����Z�o
	float GetCalOBB2CenterDistance(OBBNode& obb, SphereNode& sphere);
	//	�x�N�g���̒����Z�o
	float CalVec3Length(DirectX::SimpleMath::Vector3* vec);

	//	OBB�Ɠ_�̍ŒZ�����x�N�g���Z�o
	DirectX::SimpleMath::Vector3 GetCalDistance(OBBNode& obb, SphereNode& sphere);

};
