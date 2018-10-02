//============================================================//
//*名　前	Player.h
//*内　容	3Dオブジェクト
//*日　付	2017.8.01
//*更　新	2017.8.01
//*制作者	N.Shibayama
//============================================================//
#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <Effects.h>			//BasicEffect
#include <CommonStates.h>		//CommonStates
#include <SimpleMath.h>			//Vecter3
#include <Model.h>

#include "..\..\Library\Camera\Camera.h"
#include "..\..\Library\Devices\Devices.h"

class Object3D
{
public:
	//	静的メンバ関数
	static void InitializeStatic(Camera* camera);

private:
	//	デバイス情報
	std::unique_ptr<Devices> device;

	//	カメラ
	static Camera* m_Camera;
	//	汎用ステート設定
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//	エフェクトファクトリ
	static std::unique_ptr<DirectX::EffectFactory> m_factory;

public:
	//	コンストラクタ
	Object3D();

	//	CMOモデルを読み込む
	void LoadModel(const wchar_t* fileName);
	//	更新
	void Update();
	//	描画
	void Draw();

	//	スケーリング(XYZ)
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	//	回転角(XYZ)→フラグをオフ
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation; m_UseQuaternion = false; }
	//	回転角(クォータニオン)→フラグをオン
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotationQ) { m_rotationQ = rotationQ; m_UseQuaternion = true; }
	//	平行移動(XYZ)
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation) { m_translation = translation; }
	//	ワールド行列
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }
	//	親の3Dオブジェクト
	void SetObjParent(Object3D* objParentle) { m_ObjParent = objParentle; }

	//	スケーリング(XYZ)取得
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	//	回転角(XYZ)取得
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	//	平行移動(XYZ)取得
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }
	//	ワールド行列取得
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }

private:
	//	モデル
	std::unique_ptr<DirectX::Model> m_model;
	//	スケーリング(XYZ)
	DirectX::SimpleMath::Vector3 m_scale;
	//	回転角(XYZ)
	DirectX::SimpleMath::Vector3 m_rotation;
	//	回転角(クォータニオン)
	DirectX::SimpleMath::Quaternion m_rotationQ;
	//	平行移動(XYZ)
	DirectX::SimpleMath::Vector3 m_translation;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	//	親のObj3dへのポインタ
	Object3D* m_ObjParent;
	//	回転をクォータニオンで扱うフラグ
	bool m_UseQuaternion;

};
