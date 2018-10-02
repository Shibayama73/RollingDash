//============================================================//
//*名　前	FollowCamera.cpp
//*内　容	追尾カメラ
//*日　付	2017.7.11
//*更　新	2017.7.11
//*制作者	N.Shibayama
//============================================================//
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	静的メンバ変数の初期化
const float FollowCamera::CAMERA_DISTANCE = 12.0f;

FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	//	初期化===============================
	//	追従対象の座標
	m_targetPos = Vector3(0, 0, 0);
	//	追従対象の回転角
	m_targetAngle = 0.0f;
	//	FPSフラグ
	m_isFPS = false;

	{//	TPSカメラの処理
		Vector3 eyepos, refpos;
		//	参照点座標の計算
		refpos = m_targetPos + Vector3(0, 2.0f, 0);
		//	自機からカメラまでの距離
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);

		//	自機から後ろに回り込むための回転行列
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		//	カメラへのベクトルを回転させる
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		//	カメラ座標を計算
		eyepos = refpos + cameraV;

		//	カメラに情報を渡す
		this->SetRefPos(refpos);
		this->SetEyePos(eyepos);
	}

}

void FollowCamera::Update()
{
	auto& key = Keyboards::GetInstance();
	key.GetState();

	//	カメラの設定（自機に追従するカメラ）
	//	視点・参照点の座標
	Vector3 eyepos, refpos;

	if (m_isFPS)
		//FPSカメラとTPSカメラは参照点とカメラの座標計算の順番を入れ替えるのみ
	{//	FPSカメラの処理
		Vector3 position;
		//	カメラ座標の計算
		position = m_targetPos + Vector3(0, 0.2f, 0);

		//	自機からカメラまでの距離
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);

		//	自機から後ろに回り込むための回転行列
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		//	カメラへのベクトルを回転させる
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		//	少し進んだ先視点座標の計算
		eyepos = position + cameraV * 0.1f;
		//	先に進んだ参照点座標の計算
		refpos = position + cameraV;

	}

	else
	{//	TPSカメラの処理
		 //	参照点座標の計算
		refpos = m_targetPos + Vector3(0, 2.0f, 0);
		//	自機からカメラまでの距離
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);

		//	自機から後ろに回り込むための回転行列
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		//	カメラへのベクトルを回転させる
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		//	カメラ座標を計算
		eyepos = refpos + cameraV;

		//ゴムひもの挙動
		//	視点を現在位置から補間する
		//	前回の視点 + (視点の目標点 - 前回の視点) * 0.05f
		eyepos = m_eyepos + (eyepos - m_eyepos)*0.03f;

		//	カメラの参照点を現在位置から補間する
		//	前回の参照点 + (参照点の目標点 - 前回の参照点) * 0.05f
		refpos = m_refpos + (refpos - m_refpos)*0.3f;

	}

	//	カメラに情報を渡す
	this->SetRefPos(refpos);
	this->SetEyePos(eyepos);

	//	カメラ(基底クラス)の更新
	Camera::Update();

}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}

void FollowCamera::SetKeyboard(Keyboards * keyboard)
{
	//m_keyboard = keyboard;
}
