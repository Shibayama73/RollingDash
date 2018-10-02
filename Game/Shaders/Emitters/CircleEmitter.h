//============================================================//
//*���@�O	CircleEmitter.h
//*���@�e	���S�~�G�~�b�^
//*���@�t	2018.7.20
//*�X�@�V	2018.7.24
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "..\Managers\ParticleEffectManager.h"
#include "..\Managers\Emitter.h"

class CircleEmitter :public Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	CircleEmitter(Vector3 position);
	~CircleEmitter();
	void Update();
	void End();

private:
	//	�X�P�[��
	float m_scale;

};
