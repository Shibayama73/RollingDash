//============================================================//
//*���@�O	OBB2SphereCollision.cpp
//*���@�e	OBB�Ƌ��̂̓����蔻��
//*���@�t	2017.11.22
//*�X�@�V	2017.12.04
//*�����	N.Shibayama
//============================================================//
#include "..\..\..\Library\Framework\pch.h"
#include "OBB2SphereCollision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	OBB�Ƌ��̂̓����蔻��
bool OBB2SphereCollision::IsOBB2SphereCollision(OBBNode & obb, SphereNode & sphere)
{
	//	OBB�Ɠ_�̍ŒZ�����Z�o
	float length = GetCalOBB2CenterDistance(obb, sphere);

	//	���������̔��a���Z���Ƃ�
	if (length < sphere.GetRadius()) return true;

	return false;
}

//	OBB�Ɠ_�̍ŒZ�����Z�o
float OBB2SphereCollision::GetCalOBB2CenterDistance(OBBNode & obb, SphereNode & sphere)
{
	//	�͂ݏo�����x�N�g��
	Vector3 vec(0, 0, 0);

	//	�e���̂͂ݏo�����̃x�N�g���Z�o
	for (int i = 0; i < 3; i++)
	{
		float length;
		//	OBB�̔��a�擾
		if (i == 0) length = obb.GetRadius().x;
		if (i == 1) length = obb.GetRadius().y;
		if (i == 2) length = obb.GetRadius().z;

		//	0�ȉ��Ȃ�v�Z�s�v
		if (length <= 0) continue;

		//	2�_�̋����ƕ������̓���
		Vector3 distance = sphere.GetCenter() - obb.GetLocalCenter();
		Vector3 axis;
		if (i == 0) axis = obb.GetLocalSeparationAxisX();
		if (i == 1) axis = obb.GetLocalSeparationAxisY();
		if (i == 2) axis = obb.GetLocalSeparationAxisZ();
		//	�͂ݏo��
		float protrude = (distance.x * axis.x + distance.y * axis.y + distance.z * axis.z) / length;

		//	�͂ݏo������������Ȃ�
		protrude = fabsf(protrude);
		if (protrude > 1)
		{
			//	�͂ݏo�����̎Z�o
			if (i == 0) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisX();
			if (i == 1) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisY();
			if (i == 2) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisZ();
		}
	}
	return CalVec3Length(&vec);
}

float OBB2SphereCollision::CalVec3Length(Vector3* vec)
{
	float x, y, z;
	float length;

	if (!vec) return 0.0f;

	x = (float)(vec->x);
	y = (float)(vec->y);
	z = (float)(vec->z);
	length = sqrt(x*x + y*y + z*z);

	return (float)(length);
}

DirectX::SimpleMath::Vector3 OBB2SphereCollision::GetCalDistance(OBBNode & obb, SphereNode & sphere)
{
	//	�͂ݏo�����x�N�g��
	Vector3 vec(0, 0, 0);

	//	�e���̂͂ݏo�����̃x�N�g���Z�o
	for (int i = 0; i < 3; i++)
	{
		float length;
		//	OBB�̔��a�擾
		if (i == 0) length = obb.GetRadius().x;
		if (i == 1) length = obb.GetRadius().y;
		if (i == 2) length = obb.GetRadius().z;

		//	0�ȉ��Ȃ�v�Z�s�v
		if (length <= 0) continue;

		//	2�_�̋���
		Vector3 distance = sphere.GetCenter() - obb.GetLocalCenter();
		
		Vector3 axis;
		if (i == 0) axis = obb.GetLocalSeparationAxisX();
		if (i == 1) axis = obb.GetLocalSeparationAxisY();
		if (i == 2) axis = obb.GetLocalSeparationAxisZ();

		//	�͂ݏo���������̎Z�o(�����ƕ������̓���)
		float protrude = (distance.x * axis.x + distance.y * axis.y + distance.z * axis.z) / length;

		//	�͂ݏo������������Ȃ�
		//protrude = fabsf(protrude);
		// �����������ɉ����o��
		if (protrude > 1)
		{
			//	�͂ݏo�������̃x�N�g���Z�o
			if (i == 0) vec += ((1 - protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisX();
			if (i == 1) vec += ((1 - protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisY();
			if (i == 2) vec += ((1 - protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisZ();

			//if (i == 1)
			//{
			//	float A = 1 - protrude;
			//	A *= length;
			//	A += sphere.m_radius;
			//	Vector3 v = A * obb.GetLocalSeparationAxisY();
			//	vec += v;
			//}
		}
		// �������̋t�����ɉ����o��
		if (protrude < -1)
		{
			//	�͂ݏo�����̎Z�o
			if (i == 0) vec -= ((1 + protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisX();
			if (i == 1) vec -= ((1 + protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisY();
			if (i == 2) vec -= ((1 + protrude) * length + sphere.GetRadius()) * obb.GetLocalSeparationAxisZ();

			//if (i == 1)
			//{
			//	float A = 1 + protrude;
			//	A *= length;
			//	A += sphere.m_radius;
			//	Vector3 v = A * obb.GetLocalSeparationAxisY();
			//	vec -= v;
			//}
		}

		//if (protrude > 1)
		//{
		//	//	�͂ݏo�������̃x�N�g���Z�o
		//	if (i == 0) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisX();
		//	if (i == 1) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisY();
		//	if (i == 2) vec += (1 - protrude) * length * obb.GetLocalSeparationAxisZ();
		//}
		//if (protrude < -1)
		//{
		//	//	�͂ݏo�����̎Z�o
		//	if (i == 0) vec -= (1 + protrude) * length * obb.GetLocalSeparationAxisX();
		//	if (i == 1) vec -= (1 + protrude) * length * obb.GetLocalSeparationAxisY();
		//	if (i == 2) vec -= (1 + protrude) * length * obb.GetLocalSeparationAxisZ();
		//}

	}

	return vec;
}
