//============================================================//
//*���@�O	Enemy.cpp
//*���@�e	�G
//*���@�t	2017.7.03
//*�X�@�V	2017.7.03
//*�����	N.Shibayama
//============================================================//
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

//	�߂荞�ݒ��˕Ԃ�l
const float Enemy::REBOUND = 0.01f;
//	�ړ��\�ő�l
const float Enemy::MOVE_MAX = 25.0f;
//	�ړ��\�ŏ��l
const float Enemy::MOVE_MIN = -25.0f;
//	�d�͒l
const Vector3 Enemy::GRAVITY = Vector3(0.0f, 0.0098f, 0.0f);
//	�����l
const float Enemy::DAMPIND = 0.95f;
//	����
//const float Enemy::HALF = 0.5f;
const float Enemy::HALF = 0.75f;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	//	�������W
	Vector3 pos = Vector3(GetRandomRange(-20.0f, 20.0f), 30.0f, GetRandomRange(-20.0f, 20.0f));

	//	���f���̏�����
	this->m_model.LoadModel(L"Resources/sphereE.cmo");
	this->m_model.SetTranslation(pos);
	this->m_model.SetScale(Vector3(1, 1, 1));
	this->m_model.SetRotation(Vector3(0, 0, 0));

	//	�G�̓����蔻�菉����
	this->m_collisionNode.Initialize();
	this->m_collisionNode.SetParent(&m_model);
	this->m_collisionNode.SetLocalRadius(1.2f);

	//	������
	m_time = 0;
	m_speed = Vector3(0.0f, 0.0f, 0.0f);
	m_bound = true;

}

void Enemy::Update(const SphereNode& sphereNode)
{
	//	���@�I�u�W�F�N�g�̍X�V
	this->m_model.Update();
	//	�G�̓����蔻��m�[�h
	this->m_collisionNode.Update();

	//	�o�E���h����
	//this->Bound(obb);

	////	�n�ʂƓ������Ă���Ƃ�
	//OBB2SphereCollision obb2sphereCollition;
	//if (obb2sphereCollition.IsOBB2SphereCollision(obb, m_collisionNode))
	//{
	//	//	�o�E���h����
	//	this->SinkRestore(obb);
	//}

	//	�d�͂�������
	//this->Gravity();

	//	�v���C���[�ƏՓ˂����Ƃ�
	SphereCollision sphereCollision;
	if (sphereCollision.CheckSphere2Sphere(m_collisionNode, sphereNode))
	{
		this->Initialize();
	}

	////	�v���C���[���n�[�g�������Ă�����
	//if (playerHaveHeart)
	//{
	//	//	��������
	//	this->Escape(playerPos);
	//}
	//else
	//{
	//	//	�ǐՂ���
	//	this->Chase(playerPos);
	//}

}

void Enemy::Draw()
{
	m_model.Draw();

	//	�G�̓����蔻��m�[�h
	//this->m_collisionNode.Draw();
}

//	�͈͕��̗���
float Enemy::GetRandomRange(float min, float max)
{
	float random = (float)rand() / RAND_MAX;
	random = min + (max - min)*random;
	return random;
}

//	�G��OBB�������������ǂ���
bool Enemy::IsOBBCollision(OBBNode & obb)
{
	//	�����̂ƓG�Ƃ̓����蔻��
	OBB2SphereCollision obb2sphereCollition;
	if (obb2sphereCollition.IsOBB2SphereCollision(obb, m_collisionNode)) return true;
	return false;
}

////	�o�E���h����
//void Enemy::Bound(OBBNode & obb)
//{
//	m_speed -= GRAVITY;
//	Vector3 pos = m_model.GetTranslation();
//
//	//	�n�ʂƓ������Ă���Ƃ�
//	OBB2SphereCollision obb2sphereCollition;
//	if (obb2sphereCollition.IsOBB2SphereCollision(obb, m_collisionNode))
//	{
//		//	�߂荞�񂾒����������グ��
//		Vector3 length = obb2sphereCollition.GetCalDistance(obb, m_collisionNode);
//		//pos.y += length.y;
//		pos += length;
//
//		//	���x����������
//		//m_speed.y = (-m_speed.y * DAMPIND) * HALF;
//		m_speed = (-m_speed * DAMPIND) * HALF;
//	}
//	pos += m_speed;
//
//	m_model.SetTranslation(pos);
//	//m_position += pos;
//
//}

//	�o�E���h����
void Enemy::Bound(OBBNode & obb)
{
	//	�G��OBB���Փ˂�����
	if (this->IsOBBCollision(obb))
	{
		//	�߂荞�񂾒���
		OBB2SphereCollision obb2sphereCollition;
		Vector3 length = obb2sphereCollition.GetCalDistance(obb, m_collisionNode);
		length *= 2.0f;

		//	���˕Ԃ肪��������܂�
		if (m_speed.y < -0.5f && m_bound == true)
			//	���x�𔽓]������
			m_speed.y = (-m_speed.y * DAMPIND) * HALF;
		else
			m_bound = false;

		//	�ړ�������
		Vector3 pos = m_model.GetTranslation();
		m_model.SetTranslation(pos + length);
		//m_position += length;
	}

}

//	�d�͂�������
void Enemy::Gravity()
{
	m_speed -= GRAVITY;

	//	��]
	//float angle = m_model.GetRotation().y;
	//Matrix rotmat = Matrix::CreateRotationY(angle);
	//	�ړ��x�N�g�������@�̊p�x����]������
	//Vector3 move = Vector3::TransformNormal(GRAVITY, rotmat);
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + m_speed);
	//m_position += move;

}

////	��������
//void Enemy::Escape(DirectX::SimpleMath::Vector3 targetPos)
//{
//	//	�ړ��x�N�g��
//	Vector3 moveV(-1.5f, -1.5f, -1.5f);
//	//	�v���C���[�Ƃ̋���
//	Vector3 distance = targetPos - m_position;
//	distance.Normalize();
//	//	����������W�̌v�Z
//	m_position += distance * moveV * m_time;
//
//	//	�ړ��\�͈͓��ňړ�
//	m_position.x = this->MovePossibleRange(m_position.x);
//	m_position.z = this->MovePossibleRange(m_position.z);
//
//	m_model.SetTranslation(m_position);
//	m_time += 0.0003f;
//
//}
//
////	�ǐՂ���
//void Enemy::Chase(DirectX::SimpleMath::Vector3 targetPos)
//{
//	//	�ړ��x�N�g��
//	Vector3 moveV(1.5f, 1.5f, 1.5f);
//	//	�v���C���[�Ƃ̋���
//	Vector3 distance = targetPos - m_position;
//	distance.Normalize();
//	//	�ǐՂ�����W�̌v�Z
//	m_position += distance * moveV * m_time;
//
//	//	�ړ��\�͈͓��ňړ�
//	m_position.x = this->MovePossibleRange(m_position.x);
//	m_position.z = this->MovePossibleRange(m_position.z);
//
//	m_model.SetTranslation(m_position);
//	m_time += 0.00001f;
//}
//
////�ړ��\�͈͓��ł̈ړ�
//float Enemy::MovePossibleRange(float pos)
//{
//	float position = pos;
//	if (position < MOVE_MIN)
//	{
//		position = MOVE_MIN;
//	}
//	else if (position > MOVE_MAX)
//	{
//		position = MOVE_MAX;
//	}
//	return position;
//}
