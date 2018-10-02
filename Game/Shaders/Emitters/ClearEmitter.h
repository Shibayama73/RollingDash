//============================================================//
//*名　前	ClearEmitter.h
//*内　容	ゲームクリアエフェクトエミッタ
//*日　付	2018.7.20
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\Managers\ParticleEffectManager.h"
#include "..\Managers\Emitter.h"

class ClearEmitter :public Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	ClearEmitter(Vector3 position);
	void Update();

private:
	//	スケール
	float m_scale;

};
