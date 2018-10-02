//============================================================//
//*名　前	GoalEmitter.cpp
//*内　容	ゴール範囲エフェクトエミッタ
//*日　付	2018.7.20
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#include "GoalEmitter.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

GoalEmitter::GoalEmitter(Vector3 position) :Emitter(position)
{
}

void GoalEmitter::Update()
{
	//	発生制限時間になるまで
	if (m_occurNowTime <= m_occurLimitTime)
	{
		//	パーティクルエフェクトマネージャの作成
		ParticleEffectManager* particleManager = ParticleEffectManager::GetInstance();

		//	円運動
		Vector3 pos = m_Position;
		m_Param += 0.1f;
		pos.x = cosf(m_Param) * 5.0f;
		pos.y = 0;
		pos.z = sinf(m_Param) * 5.0f;
		pos = m_Position + pos;

		particleManager->Entry(
			4,
			pos,					//ワールド座標
			pos,
			Vector3(0, 0.01f, 0),	//速度
			Color(1, 1, 1, 1),		//色(開始、終了)
			Color(1, 1, 1, 0),
			1,						//スケール(開始、終了)
			0,
			0,						//角度(開始、終了)
			0,
			RandomRange(30, 60)		//消滅時間
		);
		//	発生制限時間
		m_occurNowTime++;
	}

}

void GoalEmitter::End()
{
	m_occurLimitTime = 0.0f;
}
