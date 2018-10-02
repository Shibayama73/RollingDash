//============================================================//
//*名　前	OBBNode.cpp
//*内　容	OBBノード
//*日　付	2017.10.23
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#include "OBBNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

OBBNode::OBBNode()
{
	//	中心座標
	m_localCenter = Vector3(0.0f, 0.0f, 0.0f);
	//	角度
	m_localRotation = Vector3(0.0f, 0.0f, 0.0f);
	//	回転行列の更新
	SetRotation(m_localRotation);
	//	地面との当たりフラグ
//	m_groundFlag = false;
	//	回転行列
	m_rotation = Matrix::Identity;

}

void OBBNode::Initialize()
{
	this->m_model.LoadModel(L"Resources/cubeStage.cmo");
}

void OBBNode::Update()
{
	//	初期位置の設定
	this->m_model.SetTranslation(m_center);

	//	回転行列の更新
	m_rotation = SetRotation(m_localRotation);

	//	分離軸の更新
	m_separationAxisX = Vector3::TransformNormal(Vector3(1.0f, 0.0f, 0.0f), m_rotation);
	m_separationAxisY = Vector3::TransformNormal(Vector3(0.0f, 1.0f, 0.0f), m_rotation);
	m_separationAxisZ = Vector3::TransformNormal(Vector3(0.0f, 0.0f, 1.0f), m_rotation);

	//	モデルの更新
	this->m_model.Update();

}

void OBBNode::Draw()
{
	this->m_model.Draw();
}

//=======================================================================//

//	ローカル中心座標の設定
void OBBNode::SetLocalCenter(DirectX::SimpleMath::Vector3 center)
{
	m_localCenter = center;
}

//	ローカル角度の設定
void OBBNode::SetLocalRotation(DirectX::SimpleMath::Vector3 rotation)
{
	m_localRotation = rotation;
}

//	回転行列の設定
DirectX::SimpleMath::Matrix OBBNode::SetRotation(DirectX::SimpleMath::Vector3 rotation)
{
	Matrix matrix;
	Matrix matrixX = matrix.CreateRotationX(rotation.x);
	Matrix matrixY = matrix.CreateRotationY(rotation.y);
	Matrix matrixZ = matrix.CreateRotationZ(rotation.z);

	return matrixZ*matrixX*matrixY;
}

//	半径の設定
void OBBNode::SetRadius(DirectX::SimpleMath::Vector3 radius)
{
	m_radius = radius;
}

////	地面との当たりフラグ取得
//bool OBBNode::IsGroundFlag()
//{
//	return m_groundFlag;
//}

//=======================================================================//
//	ローカル中心座標の取得
DirectX::SimpleMath::Vector3 OBBNode::GetLocalCenter()
{
	return m_localCenter;
}

//	ローカル角度の取得
DirectX::SimpleMath::Vector3 OBBNode::GetLocalRotation()
{
	return m_localRotation;
}

//	回転行列の取得
DirectX::SimpleMath::Matrix OBBNode::GetRotation()
{
	return m_rotation;
}

//	半径の取得
DirectX::SimpleMath::Vector3 OBBNode::GetRadius()
{
	return m_radius;
}

//	分離軸X
DirectX::SimpleMath::Vector3 OBBNode::GetLocalSeparationAxisX()
{
	return m_separationAxisX;
}

//	分離軸Y
DirectX::SimpleMath::Vector3 OBBNode::GetLocalSeparationAxisY()
{
	return m_separationAxisY;
}

//	分離軸Z
DirectX::SimpleMath::Vector3 OBBNode::GetLocalSeparationAxisZ()
{
	return m_separationAxisZ;
}

//	中心座標
DirectX::SimpleMath::Vector3 OBBNode::GetCenter()
{
	return m_center;
}

////	地面との当たりフラグ設定
//void OBBNode::SetGroundFlag(bool flag)
//{
//	m_groundFlag = flag;
//}
