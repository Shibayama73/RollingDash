//============================================================//
//*名　前	FontImage.h
//*内　容	文字を文字コードに変換し表示する
//*日　付	2017.02.07
//*更　新	2017.02.07
//*制作者	N.Shibayama
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

	//	文字を登録
	void SetWord(wchar_t word[256]);
	//	文字コードと一致する文字画像を描画
	void DrowFont();

private:
	//	スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//	メッセージウィンドウテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_MesTexture;

	//	文字
	wchar_t m_word[256];


};
