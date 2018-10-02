//============================================================//
//*���@�O	Emitter.h
//*���@�e	�G�t�F�N�g�𔭐�������
//*���@�t	2018.7.18
//*�X�@�V	2018.7.20
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "ParticleEffectManager.h"

class Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	Emitter(Vector3 position);
	virtual void Update() = 0;

	//	�e�N�X�`���Ǎ���
	static void LoadTexture(int textureSlot, const wchar_t* filename);
	// �w��͈̗͂������擾
	float RandomRange(float min_value, float max_value);
	// �w��͈̗͂������擾
	int RandomRangInt(int min_value, int max_value);

	//	���W�̐ݒ�
	void SetPosition(Vector3 position) { m_Position = position; }

	//	���x�̃A�N�Z�b�T
	void SetVelocity(Vector3 velocity) { m_Velocity = velocity; }
	//	������������
	void SetOccurLimitTime(float occurLimitTime) { m_occurLimitTime = occurLimitTime; }

protected:
	//	�e�N�X�`���ԍ�
	static int s_TextureSlot;
	//	���W
	Vector3 m_Position;
	//	���x
	Vector3 m_Velocity;
	//	�p�x
	float m_Param;
	//	������������
	float m_occurLimitTime;
	//	���݂̔�������
	float m_occurNowTime;

};
