//============================================================//
//*名　前	Enemy.cpp
//*内　容	敵
//*日　付	2017.7.03
//*更　新	2017.7.03
//*制作者	N.Shibayama
//============================================================//
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

//	めり込み跳ね返り値
const float Enemy::REBOUND = 0.01f;
//	移動可能最大値
const float Enemy::MOVE_MAX = 25.0f;
//	移動可能最小値
const float Enemy::MOVE_MIN = -25.0f;
//	重力値
const Vector3 Enemy::GRAVITY = Vector3(0.0f, 0.0098f, 0.0f);
//	減衰値
const float Enemy::DAMPIND = 0.95f;
//	半分
//const float Enemy::HALF = 0.5f;
const float Enemy::HALF = 0.75f;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	//	初期座標
	Vector3 pos = Vector3(GetRandomRange(-20.0f, 20.0f), 30.0f, GetRandomRange(-20.0f, 20.0f));

	//	モデルの初期化
	this->m_model.LoadModel(L"Resources/sphereE.cmo");
	this->m_model.SetTranslation(pos);
	this->m_model.SetScale(Vector3(1, 1, 1));
	this->m_model.SetRotation(Vector3(0, 0, 0));

	//	敵の当たり判定初期化
	this->m_collisionNode.Initialize();
	this->m_collisionNode.SetParent(&m_model);
	this->m_collisionNode.SetLocalRadius(1.2f);

	//	初期化
	m_time = 0;
	m_speed = Vector3(0.0f, 0.0f, 0.0f);
	m_bound = true;

}

void Enemy::Update(const SphereNode& sphereNode)
{
	//	自機オブジェクトの更新
	this->m_model.Update();
	//	敵の当たり判定ノード
	this->m_collisionNode.Update();

	//	バウンドする
	//this->Bound(obb);

	////	地面と当たっているとき
	//OBB2SphereCollision obb2sphereCollition;
	//if (obb2sphereCollition.IsOBB2SphereCollision(obb, m_collisionNode))
	//{
	//	//	バウンドする
	//	this->SinkRestore(obb);
	//}

	//	重力をかける
	//this->Gravity();

	//	プレイヤーと衝突したとき
	SphereCollision sphereCollision;
	if (sphereCollision.CheckSphere2Sphere(m_collisionNode, sphereNode))
	{
		this->Initialize();
	}

	////	プレイヤーがハートを持っていたら
	//if (playerHaveHeart)
	//{
	//	//	逃走する
	//	this->Escape(playerPos);
	//}
	//else
	//{
	//	//	追跡する
	//	this->Chase(playerPos);
	//}

}

void Enemy::Draw()
{
	m_model.Draw();

	//	敵の当たり判定ノード
	//this->m_collisionNode.Draw();
}

//	範囲分の乱数
float Enemy::GetRandomRange(float min, float max)
{
	float random = (float)rand() / RAND_MAX;
	random = min + (max - min)*random;
	return random;
}

//	敵とOBBが当たったかどうか
bool Enemy::IsOBBCollision(OBBNode & obb)
{
	//	立方体と敵との当たり判定
	OBB2SphereCollision obb2sphereCollition;
	if (obb2sphereCollition.IsOBB2SphereCollision(obb, m_collisionNode)) return true;
	return false;
}

////	バウンドする
//void Enemy::Bound(OBBNode & obb)
//{
//	m_speed -= GRAVITY;
//	Vector3 pos = m_model.GetTranslation();
//
//	//	地面と当たっているとき
//	OBB2SphereCollision obb2sphereCollition;
//	if (obb2sphereCollition.IsOBB2SphereCollision(obb, m_collisionNode))
//	{
//		//	めり込んだ長さ分押し上げる
//		Vector3 length = obb2sphereCollition.GetCalDistance(obb, m_collisionNode);
//		//pos.y += length.y;
//		pos += length;
//
//		//	速度を減衰する
//		//m_speed.y = (-m_speed.y * DAMPIND) * HALF;
//		m_speed = (-m_speed * DAMPIND) * HALF;
//	}
//	pos += m_speed;
//
//	m_model.SetTranslation(pos);
//	//m_position += pos;
//
//}

//	バウンドする
void Enemy::Bound(OBBNode & obb)
{
	//	敵とOBBが衝突したら
	if (this->IsOBBCollision(obb))
	{
		//	めり込んだ長さ
		OBB2SphereCollision obb2sphereCollition;
		Vector3 length = obb2sphereCollition.GetCalDistance(obb, m_collisionNode);
		length *= 2.0f;

		//	跳ね返りが完了するまで
		if (m_speed.y < -0.5f && m_bound == true)
			//	速度を反転させる
			m_speed.y = (-m_speed.y * DAMPIND) * HALF;
		else
			m_bound = false;

		//	移動させる
		Vector3 pos = m_model.GetTranslation();
		m_model.SetTranslation(pos + length);
		//m_position += length;
	}

}

//	重力をかける
void Enemy::Gravity()
{
	m_speed -= GRAVITY;

	//	回転
	//float angle = m_model.GetRotation().y;
	//Matrix rotmat = Matrix::CreateRotationY(angle);
	//	移動ベクトルを自機の角度分回転させる
	//Vector3 move = Vector3::TransformNormal(GRAVITY, rotmat);
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + m_speed);
	//m_position += move;

}

////	逃走する
//void Enemy::Escape(DirectX::SimpleMath::Vector3 targetPos)
//{
//	//	移動ベクトル
//	Vector3 moveV(-1.5f, -1.5f, -1.5f);
//	//	プレイヤーとの距離
//	Vector3 distance = targetPos - m_position;
//	distance.Normalize();
//	//	逃走する座標の計算
//	m_position += distance * moveV * m_time;
//
//	//	移動可能範囲内で移動
//	m_position.x = this->MovePossibleRange(m_position.x);
//	m_position.z = this->MovePossibleRange(m_position.z);
//
//	m_model.SetTranslation(m_position);
//	m_time += 0.0003f;
//
//}
//
////	追跡する
//void Enemy::Chase(DirectX::SimpleMath::Vector3 targetPos)
//{
//	//	移動ベクトル
//	Vector3 moveV(1.5f, 1.5f, 1.5f);
//	//	プレイヤーとの距離
//	Vector3 distance = targetPos - m_position;
//	distance.Normalize();
//	//	追跡する座標の計算
//	m_position += distance * moveV * m_time;
//
//	//	移動可能範囲内で移動
//	m_position.x = this->MovePossibleRange(m_position.x);
//	m_position.z = this->MovePossibleRange(m_position.z);
//
//	m_model.SetTranslation(m_position);
//	m_time += 0.00001f;
//}
//
////移動可能範囲内での移動
//float Enemy::MovePossibleRange(float pos)
//{
//	float position = pos;
//	if (position < MOVE_MIN)
//	{
//		position = MOVE_MIN;
//	}
//	else if (position > MOVE_MAX)
//	{
//		position = MOVE_MAX;
//	}
//	return position;
//}
