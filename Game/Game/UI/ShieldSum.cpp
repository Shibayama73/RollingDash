//============================================================//
//*���@�O	ShieldSum.cpp
//*���@�e	�V�[���h�̐��摜�̕\��
//*���@�t	2018.7.02
//*�X�@�V	2018.7.02
//*�����	N.Shibayama
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

//	�\�����W
const float ShieldSum::NOW_POS_X = 30.0f;
const float ShieldSum::NOW_POS_Y = 20.0f;
const float ShieldSum::SLASH_POS_X = 80.0f;
const float ShieldSum::SLASH_POS_Y = 20.0f;
const float ShieldSum::MAX_POS_X = 140.0f;
const float ShieldSum::MAX_POS_Y = 20.0f;

void ShieldSum::Initialize()
{
	auto& devices = Devices::GetInstance();

	//	���\�[�X�ǂݍ���
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

	//	�\�����鐔
	RECT rect;
	rect.top = 0;
	rect.bottom = 30;

	//	�ő吔
	int sum = max;
	for (int i = 0; i <= sum; i++)
	{
		rect.left = ((int)sum % 10) * 30;
		rect.right = ((int)sum % 10) * 30 + 30;
		spriteBatch->Draw(m_maxTex.Get(), Vector2(MAX_POS_X, MAX_POS_Y), &rect, Colors::DeepSkyBlue, 0.0f, Vector2(0, 0), 1.5f);
	}

	//	����
	int now = now_sum;
	//	�������\��
	for (int i = 0; i <= now; i++)
	{
		rect.left = ((int)now % 10) * 30;
		rect.right = ((int)now % 10) * 30 + 30;

		//	�e�N�X�`���̕`��
		spriteBatch->Draw(m_limitTex.Get(), Vector2(NOW_POS_X, NOW_POS_Y), &rect, Colors::DeepSkyBlue, 0.0f, Vector2(0, 0), 1.5f);
	}
	spriteBatch->End();
}
