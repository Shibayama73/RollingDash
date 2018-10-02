//============================================================//
//*���@�O	ClearEmitter.h
//*���@�e	�Q�[���N���A�G�t�F�N�g�G�~�b�^
//*���@�t	2018.7.20
//*�X�@�V	2018.7.24
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "..\Managers\ParticleEffectManager.h"
#include "..\Managers\Emitter.h"

class ClearEmitter :public Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	ClearEmitter(Vector3 position);
	void Update();

private:
	//	�X�P�[��
	float m_scale;

};
