//============================================================//
//*名　前	Message.cpp
//*内　容	メッセージを表示する
//*日　付	2017.12.27
//*更　新	2017.12.27
//*制作者	N.Shibayama
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

	//	スプライトバッチ生成
	this->m_spriteBatch = std::make_unique<SpriteBatch>(devices.GetDeviceContext().Get());
	//	フォント生成
	//this->m_spriteFont = std::make_unique<SpriteFont>(devices.GetDevice().Get(), L"myfile.spritefont");

	//	リソース読み込み
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/mesframe.png", resource.GetAddressOf(),
			m_MesTexture.ReleaseAndGetAddressOf()));

	//	テキストファイル名の登録
	m_fileInput = new FileIO();
	m_fileInput->SetFileName("Text/text.txt");

	//	フォント画像の初期化
	m_fontImage = new FontImage();
	m_fontImage->Initialize();

	//	行数
	m_line = 0;

	return 0;
}

void Message::Render()
{
	auto& devices = Devices::GetInstance();

	//	テクスチャの描画
	CommonStates m_states(devices.GetDevice().Get());
	this->m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());
	//	メッセージウィンド
	this->m_spriteBatch->Draw(m_MesTexture.Get(), Vector2(30.0f, 600.0f), nullptr, Colors::White, 0.0f);
	this->m_spriteBatch->End();

	//	キーボードの取得
	auto& key = Keyboards::GetInstance();
	key.GetState();

	if (key.CheckPressed("L"))
	{
		//	最後の行まで
		if (m_line < m_fileInput->GetRow() - 1)
		{
			m_line += 1;	//	行の更新
		}
		//	最後の行になったとき
		else
		{
			m_fileInput->SetFileName("Text/text2.txt");
			m_line = 0;
		}
	}

	//wchar_t* a[256];
	//*a = m_fileInput->LoadText(m_line);

	//	指定された行の文字を登録
	m_fontImage->SetWord(m_fileInput->LoadText(m_line));
	//	フォントの表示
	m_fontImage->DrowFont();

}
//
//int Message::LoadText(int line)
//{
//	setlocale(LC_ALL, "japanese");
//
//	std::ifstream ifs("Text/text.txt");
//	char fileText[256];		//ファイル読込み用
//	wchar_t text[256];		//読み込んだ文字を表示変換用
//
//	if (ifs.fail())
//	{
//		return -1;
//	}
//	//	指定された行
//	for (int i = 0; i <= line; i++)
//	{
//		//	1行読み込み
//		ifs.getline(fileText, 256 - 1);
//	}
//	//	ファイルから読み込んだ文字の変換(charからwchar_tに変換)
//	mbstowcs(text, fileText, sizeof(fileText));		//text(decimal)
//
//	//	表示
//	this->m_spriteBatch->Begin();
//	this->m_spriteFont->DrawString(m_spriteBatch.get(), text, SimpleMath::Vector2(50, 600), Colors::Black, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
//	this->m_spriteBatch->End();
//
//
//
//	////	1行読み込み
//	//while (ifs.getline(fileText, 256 - 1))
//	//{
//	//	//wchar_t c = (wchar_t)cstr;	//不可能
//
//	//	//	ファイルから読み込んだ文字の変換(charからwchar_tに変換)
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
