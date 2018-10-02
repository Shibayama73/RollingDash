//============================================================//
//*���@�O	Camera.h
//*���@�e	�J����
//*���@�t	2017.7.11
//*�X�@�V	2017.7.11
//*�����	N.Shibayama
//============================================================//
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

class Camera
{
public:
	Camera(int width, int height);
	virtual ~Camera();
	//	�X�V
	virtual void Update();
	//	�r���[�s��̎擾
	const DirectX::SimpleMath::Matrix& GetViewMatrix();
	//	�ˉe�s��̎擾
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix();
	//	���_���W�̃Z�b�g
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);
	//	�����_�E�Q�Ɠ_�Z�b�g
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);
	//	�J�����̌����̃Z�b�g
	void SetUpvec(const DirectX::SimpleMath::Vector3& upvec);
	//	������������p�̃Z�b�g
	void SetFovY(float fovY);
	//	�A�X�y�N�g��̃Z�b�g
	void SetAspect(float aspect);
	//	�j�A�N���b�v�̃Z�b�g
	void SetNearclip(float nearclip);
	//	�t�@�[�N���b�v�̃Z�b�g
	void SetFarclip(float farclip);

//	const DirectX::SimpleMath::Matrix& GetView() const { return m_view; }
//	const DirectX::SimpleMath::Matrix& GetProj() const { return m_proj; }

	const DirectX::SimpleMath::Matrix& GetBillboard() const { return m_billboard; }
	const DirectX::SimpleMath::Matrix& GetBillboardConstrainY() const { return m_billboardConstrainY; }

	// �r���{�[�h�s��̌v�Z
	void CalcBillboard();

protected:
	//	�J�����̈ʒu�i���_���W�j
	DirectX::SimpleMath::Vector3 m_eyepos;
	//	�J�����̌��Ă����i�����_�E�Q�Ɠ_�j
	DirectX::SimpleMath::Vector3 m_refpos;
	//	�J�����̏�����x�N�g��
	DirectX::SimpleMath::Vector3 m_upvec;
	//	�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	//	������������p
	float m_fovY;
	//	�A�X�y�N�g��i��ʔ䗦�j
	float m_aspect;
	//	�j�A�N���b�v�i��O�̕\�����E�����j
	float m_nearclip;
	//	�t�@�[�N���b�v�i���̕\�����E�����j
	float m_farclip;
	//	�ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;

	// �r���{�[�h�s��
	DirectX::SimpleMath::Matrix m_billboard;
	// �r���{�[�h�s��(Y���������j
	DirectX::SimpleMath::Matrix m_billboardConstrainY;

};