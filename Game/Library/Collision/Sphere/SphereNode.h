//============================================================//
//*名　前	SphereNode.h
//*内　容	球当たり判定ノード
//*日　付	2017.9.20
//*更　新	2018.5.10
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "SphereCollision.h"
#include "CollisionNode.h"

class SphereNode :public CollisionNode, public SphereCollision
{
public:
	SphereNode();
	//	初期化
	void Initialize();
	//	更新
	void Update();
	//	描画
	void Draw();

	//	ローカル半径のセット
	void SetLocalRadius(float radius) { m_localRadius = radius; }
	//	原点の取得
	DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
	//	半径の取得
	float GetRadius() { return m_radius; }

protected:
	//	ローカル半径
	float m_localRadius;

};
