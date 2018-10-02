//============================================================//
//*���@�O	Emitter.cpp
//*���@�e	�G�t�F�N�g�𔭐�������
//*���@�t	2018.7.18
//*�X�@�V	2018.7.20
//*�����	N.Shibayama
//============================================================//
#include "Emitter.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	�e�N�X�`���ԍ�����
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

// �w��͈̗͂������擾
float Emitter::RandomRange(float min_value, float max_value)
{
	//	0����1�͈̗̔͂���
	float value = (float)rand() / RAND_MAX;
	value = min_value + (max_value - min_value)*value;
	return value;
}

int Emitter::RandomRangInt(int min_value, int max_value)
{
	//	0����1�͈̗̔͂���
	int value = (int)rand() / RAND_MAX;
	value = min_value + (max_value - min_value)*value;
	return value;
}
