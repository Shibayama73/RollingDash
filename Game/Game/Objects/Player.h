//============================================================//
//*名　前	Player.h
//*内　容	プレイヤー
//*日　付	2018.5.22
//*更　新	2018.7.23
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "Object3D.h"
#include <keyboard.h>
#include "..\..\Library\Collision\Sphere\SphereNode.h"
#include "..\..\Library\Keyboards\Keyboards.h"
#include "..\..\Library\Collision\OBB2Sphere\OBB2SphereCollision.h"
#include "..\..\Game\Objects\CubeStage.h"
#include "..\..\Game\Objects\Shield.h"

class Player
{
private:
	//	前進する値
	const float FORWARD_Z = 0.4f;
	//	後退する値
	const float BACKWARD_Z = 0.3f;
	//	左旋回する値
	const float LEFTTURN_Y = 0.05f;
	//	右旋回する値
	const float RIGHTTURN_Y = 0.05f;
	//	めり込み跳ね返り値
	const float REBOUND = 0.1f;
	//	重力値
	const DirectX::SimpleMath::Vector3 GRAVITY = DirectX::SimpleMath::Vector3(0.0f, -0.098f, 0.0f);

	//	ステージ領域を超えた限界地
	const float AREA_OVER_Y = -25.0f;

public:
	//	初期化
	void Initialize();
	//	更新
	void Update();
	//	描画
	void Draw();

	//	平行移動の設定
	void SetTranslation(DirectX::SimpleMath::Vector3 trans) { m_model.SetTranslation(trans); }
	//	回転角の設定
	void SetRotation(DirectX::SimpleMath::Vector3 angle) { m_model.SetRotation(angle); }
	//	平行移動の取得
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_model.GetTranslation(); }
	//	回転角の取得
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_model.GetRotation(); }
	//	自機の当たり判定取得
	const SphereNode& GetCollisionNode() { return m_collisionNode; }
	//	自機とOBBが当たったかどうか
	bool IsOBBCollision(OBBNode& obb);

	//	前進
	void Forward();
	//	後退
	void Backward();
	//	左旋回
	void LeftTurn();
	//	右旋回
	void RightTurn();

	//	OBBオブジェクトと衝突していたらめり込み戻しをする
	void ObbColSinkRestore(OBBNode& obb);
	//	ステージと衝突していたらめり込み戻しをする
	void StageColSinkRestore(CubeStage& obb);
	//	地面(OBB)とのめり込み分戻す
	void SinkRestore(OBBNode& obb);
	//	シールドと衝突していたらめり込み戻しをする
	void ShieldColSinkRestore(OBBNode& obb);
	//	シールドとのめり込み分戻す
	void ShieldSinkRestore(OBBNode& obb);
	//	重力をかける
	void Gravity();
	//	ゲームオーバーエリアを越えるかどうか
	bool IsAreaOver(OBBNode& obb);
	//	操作を使用停止する
	void StopControl();

private:
	//	自機
	Object3D m_model;
	//	自機の当たり判定
	SphereNode m_collisionNode;

	//	当たっているかどうか
	bool m_isCollision;

};
