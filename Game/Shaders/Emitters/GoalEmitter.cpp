//============================================================//
//*���@�O	GoalEmitter.cpp
//*���@�e	�S�[���͈̓G�t�F�N�g�G�~�b�^
//*���@�t	2018.7.20
//*�X�@�V	2018.7.24
//*�����	N.Shibayama
//============================================================//
#include "GoalEmitter.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

GoalEmitter::GoalEmitter(Vector3 position) :Emitter(position)
{
}

void GoalEmitter::Update()
{
	//	�����������ԂɂȂ�܂�
	if (m_occurNowTime <= m_occurLimitTime)
	{
		//	�p�[�e�B�N���G�t�F�N�g�}�l�[�W���̍쐬
		ParticleEffectManager* particleManager = ParticleEffectManager::GetInstance();

		//	�~�^��
		Vector3 pos = m_Position;
		m_Param += 0.1f;
		pos.x = cosf(m_Param) * 5.0f;
		pos.y = 0;
		pos.z = sinf(m_Param) * 5.0f;
		pos = m_Position + pos;

		particleManager->Entry(
			4,
			pos,					//���[���h���W
			pos,
			Vector3(0, 0.01f, 0),	//���x
			Color(1, 1, 1, 1),		//�F(�J�n�A�I��)
			Color(1, 1, 1, 0),
			1,						//�X�P�[��(�J�n�A�I��)
			0,
			0,						//�p�x(�J�n�A�I��)
			0,
			RandomRange(30, 60)		//���Ŏ���
		);
		//	������������
		m_occurNowTime++;
	}

}

void GoalEmitter::End()
{
	m_occurLimitTime = 0.0f;
}
