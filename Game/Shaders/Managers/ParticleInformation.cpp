//============================================================//
//*���@�O	ParticleInformation.cpp
//*���@�e	�p�[�e�B�N�����
//*���@�t	2018.7.18
//*�X�@�V	2018.7.20
//*�����	N.Shibayama
//============================================================//
#include "ParticleInformation.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

ParticleInformation::ParticleInformation()
{
	m_Vertices.position = Vector3(0, 0, 0);
	m_Vertices.color = Vector4(255, 255, 255, 1);
	m_Vertices.textureCoordinate.x = float(1.0f);
	m_Vertices.textureCoordinate.y = float(0.0f);
	m_nowTime = 0.0f;
	m_extinctTime = 0.0f;

}

void ParticleInformation::Update()
{
	//	���ԍX�V(1�t���[������)
	m_nowTime++;

	//	���x�ɂ��ړ�
	m_Vertices.position.x += m_velocity.x;
	m_Vertices.position.y += m_velocity.y;
	m_Vertices.position.z += m_velocity.z;

}
//*�ݒ�֐�============================================================
//	�e�N�X�`���ԍ��ݒ�
void ParticleInformation::SetTextureSlot(int textureSlot)
{
	m_textureSlot = textureSlot;
}

//	���W�ݒ�
void ParticleInformation::SetPosition(DirectX::SimpleMath::Vector3 postion)
{
	m_Vertices.position = postion;
}

//	�Ō�̍��W�ݒ�
void ParticleInformation::SetEndPosition(Vector3 position)
{
	m_endPosition = position;
}

//	���x�ݒ�
void ParticleInformation::SetVelocity(Vector3 velocity)
{
	m_velocity = velocity;
}

//	�F�ݒ�
void ParticleInformation::SetColor(DirectX::SimpleMath::Vector4 color)
{
	m_Vertices.color = color;
}

//	�Ō�̐F�ݒ�
void ParticleInformation::SetEndColor(Vector4 color)
{
	m_endColor = color;
}

//	�傫���ݒ�
void ParticleInformation::SetScale(float scale)
{
	m_Vertices.textureCoordinate.x = scale;
}

//	�Ō�̑傫���擾
void ParticleInformation::SetEndScale(float scale)
{
	m_endScale = scale;
}

//	�p�x�ݒ�
void ParticleInformation::SetRotation(float rotation)
{
	m_Vertices.textureCoordinate.y = rotation;
}

//	�Ō�̊p�x�ݒ�
void ParticleInformation::SetEndRotation(float rotation)
{
	m_endRotation = rotation;
}

//	���Ŏ��Ԑݒ�
void ParticleInformation::SetExtinctTime(float extinctTime)
{
	m_extinctTime = extinctTime;
}

//*�擾�֐�============================================================
//	�e�N�X�`���ԍ��擾
int ParticleInformation::GetTextureSlot()
{
	return m_textureSlot;
}

//	���_�f�[�^�擾
DirectX::VertexPositionColorTexture ParticleInformation::GetVertices()
{
	return m_Vertices;
}

//	���W�擾information
Vector3 ParticleInformation::GetPosition()
{
	return m_Vertices.position;
}

//	�Ō�̍��W�擾
Vector3 ParticleInformation::GetEndPosition()
{
	return m_endPosition;
}

//	���x�擾
Vector3 ParticleInformation::GetVelocity()
{
	return m_velocity;
}

//	�F�擾
Vector4 ParticleInformation::GetColor()
{
	return m_Vertices.color;
}

//	�Ō�̐F�擾
Vector4 ParticleInformation::GetEndColor()
{
	return m_endColor;
}

//	�傫���擾
float ParticleInformation::GetScale()
{
	return m_Vertices.textureCoordinate.x;
}

//	�Ō�̑傫���擾
float ParticleInformation::GetEndScale()
{
	return m_endScale;
}

//	��]�p�x�̎擾
float ParticleInformation::GetRotation()
{
	return m_Vertices.textureCoordinate.y;
}

//	�Ō�̉�]�p�x�̎擾
float ParticleInformation::GetEndRotation()
{
	return m_endRotation;
}

//	���ݎ��Ԏ擾
float ParticleInformation::GetNowTime()
{
	return m_nowTime;
}

//	���Ŏ��Ԏ擾
float ParticleInformation::GetExtinctTime()
{
	return m_extinctTime;
}
