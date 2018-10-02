//============================================================//
//*名　前	Camera.cpp
//*内　容	カメラ
//*日　付	2017.7.11
//*更　新	2017.7.11
//*制作者	N.Shibayama
//============================================================//
#include "..\..\Library\Framework\pch.h"
#include "Camera.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace DirectX::SimpleMath;

Camera::Camera(int width, int height)
{
	//	初期化==========================================
	//	カメラの位置（視点座標）
	m_eyepos = Vector3(0, 0, 20.0f);
	//	カメラの見ている先（注視点・参照点）
	m_refpos = Vector3(0, 0, 10);
	//	カメラの上方向ベクトル
	m_upvec = Vector3(0, 1.0f, 0);

	//	垂直方向視野角
	m_fovY = XMConvertToRadians(60.0f);
	//	アスペクト比（画面比率）
	m_aspect = (float)width / height;
	//	ニアクリップ（手前の表示限界距離）
	m_nearclip = 0.1f;
	//	ファークリップ（奥の表示限界距離）
	m_farclip = 1000.0f;

	//=======================================================
	//	ビュー行列の生成
	m_upvec.Normalize();	//長さを1に調整する
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//	射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

Camera::~Camera()
{
}

//	更新
void Camera::Update()
{
	//	ビュー行列の生成
	m_upvec.Normalize();	//長さを1に調整する
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//	射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

//	ビュー行列の取得
const DirectX::SimpleMath::Matrix& Camera::GetViewMatrix()
{
	////	ビュー行列の生成
	//m_upvec.Normalize();	//長さを1に調整する
	//m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	return m_view;
}

//	射影行列の取得
const DirectX::SimpleMath::Matrix& Camera::GetProjectionMatrix()
{
	////	射影行列の生成
	//m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

	return m_proj;
}

//	視点座標のセット
void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& eyepos)
{
	//	視点座標＝eyepos
	m_eyepos = eyepos;
}

//	注視点・参照点セット
void Camera::SetRefPos(const DirectX::SimpleMath::Vector3& refpos)
{
	m_refpos = refpos;
}

//	カメラの向きのセット
void Camera::SetUpvec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;
}

//	垂直方向視野角のセット
void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

//	アスペクト比のセット
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

//	ニアクリップのセット
void Camera::SetNearclip(float nearclip)
{
	m_nearclip = nearclip;
}

//	ファークリップのセット
void Camera::SetFarclip(float farclip)
{
	m_farclip = farclip;
}

// ビルボード行列の計算
void Camera::CalcBillboard()
{
	// 視線方向
	Vector3 eyeDir = m_eyepos - m_refpos;
	// Y軸
	Vector3 Y = Vector3::UnitY;
	// X軸
	Vector3 X = Y.Cross(eyeDir);
	X.Normalize();
	// Z軸
	Vector3 Z = X.Cross(Y);
	Z.Normalize();
	// Y軸周りビルボード行列（右手系の為Z方向反転）
	m_billboardConstrainY = Matrix::Identity;
	m_billboardConstrainY.m[0][0] = X.x;
	m_billboardConstrainY.m[0][1] = X.y;
	m_billboardConstrainY.m[0][2] = X.z;
	m_billboardConstrainY.m[1][0] = Y.x;
	m_billboardConstrainY.m[1][1] = Y.y;
	m_billboardConstrainY.m[1][2] = Y.z;
	m_billboardConstrainY.m[2][0] = -Z.x;
	m_billboardConstrainY.m[2][1] = -Z.y;
	m_billboardConstrainY.m[2][2] = -Z.z;

	Y = eyeDir.Cross(X);
	Y.Normalize();
	eyeDir.Normalize();
	// ビルボード行列（右手系の為Z方向反転）
	m_billboard = Matrix::Identity;
	m_billboard.m[0][0] = X.x;
	m_billboard.m[0][1] = X.y;
	m_billboard.m[0][2] = X.z;
	m_billboard.m[1][0] = Y.x;
	m_billboard.m[1][1] = Y.y;
	m_billboard.m[1][2] = Y.z;
	m_billboard.m[2][0] = -eyeDir.x;
	m_billboard.m[2][1] = -eyeDir.y;
	m_billboard.m[2][2] = -eyeDir.z;
}
