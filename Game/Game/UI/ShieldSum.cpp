//============================================================//
//*名　前	ShieldSum.cpp
//*内　容	シールドの数画像の表示
//*日　付	2018.7.02
//*更　新	2018.7.02
//*制作者	N.Shibayama
//============================================================//
#include "..\..\Library\Framework\pch.h"
#include "ShieldSum.h"
#include <CommonStates.h>
#include <WICTextureLoader.h>
#include "..\..\Library\Devices\Devices.h"
#include <string>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

//	表示座標
const float ShieldSum::NOW_POS_X = 30.0f;
const float ShieldSum::NOW_POS_Y = 20.0f;
const float ShieldSum::SLASH_POS_X = 80.0f;
const float ShieldSum::SLASH_POS_Y = 20.0f;
const float ShieldSum::MAX_POS_X = 140.0f;
const float ShieldSum::MAX_POS_Y = 20.0f;

void ShieldSum::Initialize()
{
	auto& devices = Devices::GetInstance();

	//	リソース読み込み
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/shield.png", resource.GetAddressOf(),
			m_shieldTex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/slash.png", resource.GetAddressOf(),
			m_slashTex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/numbers.png", resource.GetAddressOf(),
			m_limitTex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/numbers.png", resource.GetAddressOf(),
			m_maxTex.ReleaseAndGetAddressOf()));

}

void ShieldSum::Draw(std::unique_ptr<DirectX::SpriteBatch>& spriteBatch, int now_sum, int max)
{
	auto& devices = Devices::GetInstance();

	CommonStates states(devices.GetDevice().Get());
	spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	spriteBatch->Draw(m_shieldTex.Get(), Vector2(0.0f, 0.0f), nullptr, Colors::White, 0.0f, Vector2(0, 0), 0.8f);
	spriteBatch->Draw(m_slashTex.Get(), Vector2(SLASH_POS_X, SLASH_POS_Y), nullptr, Colors::DeepSkyBlue, 0.0f, Vector2(0, 0), 1.5f);

	//	表示する数
	RECT rect;
	rect.top = 0;
	rect.bottom = 30;

	//	最大数
	int sum = max;
	for (int i = 0; i <= sum; i++)
	{
		rect.left = ((int)sum % 10) * 30;
		rect.right = ((int)sum % 10) * 30 + 30;
		spriteBatch->Draw(m_maxTex.Get(), Vector2(MAX_POS_X, MAX_POS_Y), &rect, Colors::DeepSkyBlue, 0.0f, Vector2(0, 0), 1.5f);
	}

	//	桁数
	int now = now_sum;
	//	桁数分表示
	for (int i = 0; i <= now; i++)
	{
		rect.left = ((int)now % 10) * 30;
		rect.right = ((int)now % 10) * 30 + 30;

		//	テクスチャの描画
		spriteBatch->Draw(m_limitTex.Get(), Vector2(NOW_POS_X, NOW_POS_Y), &rect, Colors::DeepSkyBlue, 0.0f, Vector2(0, 0), 1.5f);
	}
	spriteBatch->End();
}
