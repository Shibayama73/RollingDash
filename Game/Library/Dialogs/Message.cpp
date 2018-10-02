//============================================================//
//*���@�O	Message.cpp
//*���@�e	���b�Z�[�W��\������
//*���@�t	2017.12.27
//*�X�@�V	2017.12.27
//*�����	N.Shibayama
//============================================================//
#include "Message.h"
#include <WICTextureLoader.h>
#include <fstream>
#include <string>
#include "..\Keyboards\Keyboards.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace std;

Message::Message()
{
}

int Message::Initialize()
{
	auto& devices = Devices::GetInstance();

	//	�X�v���C�g�o�b�`����
	this->m_spriteBatch = std::make_unique<SpriteBatch>(devices.GetDeviceContext().Get());
	//	�t�H���g����
	//this->m_spriteFont = std::make_unique<SpriteFont>(devices.GetDevice().Get(), L"myfile.spritefont");

	//	���\�[�X�ǂݍ���
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/mesframe.png", resource.GetAddressOf(),
			m_MesTexture.ReleaseAndGetAddressOf()));

	//	�e�L�X�g�t�@�C�����̓o�^
	m_fileInput = new FileIO();
	m_fileInput->SetFileName("Text/text.txt");

	//	�t�H���g�摜�̏�����
	m_fontImage = new FontImage();
	m_fontImage->Initialize();

	//	�s��
	m_line = 0;

	return 0;
}

void Message::Render()
{
	auto& devices = Devices::GetInstance();

	//	�e�N�X�`���̕`��
	CommonStates m_states(devices.GetDevice().Get());
	this->m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());
	//	���b�Z�[�W�E�B���h
	this->m_spriteBatch->Draw(m_MesTexture.Get(), Vector2(30.0f, 600.0f), nullptr, Colors::White, 0.0f);
	this->m_spriteBatch->End();

	//	�L�[�{�[�h�̎擾
	auto& key = Keyboards::GetInstance();
	key.GetState();

	if (key.CheckPressed("L"))
	{
		//	�Ō�̍s�܂�
		if (m_line < m_fileInput->GetRow() - 1)
		{
			m_line += 1;	//	�s�̍X�V
		}
		//	�Ō�̍s�ɂȂ����Ƃ�
		else
		{
			m_fileInput->SetFileName("Text/text2.txt");
			m_line = 0;
		}
	}

	//wchar_t* a[256];
	//*a = m_fileInput->LoadText(m_line);

	//	�w�肳�ꂽ�s�̕�����o�^
	m_fontImage->SetWord(m_fileInput->LoadText(m_line));
	//	�t�H���g�̕\��
	m_fontImage->DrowFont();

}
//
//int Message::LoadText(int line)
//{
//	setlocale(LC_ALL, "japanese");
//
//	std::ifstream ifs("Text/text.txt");
//	char fileText[256];		//�t�@�C���Ǎ��ݗp
//	wchar_t text[256];		//�ǂݍ��񂾕�����\���ϊ��p
//
//	if (ifs.fail())
//	{
//		return -1;
//	}
//	//	�w�肳�ꂽ�s
//	for (int i = 0; i <= line; i++)
//	{
//		//	1�s�ǂݍ���
//		ifs.getline(fileText, 256 - 1);
//	}
//	//	�t�@�C������ǂݍ��񂾕����̕ϊ�(char����wchar_t�ɕϊ�)
//	mbstowcs(text, fileText, sizeof(fileText));		//text(decimal)
//
//	//	�\��
//	this->m_spriteBatch->Begin();
//	this->m_spriteFont->DrawString(m_spriteBatch.get(), text, SimpleMath::Vector2(50, 600), Colors::Black, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
//	this->m_spriteBatch->End();
//
//
//
//	////	1�s�ǂݍ���
//	//while (ifs.getline(fileText, 256 - 1))
//	//{
//	//	//wchar_t c = (wchar_t)cstr;	//�s�\
//
//	//	//	�t�@�C������ǂݍ��񂾕����̕ϊ�(char����wchar_t�ɕϊ�)
//	//	mbstowcs(text, fileText, sizeof(fileText));
//
//	//	this->m_spriteBatch->Begin();
//	//	this->m_spriteFont->DrawString(m_spriteBatch.get(), text, SimpleMath::Vector2(30, 600), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
//	//	//this->m_spriteFont->DrawString(m_spriteBatch.get(), L"TEST", SimpleMath::Vector2(30, 600), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
//	//	this->m_spriteBatch->End();
//	//}
//
//	return 0;
//}
//
//int Message::TextLine(FILE * f, std::wstring * line)
//{
//	return 0;
//}
