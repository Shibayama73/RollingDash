//============================================================//
//*名　前	SphereCollision.h
//*内　容	球当たり判定
//*日　付	2017.9.20
//*更　新	2018.5.10
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <d3d11_1.h>
#include <simplemath.h>

class SphereCollision
{
public:
	//	コンストラクタ(半径の設定)
	SphereCollision();
	//	球と球が当たったかどうか
	bool CheckSphere2Sphere(const SphereCollision& _sphereA, const SphereCollision& _sphereB);

protected:
	//	中心座標
	DirectX::SimpleMath::Vector3 m_center;
	//	半径
	float m_radius;

};
