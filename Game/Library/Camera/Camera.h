//============================================================//
//*名　前	Camera.h
//*内　容	カメラ
//*日　付	2017.7.11
//*更　新	2017.7.11
//*制作者	N.Shibayama
//============================================================//
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

class Camera
{
public:
	Camera(int width, int height);
	virtual ~Camera();
	//	更新
	virtual void Update();
	//	ビュー行列の取得
	const DirectX::SimpleMath::Matrix& GetViewMatrix();
	//	射影行列の取得
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix();
	//	視点座標のセット
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);
	//	注視点・参照点セット
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);
	//	カメラの向きのセット
	void SetUpvec(const DirectX::SimpleMath::Vector3& upvec);
	//	垂直方向視野角のセット
	void SetFovY(float fovY);
	//	アスペクト比のセット
	void SetAspect(float aspect);
	//	ニアクリップのセット
	void SetNearclip(float nearclip);
	//	ファークリップのセット
	void SetFarclip(float farclip);

//	const DirectX::SimpleMath::Matrix& GetView() const { return m_view; }
//	const DirectX::SimpleMath::Matrix& GetProj() const { return m_proj; }

	const DirectX::SimpleMath::Matrix& GetBillboard() const { return m_billboard; }
	const DirectX::SimpleMath::Matrix& GetBillboardConstrainY() const { return m_billboardConstrainY; }

	// ビルボード行列の計算
	void CalcBillboard();

protected:
	//	カメラの位置（視点座標）
	DirectX::SimpleMath::Vector3 m_eyepos;
	//	カメラの見ている先（注視点・参照点）
	DirectX::SimpleMath::Vector3 m_refpos;
	//	カメラの上方向ベクトル
	DirectX::SimpleMath::Vector3 m_upvec;
	//	ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	//	垂直方向視野角
	float m_fovY;
	//	アスペクト比（画面比率）
	float m_aspect;
	//	ニアクリップ（手前の表示限界距離）
	float m_nearclip;
	//	ファークリップ（奥の表示限界距離）
	float m_farclip;
	//	射影行列
	DirectX::SimpleMath::Matrix m_proj;

	// ビルボード行列
	DirectX::SimpleMath::Matrix m_billboard;
	// ビルボード行列(Y軸周り限定）
	DirectX::SimpleMath::Matrix m_billboardConstrainY;

};