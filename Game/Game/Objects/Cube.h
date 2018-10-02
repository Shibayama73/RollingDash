//============================================================//
//*名　前	Cube.h
//*内　容	立方体
//*日　付	2017.5.29
//*更　新	2017.5.29
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\..\Library\Collision\OBB\OBB.h"
#include "..\..\Library\Collision\OBB\GroundNode.h"
#include "..\..\Library\Collision\OBB\OBBNode.h"
#include "..\..\Library\Collision\OBB2OBB\OBBCollision.h"

class Cube
{
public:
	Cube();
	~Cube();

	//	初期化
	void Initialize(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 scale, float angle);
	//	更新
	void Update(OBBNode& obb);
	//	描画
	void Draw();

	//	回転させる
	void StartRot();
	//	回転を止める
	void StopRot();

	//	立方体当たり判定
	OBBNode m_obbNode;

private:
	//	立方体モデル
	Object3D m_model;
	//	回転角度
	float m_angle;
	//	回転角度の値
	float m_angleValue;
	//	回転フラグ
	bool m_isRot;
	//	左回転
	bool m_isRotLeft;

};
