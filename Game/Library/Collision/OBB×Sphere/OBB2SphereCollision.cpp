//============================================================//
//*名　前	OBB2SphereCollision.cpp
//*内　容	OBBと球体の当たり判定
//*日　付	2017.11.22
//*更　新	2017.12.04
//*制作者	N.Shibayama
//============================================================//
#include "..\..\..\Library\Framework\pch.h"
#include "OBB2SphereCollision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	OBBと球体の当たり判定
bool OBB2SphereCollision::IsOBB2SphereCollision(OBBNode & obb, SphereNode & sphere)
{
	//	OBBと点の最短距離算出
	float length = GetCalOBB2CenterDistance(obb, sphere);

	//	距離が球の半径より短いとき
	if (length < sphere.GetRadius()) return true;

	return false;
}

//	OBBと点の最短距離算出
float OBB2SphereCollision::GetCalOBB2CenterDistance(OBBNode & obb, SphereNode & sphere)
{
	//	はみ出したベクトル
	Vector3 vec(0, 0, 0);

	//	各軸のはみ出た分のベクトル算出
	for (int i = 0; i < 3; i++)
	{
		float length;
		//	OBBの半径取得
		if (i == 0) length = obb.GetRadius().x;
		if (i == 1) length = obb.GetRadius().y;
		if (i == 2) length = obb.GetRadius().z;

		//	0以下なら計算不要
		if (length <= 0) continue;

		//	2点の距離と分離軸の内積
		Vector3 distance = sphere.GetCenter() - obb.GetLocalCenter();
		Vector3 axis;
		if (i == 0) axis = obb.GetLocalSeparationAxisX();
		if (i == 1) axis = obb.GetLocalSeparationAxisY();
		if (i == 2) axis = obb.GetLocalSeparationAxisZ();
		//	はみ出し
		float protrude = (distance.x * axis.x + distance.y * axis.y + distance.z * axis.z) / length;

		//	はみ出た部分があるなら
		protrude = fabsf(protrude);
		if (protrude > 1)
		{
			//	はみ出た分の算出
			if (i == 0) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisX();
			if (i == 1) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisY();
			if (i == 2) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisZ();
		}
	}
	return CalVec3Length(&vec);
}

float OBB2SphereCollision::CalVec3Length(Vector3* vec)
{
	float x, y, z;
	float length;

	if (!vec) return 0.0f;

	x = (float)(vec->x);
	y = (float)(vec->y);
	z = (float)(vec->z);
	length = sqrt(x*x + y*y + z*z);

	return (float)(length);
}

DirectX::SimpleMath::Vector3 OBB2SphereCollision::GetCalDistance(OBBNode & obb, SphereNode & sphere)
{
	//	はみ出したベクトル
	Vector3 vec(0, 0, 0);

	//	各軸のはみ出た分のベクトル算出
	for (int i = 0; i < 3; i++)
	{
		float length;
		//	OBBの半径取得
		if (i == 0) length = obb.GetRadius().x;
		if (i == 1) length = obb.GetRadius().y;
		if (i == 2) length = obb.GetRadius().z;

		//	0以下なら計算不要
		if (length <= 0) continue;

		//	2点の距離
		Vector3 distance = sphere.GetCenter() - obb.GetLocalCenter();
		
		Vector3 axis;
		if (i == 0) axis = obb.GetLocalSeparationAxisX();
		if (i == 1) axis = obb.GetLocalSeparationAxisY();
		if (i == 2) axis = obb.GetLocalSeparationAxisZ();

		//	はみ出した部分の算出(距離と分離軸の内積)
		float protrude = (distance.x * axis.x + distance.y * axis.y + distance.z * axis.z) / length;

		//	はみ出た部分があるなら
		//protrude = fabsf(protrude);
		// 分離軸方向に押し出す
		if (protrude > 1)
		{
			//	はみ出た部分のベクトル算出
			if (i == 0) vec += ((1 - protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisX();
			if (i == 1) vec += ((1 - protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisY();
			if (i == 2) vec += ((1 - protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisZ();

			//if (i == 1)
			//{
			//	float A = 1 - protrude;
			//	A *= length;
			//	A += sphere.m_radius;
			//	Vector3 v = A * obb.GetLocalSeparationAxisY();
			//	vec += v;
			//}
		}
		// 分離軸の逆方向に押し出す
		if (protrude < -1)
		{
			//	はみ出た分の算出
			if (i == 0) vec -= ((1 + protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisX();
			if (i == 1) vec -= ((1 + protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisY();
			if (i == 2) vec -= ((1 + protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisZ();

			//if (i == 1)
			//{
			//	float A = 1 + protrude;
			//	A *= length;
			//	A += sphere.m_radius;
			//	Vector3 v = A * obb.GetLocalSeparationAxisY();
			//	vec -= v;
			//}
		}

		//if (protrude > 1)
		//{
		//	//	はみ出た部分のベクトル算出
		//	if (i == 0) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisX();
		//	if (i == 1) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisY();
		//	if (i == 2) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisZ();
		//}
		//if (protrude < -1)
		//{
		//	//	はみ出た分の算出
		//	if (i == 0) vec -= (1 + protrude) * length * obb.GetLocalSeparationAxisX();
		//	if (i == 1) vec -= (1 + protrude) * length * obb.GetLocalSeparationAxisY();
		//	if (i == 2) vec -= (1 + protrude) * length * obb.GetLocalSeparationAxisZ();
		//}

	}

	return vec;
}
