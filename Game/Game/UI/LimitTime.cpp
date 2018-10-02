//============================================================//
//*名　前	LimitTime.cpp
//*内　容	制限時間
//*日　付	2017.7.28
//*更　新	2017.7.28
//*制作者	N.Shibayama
//============================================================//
#include "..\..\Library\Framework\pch.h"
#include "LimitTime.h"
#include <CommonStates.h>
#include <WICTextureLoader.h>
#include "..\..\Library\Devices\Devices.h"
#include <string>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

const float LimitTime::POS_X = 520.0f;
const float LimitTime::POS_Y = 10.0f;

LimitTime::LimitTime(float limitTime) :m_time(limitTime)
{
	m_isHand = true;
}

LimitTime::~LimitTime()
{
}

//	初期化
void LimitTime::Initialize()
{
	auto& devices = Devices::GetInstance();

	//	リソース読み込み
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/numbers.png", resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

}

//	更新
void LimitTime::Update()
{
	if (m_isHand)
		m_time -= 0.01f;
}

//	描画
void LimitTime::Draw(std::unique_ptr<DirectX::SpriteBatch>& spriteBatch)
{
	auto& devices = Devices::GetInstance();
	float time = m_time;

	CommonStates states(devices.GetDevice().Get());
	spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	//	表示する数
	RECT rect;
	rect.top = 0;
	rect.bottom = 30;

	//	桁数
	int value = std::to_string((int)time).length();

	//	桁数分表示
	for (int i = 0; i < value; i++)
	{
		rect.left = ((int)time % 10) * 30;
		rect.right = ((int)time % 10) * 30 + 30;

		//	テクスチャの描画
		spriteBatch->Draw(m_texture.Get(), Vector2(POS_X - 30.0f * i, POS_Y), &rect, Colors::White, 0.0f, Vector2(0, 0), 1.5f);
		
		time = time / 10;
	}
	spriteBatch->End();
}

//	リセット
void LimitTime::Reset(float limitTime)
{
	m_time = limitTime;
}

//	時間を進める
void LimitTime::Forward()
{
	m_isHand = true;
}

//	時間を止める
void LimitTime::Stop()
{
	m_isHand = false;
}

//	タイムオーバーかどうか
bool LimitTime::IsTimeOver()
{
	if (m_time <= 0.0f)
	{
		m_isHand = false;
		m_time = 0.0f;
		return  true;
	}
	else return false;
}

//	現在の時間
float LimitTime::NowTime()
{
	return m_time;
}

//	フレーム秒の取得
int LimitTime::GetTime()
{
	return m_time * 6000;
}
