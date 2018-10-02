//============================================================//
//*���@�O	Player.cpp
//*���@�e	�v���C���[
//*���@�t	2018.5.22
//*�X�@�V	2018.7.23
//*�����	N.Shibayama
//============================================================//
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void Player::Initialize()
{
	//	���@���f���̏�����
	this->m_model.LoadModel(L"Resources/sphereP.cmo");
	this->m_model.SetTranslation(Vector3(0.0f, 5.0f, 0.0f));
	this->m_model.SetScale(Vector3(1, 1, 1));
	this->m_model.SetRotation(Vector3(0, 0, 0));

	//	���@�̓����蔻�菉����
	this->m_collisionNode.Initialize();
	this->m_collisionNode.SetParent(&m_model);
	this->m_collisionNode.SetLocalRadius(1.2f);

	m_isCollision = false;

}

void Player::Update()
{
	//	�L�[�{�[�h�擾
	auto& key = Keyboards::GetInstance();
	key.GetState();

	//	���@
	this->m_model.Update();
	//	���@�̓����蔻��m�[�h
	this->m_collisionNode.Update();

	//	�d�͂�������
	this->Gravity();

	if(m_isCollision)
	{
		//	W�L�[��������Ă�Ƃ��O�i
		if (key.CheckKey("W"))
		{
			this->Forward();
		}
		//	S�L�[��������Ă�Ƃ����
		if (key.CheckKey("S"))
		{
			this->Backward();
		}
		//	A�L�[��������Ă�Ƃ�������
		if (key.CheckKey("A"))
		{
			this->LeftTurn();
		}
		//	D�L�[��������Ă�Ƃ��E����
		if (key.CheckKey("D"))
		{
			this->RightTurn();
		}
	}

#ifdef _DEBUG
	//	�f�o�b�O�p(Y)
	//{
	//	if (key.CheckKey("X"))
	//	{
	//		//	�ړ��x�N�g��(Z���W�O�i)
	//		Vector3 moveV(0, -REBOUND, 0);
	//		//	��]
	//		float angle = m_model.GetRotation().y;
	//		Matrix rotmat = Matrix::CreateRotationY(angle);
	//		//	�ړ��x�N�g�������@�̊p�x����]������
	//		moveV = Vector3::TransformNormal(moveV, rotmat);
	//		Vector3 pos = m_model.GetTranslation();
	//		m_model.SetTranslation(pos + moveV);

	//	}
	//	if (key.CheckKey("Z"))
	//	{
	//		//	�ړ��x�N�g��(Z���W�O�i)
	//		Vector3 moveV(0, REBOUND, 0);
	//		//	��]
	//		float angle = m_model.GetRotation().y;
	//		Matrix rotmat = Matrix::CreateRotationY(angle);
	//		//	�ړ��x�N�g�������@�̊p�x����]������
	//		moveV = Vector3::TransformNormal(moveV, rotmat);
	//		Vector3 pos = m_model.GetTranslation();
	//		m_model.SetTranslation(pos + moveV);

	//	}
	//}
#endif

}

void Player::Draw()
{
	//	���@�̕`��
	this->m_model.Draw();
	//	���@�̓����蔻��m�[�h���f���̕\��
	//this->m_collisionNode.Draw();

}

//	���@��OBB�������������ǂ���
bool Player::IsOBBCollision(OBBNode & obb)
{
	//	OBB�Ǝ��@�Ƃ̓����蔻��
	OBB2SphereCollision obb2sphereCollition;
	//	OBB�Ɠ������Ă���Ƃ�
	if (obb2sphereCollition.IsOBB2SphereCollision(obb, m_collisionNode)) return true;
	return false;
}

//	�O�i
void Player::Forward()
{
	//	�ړ��x�N�g��(Z���W�O�i)
	Vector3 moveV(0, 0, -FORWARD_Z);
	//	��]
	Vector3 angle = m_model.GetRotation();
	angle.x -= 0.1f;
	m_model.SetRotation(angle);
	Matrix rotmat = Matrix::CreateRotationY(angle.y);
	//	�ړ��x�N�g�������@�̊p�x����]������
	moveV = Vector3::TransformNormal(moveV, rotmat);
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + moveV);

}

//	���
void Player::Backward()
{
	//	�ړ��x�N�g��(Z���W���)
	Vector3 moveV(0, 0, BACKWARD_Z);
	//	��]
	Vector3 angle = m_model.GetRotation();
	angle.x += 0.1f;
	m_model.SetRotation(angle);
	Matrix rotmat = Matrix::CreateRotationY(angle.y);
	//	�ړ��x�N�g�������@�̊p�x����]������
	moveV = Vector3::TransformNormal(moveV, rotmat);
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + moveV);

}

//	������
void Player::LeftTurn()
{
	//	���ɐ��񂷂�
	Vector3 angle = m_model.GetRotation();
	angle.y += LEFTTURN_Y;
	m_model.SetRotation(angle);
}

//	�E����
void Player::RightTurn()
{
	//	�E�ɐ��񂷂�
	Vector3 angle = m_model.GetRotation();
	angle.y -= LEFTTURN_Y;
	m_model.SetRotation(angle);
}

//	OBB�I�u�W�F�N�g�ƏՓ˂��Ă�����߂荞�ݖ߂�������
void Player::ObbColSinkRestore(OBBNode & obb)
{
	//	�n�ʂƓ������Ă���Ƃ�
	if (this->IsOBBCollision(obb))
	{
		//	�߂荞�ݖ߂�
		this->SinkRestore(obb);
	}
}

//	�X�e�[�W�ƏՓ˂��Ă�����߂荞�ݖ߂�������
void Player::StageColSinkRestore(CubeStage & stage)
{
	//	�n�ʂƓ������Ă���Ƃ�
	if (this->IsOBBCollision(stage.m_obbNode))
	{
		m_isCollision = true;

		//	�߂荞�ݖ߂�
		this->SinkRestore(stage.m_obbNode);
	}
	else m_isCollision = false;
}

//	�n��(OBB)�Ƃ̂߂荞�ݕ��߂�
void Player::SinkRestore(OBBNode& obb)
{
	//	�����̂ƓG�Ƃ̓����蔻��
	OBB2SphereCollision obb2sphereCollition;
	//	�߂荞�񂾒���
	Vector3 length = obb2sphereCollition.GetCalDistance(obb, m_collisionNode);

	//	�ړ��x�N�g�������@�̊p�x����]������
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + length);

}

//	�V�[���h�ƏՓ˂��Ă�����߂荞�ݖ߂�������
void Player::ShieldColSinkRestore(OBBNode & obb)
{
	//	�n�ʂƓ������Ă���Ƃ�
	if (this->IsOBBCollision(obb))
	{
		m_isCollision = true;

		//	�߂荞�ݖ߂�
		this->ShieldSinkRestore(obb);
	}

}

//	�V�[���h�Ƃ̂߂荞�ݕ��߂�
void Player::ShieldSinkRestore(OBBNode & obb)
{
	//	�����̂ƓG�Ƃ̓����蔻��
	OBB2SphereCollision obb2sphereCollition;
	//	�߂荞�񂾒���
	Vector3 length = obb2sphereCollition.GetCalDistance(obb, m_collisionNode);

	//	������ɂ߂荞�ݕԂ�
	float x = std::fabs(length.x);
	float y = std::fabs(length.y);
	float z = std::fabs(length.z);

	//	�ړ��x�N�g�������@�̊p�x����]������
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + Vector3(x, y, z));

}

//	�d�͂�������
void Player::Gravity()
{
	//	��]
	float angle = m_model.GetRotation().y;
	Matrix rotmat = Matrix::CreateRotationY(angle);
	//	�ړ��x�N�g�������@�̊p�x����]������
	Vector3 move = Vector3::TransformNormal(GRAVITY, rotmat);
	Vector3 pos = m_model.GetTranslation();
	m_model.SetTranslation(pos + move);

}

//	�Q�[���I�[�o�[�G���A���z���邩�ǂ���
bool Player::IsAreaOver(OBBNode& obb)
{
	Vector3 pos = m_model.GetTranslation();

	//	�X�e�[�W�ɓ������Ă��Ȃ��Ƃ�
	if (!this->IsOBBCollision(obb))
	{
		Vector3 min = obb.GetLocalCenter() - obb.GetRadius();
		Vector3 max = obb.GetLocalCenter() + obb.GetRadius();

		//	�Q�[���I�[�o�[�G���A�ɂ�����
		if (pos.x <= min.x || pos.x >= max.x ||
			pos.y <= min.y ||
			pos.z <= min.z || pos.z >= max.z)
		{
			return true;
		}
	}
	return false;
}

//	������g�p��~����
void Player::StopControl()
{
	m_isCollision = false;
}
