//============================================================//
//*名　前	Player.cpp
//*内　容	3Dオブジェクト
//*日　付	2017.8.01
//*更　新	2017.8.01
//*制作者	N.Shibayama
//============================================================//
#include "Object3D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	カメラ
Camera* Object3D::m_Camera;
//	汎用ステート設定
std::unique_ptr<DirectX::CommonStates> Object3D::m_states;
//	エフェクトファクトリ
std::unique_ptr<DirectX::EffectFactory> Object3D::m_factory;

void Object3D::InitializeStatic(Camera * camera)
{
	auto& device = Devices::GetInstance();

	m_Camera = camera;

	//	汎用ステート設定生成
	m_states = std::make_unique<CommonStates>(device.GetDevice().Get());
	//	エフェクトファクトリ作成
	m_factory = std::make_unique<EffectFactory>(device.GetDevice().Get());
	//	テクスチャファイル指定
	m_factory->SetDirectory(L"Resources");

}

Object3D::Object3D()
{
	//	メンバ変数の初期化
	m_scale = Vector3(1, 1, 1);
	m_ObjParent = nullptr;

	//	デフォルトではオイラー角を使用
	m_UseQuaternion = false;

}


void Object3D::LoadModel(const wchar_t * fileName)
{
	auto& device = Devices::GetInstance();
	//	CMOからモデルの読み込み
	m_model = Model::CreateFromCMO(device.GetDevice().Get(), fileName, *m_factory);

}

void Object3D::Update()
{
	//	ワールド行列の計算
	Matrix scalemat = Matrix::CreateScale(m_scale);
	Matrix rotmat;
	if (m_UseQuaternion)
	{
		//	クォータニオンで回転を計算
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		//	オイラー角で回転を計算
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		rotmat = rotmatZ * rotmatX * rotmatY;
	}
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//	ワールド座標の合成
	m_world = scalemat * rotmat * transmat;
	//	親の行列を掛ける(子供の行列＊親の行列)
	if (m_ObjParent)
	{
		m_world *= m_ObjParent->GetWorld();
	}

}

void Object3D::Draw()
{
	if (m_model)
	{
		auto& device = Devices::GetInstance();

		m_model->Draw(device.GetDeviceContext().Get(), *m_states, m_world, m_Camera->GetViewMatrix(), m_Camera->GetProjectionMatrix());
	}

}
