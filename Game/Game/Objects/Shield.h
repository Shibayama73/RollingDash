//============================================================//
//*名　前	Shield.h
//*内　容	シールド
//*日　付	2018.5.22
//*更　新	2018.5.22
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\..\Library\Collision\OBB\OBB.h"
#include "..\..\Library\Collision\OBB\GroundNode.h"
#include "..\..\Library\Collision\OBB\OBBNode.h"
#include "..\..\Library\Collision\OBB2OBB\OBBCollision.h"

class Shield
{
public:
	//	初期化
	void Initialize(DirectX::SimpleMath::Vector3 pos);
	//	更新
	void Update();
	//	描画
	void Draw();

	//	立方体当たり判定
	OBBNode m_obbNode;

private:
	//	立方体モデル
	Object3D m_model;

};
