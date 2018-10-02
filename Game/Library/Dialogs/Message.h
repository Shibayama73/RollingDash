//============================================================//
//*名　前	Message.h
//*内　容	メッセージを表示する
//*日　付	2017.12.27
//*更　新	2017.12.27
//*制作者	N.Shibayama
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

	//	テキストの読込み
	//int LoadText(int line);
	//	テキスト表示
	//int TextLine(FILE *f, std::wstring *line);

private:
	//	スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//	メッセージウィンドウテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_MesTexture;

	//	フォント
	//std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	FileIO* m_fileInput;
	FontImage* m_fontImage;

	//	行
	int m_line;

};
