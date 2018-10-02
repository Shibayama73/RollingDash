//============================================================//
//*���@�O	ImpactEmitter.h
//*���@�e	�Ռ��G�t�F�N�g�G�~�b�^
//*���@�t	2018.7.20
//*�X�@�V	2018.7.24
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "..\Managers\ParticleEffectManager.h"
#include "..\Managers\Emitter.h"

class ImpactEmitter :public Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	ImpactEmitter(Vector3 position);
	void Update();

private:
	//	�X�P�[��
	float m_scale;

};
