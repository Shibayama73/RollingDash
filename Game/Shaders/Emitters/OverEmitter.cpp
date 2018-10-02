//============================================================//
//*���@�O	OverEmitter.cpp
//*���@�e	�Q�[���I�[�o�[�G�t�F�N�g�G�~�b�^
//*���@�t	2018.7.20
//*�X�@�V	2018.7.24
//*�����	N.Shibayama
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
	//	�����������ԂɂȂ�܂�
	if (m_occurNowTime <= m_occurLimitTime)
	{
		//	�p�[�e�B�N���G�t�F�N�g�}�l�[�W���̍쐬
		ParticleEffectManager* particleManager = ParticleEffectManager::GetInstance();

		//	���W
		Vector3 move;
		float angle = RandomRange(0.0f, 360.0f);
		move.x = RandomRange(-5.0f, 5.0f);
		move.y = 1.0f;
		move.z = RandomRange(-5.0f, 5.0f);

		particleManager->Entry(
			2,
			m_Position + Vector3(move),		//���[���h���W(�J�n�A�I��)
			m_Position + Vector3(move),
			Vector3(0.0f, -0.98f, 0.0f),	//���x
			Color(1, 1, 1, 1),		//�F(�J�n�A�I��)
			Color(1, 1, 1, 0),
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
