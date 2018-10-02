//============================================================//
//*���@�O	CubeStage.cpp
//*���@�e	�����̂̃X�e�[�W
//*���@�t	2018.6.27
//*�X�@�V	2018.6.27
//*�����	N.Shibayama
//============================================================//
#include "CubeStage.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	��]�l
const float CubeStage::ROTATE = 0.003f;
//	���a�l
const float CubeStage::RADIUS = 5.0f;

CubeStage::CubeStage()
{
}

CubeStage::~CubeStage()
{
}

void CubeStage::Initialize(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 sca)
{
	m_model.LoadModel(L"Resources/cubeStage.cmo");

	//	���W
//	const Vector3 pos(0.0f, -25.0f, 0.0f);	//def:(y)-5.0f
	const Vector3 position = pos;
	//	��]
	const Vector3 rot(0.0f, 0.0f, 0.0f);
	//const Vector3 rot(XM_PI, 0.0f, 0.0f);

	//	�X�P�[��
	//Vector3(5.0f, 5.0f, 5.0f)
	const Vector3 scale = sca;

	//	�����ʒu�̐ݒ�
	m_model.SetTranslation(position);
	m_model.SetScale(scale);	//def:1.0f
	m_model.SetRotation(rot);

	//	�����̂̓����蔻�菉����(OBB)
	m_obbNode.Initialize();
	m_obbNode.SetParent(&m_model);
	m_obbNode.SetLocalCenter(position);
	m_obbNode.SetRadius(scale * RADIUS);	//def:5.0f (radius=scale*5)
	m_obbNode.SetLocalRotation(rot);

	//	��]�p�x�̏�����
	m_rotation = 0.0f;
	//	��]�����t���O�̏�����
	m_isRot = false;
	//	�Փ˃t���O�̏�����
	m_isCollision = false;

}

void CubeStage::Update()
{
	m_model.Update();
	m_obbNode.Update();

	//	�Փ˂��Ă�����
	if(m_isCollision)
	{
		//	��]������ς���
		if (m_isRot) m_isRot = false;
		else m_isRot = true;
		m_isCollision = false;
	}

	//	��]�����ɉ�]������
	if (m_isRot) m_rotation -= ROTATE;
	else m_rotation += ROTATE;

	m_model.SetRotation(Vector3(0, 0, m_rotation));
	m_obbNode.SetLocalRotation(Vector3(0, 0, m_rotation));

}

void CubeStage::Draw()
{
	m_model.Draw();
	m_obbNode.Draw();
}

void CubeStage::OnCollision()
{
	m_isCollision = true;
}
