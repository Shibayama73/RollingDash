//============================================================//
//*名　前	SphereCollision.cpp
//*内　容	球当たり判定
//*日　付	2017.9.20
//*更　新	2018.5.10
//*制作者	N.Shibayama
//============================================================//
#include "SphereCollision.h"

using namespace DirectX::SimpleMath;

SphereCollision::SphereCollision()
{
	m_radius = 1.0f;
}

//	球と球が当たったかどうか
bool SphereCollision::CheckSphere2Sphere(const SphereCollision & _sphereA, const SphereCollision & _sphereB)
{
	//	AからBに向かうベクトル
	Vector3 sub = _sphereB.m_center - _sphereA.m_center;

	//	AとBの距離の計算
	//float distance = sqrtf(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);
	//	AとBの距離の２乗の計算
	float distanceSqare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//	半径の和の計算
	//float radius = _sphereA.Radius + _sphereB.Radius;
	float radiusSquare = _sphereA.m_radius + _sphereB.m_radius;
	//	半径の和の２乗の計算
	radiusSquare = radiusSquare * radiusSquare;

	//	距離が半径の和より大きいとき
	if (distanceSqare > radiusSquare) {
		//当たっていない
		return false;
	}
	//	当たっている
	return true;
}
