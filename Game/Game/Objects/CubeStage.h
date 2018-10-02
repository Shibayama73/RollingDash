//============================================================//
//*名　前	CubeStage.h
//*内　容	立方体のステージ
//*日　付	2018.6.27
//*更　新	2018.6.27
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\..\Library\Collision\OBB\OBB.h"
#include "..\..\Library\Collision\OBB\GroundNode.h"
#include "..\..\Library\Collision\OBB\OBBNode.h"
#include "..\..\Library\Collision\OBB×OBB\OBBCollision.h"

class CubeStage
{
private:
	//	回転値
	static const float ROTATE;
	//	半径値
	static const float RADIUS;

public:
	CubeStage();
	~CubeStage();

	//	初期化
	void Initialize(DirectX::SimpleMath::Vector3 pos,DirectX::SimpleMath::Vector3 sca);
	//	更新
	void Update();
	//	描画
	void Draw();
	//	衝突したことを伝える
	void OnCollision();

	//	衝突しているかどうか
	bool IsCollision() { return m_isCollision; }

	//	座標取得
	DirectX::SimpleMath::Vector3 GetTranslation() { return m_model.GetTranslation(); }
	//	角度取得(ラジアン)
	DirectX::SimpleMath::Vector3 GetRotation() { return m_model.GetRotation(); }

	//	左回転
	void LeftRot() { m_isRot = false; }
	//	右回転
	void RightRot() { m_isRot = true; }

	//	立方体当たり判定
	OBBNode m_obbNode;

private:
	//	立方体モデル
	Object3D m_model;
	//	回転角度
	float m_rotation;
	//	回転方向フラグ
	bool m_isRot;
	//	衝突フラグ
	bool m_isCollision;

};
