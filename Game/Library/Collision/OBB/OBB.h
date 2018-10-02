//============================================================//
//*���@�O	OBB.h
//*���@�e	OBB���
//*���@�t	2017.10.23
//*�X�@�V	2018.7.20
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <d3d11_1.h>
#include <simplemath.h>

class OBB
{
public:
	//	���e�����̎Z�o
	float GetCalcProjectionDistance(DirectX::SimpleMath::Vector3 Crossproduct);

protected:
	OBB();
	//	���S���W
	DirectX::SimpleMath::Vector3 m_center;
	//	���a
	DirectX::SimpleMath::Vector3 m_radius;
	//	������
	DirectX::SimpleMath::Vector3 m_separationAxisX;
	DirectX::SimpleMath::Vector3 m_separationAxisY;
	DirectX::SimpleMath::Vector3 m_separationAxisZ;

};

