//============================================================//
//*名　前	Player.cpp
//*内　容	プレイヤー
//*日　付	2018.5.22
//*更　新	2018.7.23
//*制作者	N.Shibayama
//============================================================//
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void Player::Initialize()
{
	//	自機モデルの初期化
	this->m_model.LoadModel(L"Resources/sphereP.cmo");
	this->m_model.SetTranslation(Vector3(0.0f, 5.0f, 0.0f));
	this->m_model.SetScale(Vector3(1, 1, 1));
	this->m_model.SetRotation(Vector3(0, 0, 0));

	//	自機の当たり判定初期化
	this->m_collisionNode.Initialize();
	this->m_collisionNode.SetParent(&m_model);
	this->m_collisionNode.SetLocalRadius(1.2f);

	m_isCollision = false;

}

void Player::Update()
{
	//	キーボード取得
	auto& key = Keyboards::GetInstance();
	key.GetState();

	//	自機
	this->m_model.Update();
	//	自機の当たり判定ノード
	this->m_collisionNode.Update();

	//	重力をかける
	this->Gravity();

	if(m_isCollision)
	{
		//	Wキーが押されてるとき前進
		if (key.CheckKey("W"))
		{
			this->Forward();
		}
		//	Sキーが押されてるとき後退
		if (key.CheckKey("S"))
		{
			this->Backward();
		}
		//	Aキーが押されてるとき左旋回
		if (key.CheckKey("A"))
		{
			this->LeftTurn();
		}
		//	Dキーが押されてるとき右旋回
		if (key.CheckKey("D"))
		{
			this->RightTurn();
		}
	}

#ifdef _DEBUG
	//	デバッグ用(Y)
	//{
	//	if (key.CheckKey("X"))
	//	{
	//		//	移動ベクトル(Z座標前進)
	//		Vector3 moveV(0, -REBOUND, 0);
	//		//	回転
	//		float angle = m_model.GetRotation().y;
	//		Matrix rotmat = Matrix::CreateRotationY(angle);
	//		//	移動ベクトルを自機の角度分回転させる
	//		moveV = Vector3::TransformNormal(moveV, rotmat);
	//		Vector3 pos = m_model.GetTranslation();
	//		m_model.SetTranslation(pos + moveV);

	//	}
	//	if (key.CheckKey("Z"))
	//	{
	//		//	移動ベクトル(Z座標前進)
	//		Vector3 moveV(0, REBOUND, 0);
	//		//	回転
	//		float angle = m_model.GetRotation().y;
	//		Matrix rotmat = Matrix::CreateRotationY(angle);
	//		//	移動ベクトルを自機の角度分回転させる
	//		moveV = Vector3::TransformNormal(moveV, rotmat);
	//		Vector3 pos = m_model.GetTranslation();
	//		m_model.SetTranslation(pos + moveV);

	//	}
	//}
#endif

}

void Player::Draw()
{
	//	自機の描画
	this->m_model.Draw();
	//	自機の当たり判定ノードモデルの表示
	//this->m_collisionNode.Draw();

}

//	自機とOBBが当たったかどうか
bool Player::IsOBBCollision(OBBNode & obb)
{
	//	OBBと自機との当たり判定
	OBB2SphereCollision obb2sphereCollition;
	//	OBBと当たっているとき
	if (obb2sphereCollition.IsOBB2SphereCollision(obb, m_collisionNode)) return true;
	return false;
}

//	前進
void Player::Forward()
{
	//	移動ベクトル(Z座標前進)
	Vector3 moveV(0, 0, -FORWARD_Z);
	//	回転
	Vector3 angle = m_model.GetRotation();
	angle.x -= 0.1f;
	m_model.SetRotation(angle);
	Matrix rotmat = Matrix::CreateRotationY(angle.y);
	//	移動ベクトルを自機の角度分回転させる
	moveV = Vector3::TransformNormal(moveV, rotmat);
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + moveV);

}

//	後退
void Player::Backward()
{
	//	移動ベクトル(Z座標後退)
	Vector3 moveV(0, 0, BACKWARD_Z);
	//	回転
	Vector3 angle = m_model.GetRotation();
	angle.x += 0.1f;
	m_model.SetRotation(angle);
	Matrix rotmat = Matrix::CreateRotationY(angle.y);
	//	移動ベクトルを自機の角度分回転させる
	moveV = Vector3::TransformNormal(moveV, rotmat);
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + moveV);

}

//	左旋回
void Player::LeftTurn()
{
	//	左に旋回する
	Vector3 angle = m_model.GetRotation();
	angle.y += LEFTTURN_Y;
	m_model.SetRotation(angle);
}

//	右旋回
void Player::RightTurn()
{
	//	右に旋回する
	Vector3 angle = m_model.GetRotation();
	angle.y -= LEFTTURN_Y;
	m_model.SetRotation(angle);
}

//	OBBオブジェクトと衝突していたらめり込み戻しをする
void Player::ObbColSinkRestore(OBBNode & obb)
{
	//	地面と当たっているとき
	if (this->IsOBBCollision(obb))
	{
		//	めり込み戻し
		this->SinkRestore(obb);
	}
}

//	ステージと衝突していたらめり込み戻しをする
void Player::StageColSinkRestore(CubeStage & stage)
{
	//	地面と当たっているとき
	if (this->IsOBBCollision(stage.m_obbNode))
	{
		m_isCollision = true;

		//	めり込み戻し
		this->SinkRestore(stage.m_obbNode);
	}
	else m_isCollision = false;
}

//	地面(OBB)とのめり込み分戻す
void Player::SinkRestore(OBBNode& obb)
{
	//	立方体と敵との当たり判定
	OBB2SphereCollision obb2sphereCollition;
	//	めり込んだ長さ
	Vector3 length = obb2sphereCollition.GetCalDistance(obb, m_collisionNode);

	//	移動ベクトルを自機の角度分回転させる
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + length);

}

//	シールドと衝突していたらめり込み戻しをする
void Player::ShieldColSinkRestore(OBBNode & obb)
{
	//	地面と当たっているとき
	if (this->IsOBBCollision(obb))
	{
		m_isCollision = true;

		//	めり込み戻し
		this->ShieldSinkRestore(obb);
	}

}

//	シールドとのめり込み分戻す
void Player::ShieldSinkRestore(OBBNode & obb)
{
	//	立方体と敵との当たり判定
	OBB2SphereCollision obb2sphereCollition;
	//	めり込んだ長さ
	Vector3 length = obb2sphereCollition.GetCalDistance(obb, m_collisionNode);

	//	上方向にめり込み返す
	float x = std::fabs(length.x);
	float y = std::fabs(length.y);
	float z = std::fabs(length.z);

	//	移動ベクトルを自機の角度分回転させる
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + Vector3(x, y, z));

}

//	重力をかける
void Player::Gravity()
{
	//	回転
	float angle = m_model.GetRotation().y;
	Matrix rotmat = Matrix::CreateRotationY(angle);
	//	移動ベクトルを自機の角度分回転させる
	Vector3 move = Vector3::TransformNormal(GRAVITY, rotmat);
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + move);

}

//	ゲームオーバーエリアを越えるかどうか
bool Player::IsAreaOver(OBBNode& obb)
{
	Vector3 pos = m_model.GetTranslation();

	//	ステージに当たっていないとき
	if (!this->IsOBBCollision(obb))
	{
		Vector3 min = obb.GetLocalCenter() - obb.GetRadius();
		Vector3 max = obb.GetLocalCenter() + obb.GetRadius();

		//	ゲームオーバーエリアにきたら
		if (pos.x <= min.x || pos.x >= max.x ||
			pos.y <= min.y ||
			pos.z <= min.z || pos.z >= max.z)
		{
			return true;
		}
	}
	return false;
}

//	操作を使用停止する
void Player::StopControl()
{
	m_isCollision = false;
}
