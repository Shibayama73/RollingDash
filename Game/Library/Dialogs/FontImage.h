//============================================================//
//*���@�O	FontImage.h
//*���@�e	�����𕶎��R�[�h�ɕϊ����\������
//*���@�t	2017.02.07
//*�X�@�V	2017.02.07
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <SpriteBatch.h>
#include "..\Devices\Devices.h"
#include <CommonStates.h>

class FontImage
{
public:
	FontImage();
	int Initialize();

	//	������o�^
	void SetWord(wchar_t word[256]);
	//	�����R�[�h�ƈ�v���镶���摜��`��
	void DrowFont();

private:
	//	�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//	���b�Z�[�W�E�B���h�E�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_MesTexture;

	//	����
	wchar_t m_word[256];


};
