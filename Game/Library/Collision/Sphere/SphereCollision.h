//============================================================//
//*���@�O	SphereCollision.h
//*���@�e	�������蔻��
//*���@�t	2017.9.20
//*�X�@�V	2018.5.10
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <d3d11_1.h>
#include <simplemath.h>

class SphereCollision
{
public:
	//	�R���X�g���N�^(���a�̐ݒ�)
	SphereCollision();
	//	���Ƌ��������������ǂ���
	bool CheckSphere2Sphere(const SphereCollision& _sphereA, const SphereCollision& _sphereB);

protected:
	//	���S���W
	DirectX::SimpleMath::Vector3 m_center;
	//	���a
	float m_radius;

};
