//============================================================//
//*名　前	World.h
//*内　容	背景世界
//*日　付	2018.4.10
//*更　新	2018.4.10
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "Object3D.h"
#include "..\..\Library\Collision\Sphere\SphereNode.h"

class World
{
private:

public:
	//	初期化
	void Initialize();
	//	更新
	void Update();
	//	描画
	void Draw();

	//	平行移動
	void SetTranslation(DirectX::SimpleMath::Vector3 trans) { m_model.SetTranslation(trans); }
	//	回転角
	void SetRotation(DirectX::SimpleMath::Vector3 angle) { m_model.SetRotation(angle); }

	//	平行移動(XYZ)
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_model.GetTranslation(); }
	//	回転角(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_model.GetRotation(); }


private:
	Object3D m_model;

	//	敵の移動座標
	DirectX::SimpleMath::Vector3 m_headPos;
	//	敵のワールド行列
	DirectX::SimpleMath::Matrix m_worldHead;

};
