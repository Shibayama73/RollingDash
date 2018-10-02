//============================================================//
//*名　前	FontImage.cpp
//*内　容	文字を文字コードに変換し表示する
//*日　付	2017.02.07
//*更　新	2017.02.07
//*制作者	N.Shibayama
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

	//	スプライトバッチ生成
	this->m_spriteBatch = std::make_unique<SpriteBatch>(devices.GetDeviceContext().Get());

	//	リソース読み込み
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/font_riipopkkr.png", resource.GetAddressOf(),
			m_MesTexture.ReleaseAndGetAddressOf()));

	return 0;
}

//	文字を登録
void FontImage::SetWord(wchar_t word[256])
{
	wcscpy(m_word, word);
}

//	文字コードと一致する文字画像を描画
void FontImage::DrowFont()
{
	auto& devices = Devices::GetInstance();

	//	テクスチャの描画
	CommonStates m_states(devices.GetDevice().Get());
	this->m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());

	//	文字切り取り用
	RECT rect;

	//	1行分の文字数取得
	int num = wcslen(m_word);

	//	1行分の文字を描画する
	for (int i = 1; i < num + 1; i++)
	{
		switch (m_word[i - 1])
		{
		case 12354:		//あ
			rect.top = 0;
			rect.left = 0;
			rect.right = 48;
			rect.bottom = 48;
			break;
		case 12356:		//い
			rect.top = 0;
			rect.left = 52;
			rect.right = 100;
			rect.bottom = 48;
			break;
		case 12358:		//う
			rect.top = 0;
			rect.left = 104;
			rect.right = 152;
			rect.bottom = 48;
			break;
		case 12360:		//え
			rect.top = 0;
			rect.left = 156;
			rect.right = 204;
			rect.bottom = 48;
			break;
		case 12362:		//お
			rect.top = 0;
			rect.left = 208;
			rect.right = 256;
			rect.bottom = 48;
			break;
		case 12363:		//か
			rect.top = 56;
			rect.left = 0;
			rect.right = 48;
			rect.bottom = 104;
			break;
		case 12365:		//き
			rect.top = 56;
			rect.left = 52;
			rect.right = 100;
			rect.bottom = 104;
			break;
		case 12367:		//く
			rect.top = 56;
			rect.left = 104;
			rect.right = 152;
			rect.bottom = 104;
			break;
		case 12369:		//け
			rect.top = 56;
			rect.left = 156;
			rect.right = 204;
			rect.bottom = 104;
			break;
		case 12371:		//こ
			rect.top = 56;
			rect.left = 208;
			rect.right = 256;
			rect.bottom = 104;
			break;
		case 12373:		//さ
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
