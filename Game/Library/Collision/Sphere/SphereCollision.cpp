//============================================================//
//*���@�O	SphereCollision.cpp
//*���@�e	�������蔻��
//*���@�t	2017.9.20
//*�X�@�V	2018.5.10
//*�����	N.Shibayama
//============================================================//
#include "SphereCollision.h"

using namespace DirectX::SimpleMath;

SphereCollision::SphereCollision()
{
	m_radius = 1.0f;
}

//	���Ƌ��������������ǂ���
bool SphereCollision::CheckSphere2Sphere(const SphereCollision & _sphereA, const SphereCollision & _sphereB)
{
	//	A����B�Ɍ������x�N�g��
	Vector3 sub = _sphereB.m_center - _sphereA.m_center;

	//	A��B�̋����̌v�Z
	//float distance = sqrtf(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);
	//	A��B�̋����̂Q��̌v�Z
	float distanceSqare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//	���a�̘a�̌v�Z
	//float radius = _sphereA.Radius + _sphereB.Radius;
	float radiusSquare = _sphereA.m_radius + _sphereB.m_radius;
	//	���a�̘a�̂Q��̌v�Z
	radiusSquare = radiusSquare * radiusSquare;

	//	���������a�̘a���傫���Ƃ�
	if (distanceSqare > radiusSquare) {
		//�������Ă��Ȃ�
		return false;
	}
	//	�������Ă���
	return true;
}
