//============================================================//
//*名　前	OverEmitter.h
//*内　容	ゲームオーバーエフェクトエミッタ
//*日　付	2018.7.20
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\Managers\ParticleEffectManager.h"
#include "..\Managers\Emitter.h"

class OverEmitter :public Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	OverEmitter(Vector3 position);
	void Update();

private:
	//	スケール
	float m_scale;

};
