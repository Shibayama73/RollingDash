//============================================================//
//*���@�O	ShieldSum.h
//*���@�e	�V�[���h�̐��摜�̕\��
//*���@�t	2018.7.02
//*�X�@�V	2018.7.02
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <SpriteBatch.h>
#include <simplemath.h>

class ShieldSum
{
private:
	//	�\�����W
	static const float NOW_POS_X;	//���݂̃V�[���h
	static const float NOW_POS_Y;	//���݂̃V�[���h
	static const float MAX_POS_X;	//�ő�̃V�[���h
	static const float MAX_POS_Y;	//�ő�̃V�[���h
	static const float SLASH_POS_X;	//�ΐ�
	static const float SLASH_POS_Y;	//�ΐ�

public:
	void Initialize();
	void Draw(std::unique_ptr<DirectX::SpriteBatch>& spriteBatch, int now_sum, int max);

private:
	//	�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shieldTex;	//�V�[���h�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_slashTex;	//�ΐ�
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_limitTex;	//���݂̃V�[���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_maxTex;		//�V�[���h�ő吔

};