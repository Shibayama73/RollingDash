//============================================================//
//*名　前	Enemy.h
//*内　容	敵
//*日　付	2017.7.03
//*更　新	2017.7.03
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "Object3D.h"
#include "..\..\Library\Collision\Sphere\SphereNode.h"
#include "..\..\Library\Collision\OBB×Sphere\OBB2SphereCollision.h"

class Enemy
{
private:
	//	めり込み跳ね返り値
	static const float REBOUND;
	//	移動可能最大値
	static const float MOVE_MAX;
	//	移動可能最小値
	static const float MOVE_MIN;
	//	重力値
	static const DirectX::SimpleMath::Vector3 GRAVITY;
	//	減衰値
	static const float DAMPIND;
	//	半分
	static const float HALF;

public:
	Enemy();
	~Enemy();

	//	初期化
	void Initialize();
	//	更新
	void Update(const SphereNode& sphereNode);
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
	//	速度の取得
	const DirectX::SimpleMath::Vector3& GetSpeed() { return m_speed; }
	//	敵の当たり判定取得
	const SphereNode& GetCollisionNode() { return m_collisionNode; }
	//	範囲分の乱数
	float GetRandomRange(float min, float max);
	//	敵とOBBが当たったかどうか
	bool IsOBBCollision(OBBNode& obb);

	//	バウンドする
	void Bound(OBBNode& obb);
	//	重力をかける
	void Gravity();

	//	地面(OBB)とのめり込み分戻す
	//void SinkRestore(OBBNode& obb);

	////	逃走する
	//void Escape(DirectX::SimpleMath::Vector3 targetPos);
	////	追跡する
	//void Chase(DirectX::SimpleMath::Vector3 targetPos);

	////移動可能範囲内での移動
	//float MovePossibleRange(float pos);

private:
	//	敵機
	Object3D m_model;
	//	速度
	DirectX::SimpleMath::Vector3 m_speed;
	//	敵の当たり判定
	SphereNode m_collisionNode;

	//	時間
	float m_time;
	//	バウンド切り替え
	bool m_bound;

};
