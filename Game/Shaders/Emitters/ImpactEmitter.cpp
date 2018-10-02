//============================================================//
//*���@�O	ImpactEmitter.cpp
//*���@�e	�Ռ��G�t�F�N�g�G�~�b�^
//*���@�t	2018.7.20
//*�X�@�V	2018.7.24
//*�����	N.Shibayama
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
	//	�����������ԂɂȂ�܂�
	if (m_occurNowTime <= m_occurLimitTime)
	{
		//	�p�[�e�B�N���G�t�F�N�g�}�l�[�W���̍쐬
		ParticleEffectManager* particleManager = ParticleEffectManager::GetInstance();

		//	���W
		Vector3 move;
		float angle = RandomRange(0, 360);
		move.x = 0.2f*cosf(angle);
		move.y = 1;
		move.z = 0.2f*sinf(angle);

		particleManager->Entry(
			1,
			m_Position + Vector3(move),	//���[���h���W(�J�n)
			m_Position + Vector3(move),	//���[���h���W(�I��)
			Vector3(0.0f, 0.2f, 0.0f),	//���x
			Color(RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), 1),
			Color(RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), 0),	//�F(�J�n�A�I��)
			m_scale,				//�X�P�[��(�J�n�A�I��)
			0,
			0,						//�p�x(�J�n�A�I��)
			0,
			RandomRange(10, 30)		//���Ŏ���
		);

		//	�X�P�[�����Z
		if (m_scale <= 3.0f)
		{
			m_scale += 0.02f;
		}
		//	������������
		m_occurNowTime++;
	}

}
