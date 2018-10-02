//============================================================//
//*名　前	CircleEmitter.cpp
//*内　容	中心円エミッタ
//*日　付	2018.7.20
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#include "CircleEmitter.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CircleEmitter::CircleEmitter(Vector3 position) :Emitter(position)
{
	m_scale = 0;
}

CircleEmitter::~CircleEmitter()
{
}

void CircleEmitter::Update()
{
	//	発生制限時間になるまで
	if (m_occurNowTime <= m_occurLimitTime)
	{
		//	パーティクルエフェクトマネージャの作成
		ParticleEffectManager* particleManager = ParticleEffectManager::GetInstance();

		for (int i = 0; i < 10; i++)
		{
			particleManager->Entry(
				0,
				Vector3(0.0f, 0.0f, 0.0f),	//ワールド座標(開始)
				Vector3(0.0f, 0.0f, 0.0f),	//ワールド座標(終了)
				Vector3(0.0f, 0.0f, 0.0f),	//速度
				Color(RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), 1),
				Color(RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), 0),	//色(開始、終了)
				m_scale,				//スケール(開始、終了)
				4.0f,
				0,						//角度(開始、終了)
				0,
				RandomRange(60, 90)		//消滅時間
			);

			//	スケール加算
			if (m_scale <= 3.0f)
			{
				m_scale += 0.05f;
			}

		}
		//	発生制限時間
		m_occurNowTime++;
	}

}

void CircleEmitter::End()
{
	m_occurLimitTime = 0.0f;
}
