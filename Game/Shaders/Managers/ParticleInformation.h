//============================================================//
//*���@�O	ParticleInformation.h
//*���@�e	�p�[�e�B�N�����
//*���@�t	2018.7.18
//*�X�@�V	2018.7.20
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <vector>
#include <Windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <simplemath.h>
#include "VertexTypes.h"

class ParticleInformation
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;

public:
	ParticleInformation();
	void Update();

	//*�ݒ�֐�==========================================
	//	�e�N�X�`���ԍ��ݒ�
	void SetTextureSlot(int textureSlot);
	//	���W�ݒ�
	void SetPosition(Vector3 position);
	//	�Ō�̍��W�ݒ�
	void SetEndPosition(Vector3 position);
	//	���x�ݒ�
	void SetVelocity(Vector3 velocity);
	//	�F�ݒ�
	void SetColor(Vector4 color);
	//	�Ō�̐F�ݒ�
	void SetEndColor(Vector4 color);
	//	�傫���ݒ�
	void SetScale(float scale);
	//	�Ō�̑傫���ݒ�
	void SetEndScale(float scale);
	//	�p�x�ݒ�
	void SetRotation(float rotation);
	//	�Ō�̊p�x�ݒ�
	void SetEndRotation(float rotation);

	//	���Ŏ��Ԑݒ�
	void SetExtinctTime(float extinctTime);

	//*�擾�֐�==========================================
	//	�e�N�X�`���ԍ��擾
	int GetTextureSlot();
	//	���_�f�[�^�擾
	DirectX::VertexPositionColorTexture GetVertices();
	//	���W�擾
	Vector3 GetPosition();
	//	�Ō�̍��W�擾
	Vector3 GetEndPosition();
	//	���x�擾
	Vector3 GetVelocity();
	//	�F�擾
	Vector4 GetColor();
	//	�Ō�̐F�擾
	Vector4 GetEndColor();
	//	�傫���擾
	float GetScale();
	//	�Ō�̑傫���擾
	float GetEndScale();
	//	��]�p�x�̎擾
	float GetRotation();
	//	�Ō�̉�]�p�x�̎擾
	float GetEndRotation();
	//	���ݎ��Ԏ擾
	float GetNowTime();
	//	���Ŏ��Ԏ擾
	float GetExtinctTime();

private:
	//	�e�N�X�`���ԍ�
	int m_textureSlot;
	//	���_�f�[�^
	DirectX::VertexPositionColorTexture m_Vertices;
	//	���x
	Vector3 m_velocity;
	//	���ݎ���
	float m_nowTime;
	//	���Ŏ���
	float m_extinctTime;

	//	�Ō�̍��W
	Vector3 m_endPosition;
	//	�Ō�̐F
	DirectX::SimpleMath::Vector4 m_endColor;
	//	�Ō�̑傫��
	float m_endScale;
	//	�Ō�̉�]�p�x
	float m_endRotation;

};
