//============================================================//
//*名　前	OBBNode.h
//*内　容	OBBノード
//*日　付	2017.10.23
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "OBB.h"
#include "GroundNode.h"

class OBBNode :public GroundNode, public OBB
{
public:
	OBBNode();
	//	初期化
	void Initialize();
	//	更新
	void Update();
	//	描画
	void Draw();

	//	ローカル中心座標の設定
	void SetLocalCenter(DirectX::SimpleMath::Vector3 center);
	//	ローカル角度の設定
	void SetLocalRotation(DirectX::SimpleMath::Vector3 rotation);
	//	回転行列の設定
	DirectX::SimpleMath::Matrix SetRotation(DirectX::SimpleMath::Vector3 rotation);
	//	半径の設定
	void SetRadius(DirectX::SimpleMath::Vector3 radius);

	//	ローカル中心座標の取得
	DirectX::SimpleMath::Vector3 GetLocalCenter();
	//	ローカル角度の取得
	DirectX::SimpleMath::Vector3 GetLocalRotation();
	//	回転行列の取得
	DirectX::SimpleMath::Matrix GetRotation();
	//	半径の取得
	DirectX::SimpleMath::Vector3 GetRadius();
	//	分離軸の取得
	DirectX::SimpleMath::Vector3 GetLocalSeparationAxisX();
	DirectX::SimpleMath::Vector3 GetLocalSeparationAxisY();
	DirectX::SimpleMath::Vector3 GetLocalSeparationAxisZ();
	//	中心座標の取得
	DirectX::SimpleMath::Vector3 GetCenter();

private:
	//	ローカル中心座標
	DirectX::SimpleMath::Vector3 m_localCenter;
	//	ローカル角度
	DirectX::SimpleMath::Vector3 m_localRotation;
	//	回転行列
	DirectX::SimpleMath::Matrix m_rotation;

};
