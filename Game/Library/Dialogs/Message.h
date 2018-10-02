//============================================================//
//*���@�O	Message.h
//*���@�e	���b�Z�[�W��\������
//*���@�t	2017.12.27
//*�X�@�V	2017.12.27
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <SpriteBatch.h>
#include "..\Devices\Devices.h"
#include <CommonStates.h>
#include <SpriteFont.h>
#include <string>

#include "..\Files\FileIO.h"
#include "FontImage.h"

class Message
{
public:
	Message();
	int Initialize();
	void Render();

	//	�e�L�X�g�̓Ǎ���
	//int LoadText(int line);
	//	�e�L�X�g�\��
	//int TextLine(FILE *f, std::wstring *line);

private:
	//	�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//	���b�Z�[�W�E�B���h�E�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_MesTexture;

	//	�t�H���g
	//std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	FileIO* m_fileInput;
	FontImage* m_fontImage;

	//	�s
	int m_line;

};
