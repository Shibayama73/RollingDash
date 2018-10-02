//============================================================//
//*名　前	ImpactEmitter.cpp
//*内　容	衝撃エフェクトエミッタ
//*日　付	2018.7.20
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#include "ImpactEmitter.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

ImpactEmitter::ImpactEmitter(Vector3 position) :Emitter(position)
{
	m_scale = 0;
}

void ImpactEmitter::Update()
{
	//	発生制限時間になるまで
	if (m_occurNowTime <= m_occurLimitTime)
	{
		//	パーティクルエフェクトマネージャの作成
		ParticleEffectManager* particleManager = ParticleEffectManager::GetInstance();

		//	座標
		Vector3 move;
		float angle = RandomRange(0, 360);
		move.x = 0.2f*cosf(angle);
		move.y = 1;
		move.z = 0.2f*sinf(angle);

		particleManager->Entry(
			1,
			m_Position + Vector3(move),	//ワールド座標(開始)
			m_Position + Vector3(move),	//ワールド座標(終了)
			Vector3(0.0f, 0.2f, 0.0f),	//速度
			Color(RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), 1),
			Color(RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), 0),	//色(開始、終了)
			m_scale,				//スケール(開始、終了)
			0,
			0,						//角度(開始、終了)
			0,
			RandomRange(10, 30)		//消滅時間
		);

		//	スケール加算
		if (m_scale <= 3.0f)
		{
			m_scale += 0.02f;
		}
		//	発生制限時間
		m_occurNowTime++;
	}

}
