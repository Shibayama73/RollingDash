//============================================================//
//*名　前	Heart.h
//*内　容	ゴールのハート
//*日　付	2017.5.21
//*更　新	2017.5.21
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "Object3D.h"
#include "..\..\Library\Collision\Sphere\SphereNode.h"

class Heart
{
public:
	//	初期化
	void Initialize();
	//	更新
	void Update();
	//	描画
	void Draw();

	//	座標取得
	DirectX::SimpleMath::Vector3 GetTranslation() { return m_model.GetTranslation(); }
	//	座標変更
	void ChangePos(DirectX::SimpleMath::Vector3 pos);

private:
	Object3D m_model;

	//	回転
	DirectX::SimpleMath::Vector3 m_rotation;

};
