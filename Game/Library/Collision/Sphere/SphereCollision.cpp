//============================================================//
//*–¼@‘O	SphereCollision.cpp
//*“à@—e	‹…“–‚½‚è”»’è
//*“ú@•t	2017.9.20
//*X@V	2018.5.10
//*§ìŽÒ	N.Shibayama
//============================================================//
#include "SphereCollision.h"

using namespace DirectX::SimpleMath;

SphereCollision::SphereCollision()
{
	m_radius = 1.0f;
}

//	‹…‚Æ‹…‚ª“–‚½‚Á‚½‚©‚Ç‚¤‚©
bool SphereCollision::CheckSphere2Sphere(const SphereCollision & _sphereA, const SphereCollision & _sphereB)
{
	//	A‚©‚çB‚ÉŒü‚©‚¤ƒxƒNƒgƒ‹
	Vector3 sub = _sphereB.m_center - _sphereA.m_center;

	//	A‚ÆB‚Ì‹——£‚ÌŒvŽZ
	//float distance = sqrtf(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);
	//	A‚ÆB‚Ì‹——£‚Ì‚Qæ‚ÌŒvŽZ
	float distanceSqare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//	”¼Œa‚Ì˜a‚ÌŒvŽZ
	//float radius = _sphereA.Radius + _sphereB.Radius;
	float radiusSquare = _sphereA.m_radius + _sphereB.m_radius;
	//	”¼Œa‚Ì˜a‚Ì‚Qæ‚ÌŒvŽZ
	radiusSquare = radiusSquare * radiusSquare;

	//	‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¢‚Æ‚«
	if (distanceSqare > radiusSquare) {
		//“–‚½‚Á‚Ä‚¢‚È‚¢
		return false;
	}
	//	“–‚½‚Á‚Ä‚¢‚é
	return true;
}
