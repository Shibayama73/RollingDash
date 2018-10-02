//============================================================//
//*名　前	OverEmitter.cpp
//*内　容	ゲームオーバーエフェクトエミッタ
//*日　付	2018.7.20
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#include "OverEmitter.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

OverEmitter::OverEmitter(Vector3 position) :Emitter(position)
{
	m_scale = 0;
}

void OverEmitter::Update()
{
	//	発生制限時間になるまで
	if (m_occurNowTime <= m_occurLimitTime)
	{
		//	パーティクルエフェクトマネージャの作成
		ParticleEffectManager* particleManager = ParticleEffectManager::GetInstance();

		//	座標
		Vector3 move;
		float angle = RandomRange(0.0f, 360.0f);
		move.x = RandomRange(-5.0f, 5.0f);
		move.y = 1.0f;
		move.z = RandomRange(-5.0f, 5.0f);

		particleManager->Entry(
			2,
			m_Position + Vector3(move),		//ワールド座標(開始、終了)
			m_Position + Vector3(move),
			Vector3(0.0f, -0.98f, 0.0f),	//速度
			Color(1, 1, 1, 1),		//色(開始、終了)
			Color(1, 1, 1, 0),
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
