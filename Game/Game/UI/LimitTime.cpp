//============================================================//
//*���@�O	LimitTime.cpp
//*���@�e	��������
//*���@�t	2017.7.28
//*�X�@�V	2017.7.28
//*�����	N.Shibayama
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

//	������
void LimitTime::Initialize()
{
	auto& devices = Devices::GetInstance();

	//	���\�[�X�ǂݍ���
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/numbers.png", resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

}

//	�X�V
void LimitTime::Update()
{
	if (m_isHand)
		m_time -= 0.01f;
}

//	�`��
void LimitTime::Draw(std::unique_ptr<DirectX::SpriteBatch>& spriteBatch)
{
	auto& devices = Devices::GetInstance();
	float time = m_time;

	CommonStates states(devices.GetDevice().Get());
	spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	//	�\�����鐔
	RECT rect;
	rect.top = 0;
	rect.bottom = 30;

	//	����
	int value = std::to_string((int)time).length();

	//	�������\��
	for (int i = 0; i < value; i++)
	{
		rect.left = ((int)time % 10) * 30;
		rect.right = ((int)time % 10) * 30 + 30;

		//	�e�N�X�`���̕`��
		spriteBatch->Draw(m_texture.Get(), Vector2(POS_X - 30.0f * i, POS_Y), &rect, Colors::White, 0.0f, Vector2(0, 0), 1.5f);
		
		time = time / 10;
	}
	spriteBatch->End();
}

//	���Z�b�g
void LimitTime::Reset(float limitTime)
{
	m_time = limitTime;
}

//	���Ԃ�i�߂�
void LimitTime::Forward()
{
	m_isHand = true;
}

//	���Ԃ��~�߂�
void LimitTime::Stop()
{
	m_isHand = false;
}

//	�^�C���I�[�o�[���ǂ���
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

//	���݂̎���
float LimitTime::NowTime()
{
	return m_time;
}

//	�t���[���b�̎擾
int LimitTime::GetTime()
{
	return m_time * 6000;
}
