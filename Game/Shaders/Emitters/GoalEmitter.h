//============================================================//
//*名　前	GoalEmitter.h
//*内　容	ゴール範囲エフェクトエミッタ
//*日　付	2018.7.20
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\Managers\ParticleEffectManager.h"
#include "..\Managers\Emitter.h"

class GoalEmitter :public Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	GoalEmitter(Vector3 position);
	void Update();
	void End();

};
