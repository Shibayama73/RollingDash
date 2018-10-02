//============================================================//
//*名　前	FollowCamera.h
//*内　容	追尾カメラ
//*日　付	2017.7.11
//*更　新	2017.7.11
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <Windows.h>
#include "..\Keyboards\Keyboards.h"
#include "Camera.h"
#include "..\..\..\Game\Game\Objects\Player.h"

class FollowCamera :public Camera
{
public:
	//	自機とカメラの距離
	static const float CAMERA_DISTANCE;
	//	コンストラクタ
	FollowCamera(int width, int height);
	//	更新
	void Update() override;
	//	追従対象の座標をセット
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos);
	//	追従対象の回転角をセット
	void SetTargetAngle(float targetAngle);
	//	キーボードをセット
	void SetKeyboard(Keyboards* keyboard);

protected:
	//	追従対象の座標
	DirectX::SimpleMath::Vector3 m_targetPos;
	//	追従対象の回転角
	float m_targetAngle;

private:
	//	FPSフラグ
	bool m_isFPS;

};
