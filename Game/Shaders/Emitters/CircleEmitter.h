//============================================================//
//*名　前	CircleEmitter.h
//*内　容	中心円エミッタ
//*日　付	2018.7.20
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\Managers\ParticleEffectManager.h"
#include "..\Managers\Emitter.h"

class CircleEmitter :public Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	CircleEmitter(Vector3 position);
	~CircleEmitter();
	void Update();
	void End();

private:
	//	スケール
	float m_scale;

};
