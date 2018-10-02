//============================================================//
//*名　前	Emitter.cpp
//*内　容	エフェクトを発生させる
//*日　付	2018.7.18
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#include "Emitter.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	テクスチャ番号実体
int Emitter::s_TextureSlot;

Emitter::Emitter(Vector3 position)
{
	m_Position = position;
	m_Param = 0;
	m_occurNowTime = 0.0f;

}

void Emitter::LoadTexture(int textureSlot, const wchar_t* filename)
{
	s_TextureSlot = textureSlot;
	ParticleEffectManager::GetInstance()->Load(textureSlot, filename);
}

// 指定範囲の乱数を取得
float Emitter::RandomRange(float min_value, float max_value)
{
	//	0から1の範囲の乱数
	float value = (float)rand() / RAND_MAX;
	value = min_value + (max_value - min_value)*value;
	return value;
}

int Emitter::RandomRangInt(int min_value, int max_value)
{
	//	0から1の範囲の乱数
	int value = (int)rand() / RAND_MAX;
	value = min_value + (max_value - min_value)*value;
	return value;
}
