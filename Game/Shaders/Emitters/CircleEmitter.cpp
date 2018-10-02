//============================================================//
//*���@�O	CircleEmitter.cpp
//*���@�e	���S�~�G�~�b�^
//*���@�t	2018.7.20
//*�X�@�V	2018.7.24
//*�����	N.Shibayama
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
	//	�����������ԂɂȂ�܂�
	if (m_occurNowTime <= m_occurLimitTime)
	{
		//	�p�[�e�B�N���G�t�F�N�g�}�l�[�W���̍쐬
		ParticleEffectManager* particleManager = ParticleEffectManager::GetInstance();

		for (int i = 0; i < 10; i++)
		{
			particleManager->Entry(
				0,
				Vector3(0.0f, 0.0f, 0.0f),	//���[���h���W(�J�n)
				Vector3(0.0f, 0.0f, 0.0f),	//���[���h���W(�I��)
				Vector3(0.0f, 0.0f, 0.0f),	//���x
				Color(RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), 1),
				Color(RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), RandomRange(0.1f, 0.9f), 0),	//�F(�J�n�A�I��)
				m_scale,				//�X�P�[��(�J�n�A�I��)
				4.0f,
				0,						//�p�x(�J�n�A�I��)
				0,
				RandomRange(60, 90)		//���Ŏ���
			);

			//	�X�P�[�����Z
			if (m_scale <= 3.0f)
			{
				m_scale += 0.05f;
			}

		}
		//	������������
		m_occurNowTime++;
	}

}

void CircleEmitter::End()
{
	m_occurLimitTime = 0.0f;
}
