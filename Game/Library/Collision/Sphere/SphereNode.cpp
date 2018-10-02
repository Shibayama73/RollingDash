//============================================================//
//*名　前	SphereNode.cpp
//*内　容	球当たり判定ノード
//*日　付	2017.9.20
//*更　新	2018.5.10
//*制作者	N.Shibayama
//============================================================//
#include "SphereNode.h"
using namespace DirectX::SimpleMath;

SphereNode::SphereNode()
{
	//	半径の初期化(1m)
	m_localRadius = 1.0f;
}

void SphereNode::Initialize()
{
	//	デバッグ表示用モデル読込み
	m_object.LoadModel(L"Resources/sphereNode.cmo");
}

void SphereNode::Update()
{
	m_object.SetTranslation(m_trans);
	m_object.SetScale(Vector3(m_localRadius));

	m_object.Update();

	{//	判定球の要素を計算
		const Matrix worldm = m_object.GetWorld();

		//	モデル座標系での中心点
		Vector3 center(0, 0, 0);
		//	モデル座標系での右端の点
		Vector3 right(1, 0, 0);

		//	ワールド座標系に変換
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		//	判定球の要素を代入
		SphereCollision::m_center = center;
		SphereCollision::m_radius = Vector3::Distance(center, right);

	}

}

void SphereNode::Draw()
{
	m_object.Draw();
}
