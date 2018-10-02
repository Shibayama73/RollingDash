//============================================================//
//*���@�O	ParticleEffectManager.h
//*���@�e	�p�[�e�B�N���G�t�F�N�g���Ǘ�����
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
#include <PrimitiveBatch.h>
#include <CommonStates.h>
#include <map>
#include "VertexTypes.h"
#include "..\..\Library\Devices\Devices.h"
#include "..\..\Library\Camera\Camera.h"
#include "ParticleInformation.h"

class ParticleEffectManager
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;

	//	�p�[�e�B�N���̍ő吔
	static const int PARTICLE_NUM_MUX;
	//	���̓��C�A�E�g�̒�`
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//	�R���X�^���g�o�b�t�@
	struct Constants {
		//	���[���h�r���[�v���W�F�N�V���������s��
		DirectX::SimpleMath::Matrix WVP;
		//	�r���{�[�h�s��
		DirectX::SimpleMath::Matrix Billboard;
	};
	//	�_�̐�
	static const int POINT_NUM;

	//	�C���X�^���X�擾
	static ParticleEffectManager* GetInstance();

	//	������
	void Initialize();
	//	�X�V
	void Update();
	//	�`��
	void Draw();

	//	�e�N�X�`���Ǎ���
	void Load(int texnumber, const wchar_t* filename);

	//	�p�[�e�B�N���̓o�^(�e�N�X�`���ԍ��A���W�A�Ō�̍��W�A���x�A�F�A�Ō�̐F�A�傫���A�Ō�̑傫���A��]�p�x�A�Ō�̉�]�p�x�A���Ŏ���)
	void Entry(
		int textureSlot,
		Vector3 pos, Vector3 endPos,
		Vector3 velocity,
		Vector4 color, Vector4 endColor,
		float scale, float endScale,
		float rotation, float endRotation,
		float extinctTime
	);

	//	�A�N�Z�b�T
	void SetCamera(Camera* camera) { m_Camera = camera; }

protected:
	//	���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	//	�W�I���g���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;
	//	�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_PrimitiveBatch;
	//	���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	//	�ėp�`��ݒ�
	std::unique_ptr<DirectX::CommonStates> m_CommonStates;
	//	�R���X�^���g�o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;
	//	�e�N�X�`��
	std::map<int, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_Texture;
	//	�e�N�X�`���T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
	// ���Z�`��p�̃u�����h�X�e�[�g
	ID3D11BlendState* s_pBlendState;

	// �f�o�b�O�J����
	Camera* m_Camera;
	//	�p�[�e�B�N�����z��
	std::vector<ParticleInformation> m_ParticleInfo;
	//	�e�N�X�`���ԍ�
	int m_TextureSlot;

};
