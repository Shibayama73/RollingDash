//============================================================//
//*名　前	ImpactEmitter.h
//*内　容	衝撃エフェクトエミッタ
//*日　付	2018.7.20
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\Managers\ParticleEffectManager.h"
#include "..\Managers\Emitter.h"

class ImpactEmitter :public Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	ImpactEmitter(Vector3 position);
	void Update();

private:
	//	スケール
	float m_scale;

};
