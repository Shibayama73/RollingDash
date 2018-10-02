//============================================================//
//*���@�O	FontImage.cpp
//*���@�e	�����𕶎��R�[�h�ɕϊ����\������
//*���@�t	2017.02.07
//*�X�@�V	2017.02.07
//*�����	N.Shibayama
//============================================================//
#include "FontImage.h"
#include <WICTextureLoader.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace std;

FontImage::FontImage()
{
}

int FontImage::Initialize()
{
	auto& devices = Devices::GetInstance();

	//	�X�v���C�g�o�b�`����
	this->m_spriteBatch = std::make_unique<SpriteBatch>(devices.GetDeviceContext().Get());

	//	���\�[�X�ǂݍ���
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/font_riipopkkr.png", resource.GetAddressOf(),
			m_MesTexture.ReleaseAndGetAddressOf()));

	return 0;
}

//	������o�^
void FontImage::SetWord(wchar_t word[256])
{
	wcscpy(m_word, word);
}

//	�����R�[�h�ƈ�v���镶���摜��`��
void FontImage::DrowFont()
{
	auto& devices = Devices::GetInstance();

	//	�e�N�X�`���̕`��
	CommonStates m_states(devices.GetDevice().Get());
	this->m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());

	//	�����؂���p
	RECT rect;

	//	1�s���̕������擾
	int num = wcslen(m_word);

	//	1�s���̕�����`�悷��
	for (int i = 1; i < num + 1; i++)
	{
		switch (m_word[i - 1])
		{
		case 12354:		//��
			rect.top = 0;
			rect.left = 0;
			rect.right = 48;
			rect.bottom = 48;
			break;
		case 12356:		//��
			rect.top = 0;
			rect.left = 52;
			rect.right = 100;
			rect.bottom = 48;
			break;
		case 12358:		//��
			rect.top = 0;
			rect.left = 104;
			rect.right = 152;
			rect.bottom = 48;
			break;
		case 12360:		//��
			rect.top = 0;
			rect.left = 156;
			rect.right = 204;
			rect.bottom = 48;
			break;
		case 12362:		//��
			rect.top = 0;
			rect.left = 208;
			rect.right = 256;
			rect.bottom = 48;
			break;
		case 12363:		//��
			rect.top = 56;
			rect.left = 0;
			rect.right = 48;
			rect.bottom = 104;
			break;
		case 12365:		//��
			rect.top = 56;
			rect.left = 52;
			rect.right = 100;
			rect.bottom = 104;
			break;
		case 12367:		//��
			rect.top = 56;
			rect.left = 104;
			rect.right = 152;
			rect.bottom = 104;
			break;
		case 12369:		//��
			rect.top = 56;
			rect.left = 156;
			rect.right = 204;
			rect.bottom = 104;
			break;
		case 12371:		//��
			rect.top = 56;
			rect.left = 208;
			rect.right = 256;
			rect.bottom = 104;
			break;
		case 12373:		//��
			rect.top = 112;
			rect.left = 0;
			rect.right = 48;
			rect.bottom = 160;
			break;
		default:
			rect.top = 0;
			rect.left = 0;
			rect.right = 0;
			rect.bottom = 0;
			break;
		}

		this->m_spriteBatch->Draw(m_MesTexture.Get(), Vector2(60.0f * i / 1.2f, 620.0f), &rect, Colors::White, 0.0f);
	}
	this->m_spriteBatch->End();

}
