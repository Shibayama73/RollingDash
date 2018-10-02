//============================================================//
//*���@�O	StageSelectScene.cpp
//*���@�e	�X�e�[�W�Z���N�g�V�[��
//*���@�t	2018.7.27
//*�X�@�V	2018.7.27
//*�����	N.Shibayama
//============================================================//
#include "StageSelectScene.h"
#include <WICTextureLoader.h>
#include "..\..\Library\\Keyboards\Keyboards.h"

#include "..\..\Library\Framework\GameMain.h"
#include "SceneManager.h"

#include "..\..\Library\Sounds\ADX2Le.h"
#include "..\..\Resources\Sounds\CueSheet_0.h"
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

StageSelectScene::StageSelectScene(int width, int height) :m_outputWidth(width), m_outputHeight(height)
{
}

StageSelectScene::~StageSelectScene()
{
}

int StageSelectScene::InitializeGame()
{
	auto& devices = Devices::GetInstance();

	//	�J��������
	m_camera = std::make_unique<FollowCamera>(this->m_outputWidth, this->m_outputHeight);
	Object3D::InitializeStatic(m_camera.get());

	//	�X�v���C�g�o�b�`����
	m_spriteBatch = std::make_unique<SpriteBatch>(devices.GetDeviceContext().Get());

	//	���\�[�X�ǂݍ���
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/stageSelect.png", resource.GetAddressOf(),
			m_selectTexture.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/stage1.png", resource.GetAddressOf(),
			m_stage1Texture.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/stage2.png", resource.GetAddressOf(),
			m_stage2Texture.ReleaseAndGetAddressOf()));

	//	���E�X�e�[�W
	m_worldStage = new World();
	m_worldStage->Initialize();

	//	������
	m_cubeRight = new Cube();
	m_cubeRight->Initialize(Vector3(3.0f, 0.0f, 0.0f), Vector3(0.5f, 0.5f, 0.5f), 0.005f);
	m_cubeRight->StartRot();
	m_cubeLeft = new Cube();
	m_cubeLeft->Initialize(Vector3(-3.0f, 0.0f, 0.0f), Vector3(0.5f, 0.5f, 0.5f), 0.005f);
	m_cubeLeft->StartRot();

	//	�I���̏�����
	m_select = SELECT::STAGE_1;
	//	�^�C�}�[�J�n���Ȃ�
	m_isTimer = false;
	//	�I������
	m_endTime = 60;

	//	�T�E���h�t�@�C���̓ǂݍ���
	ADX2Le* adx2le = ADX2Le::GetInstance();
	adx2le->Initialize(L"KoroDash.acf");
	adx2le->LoadAcb(L"CueSheet_0.acb", L"CueSheet_0.awb");

	//	�T�E���h�Đ�
	adx2le->Play(CRI_CUESHEET_0_SELECT_STAGE);

	return 0;
}

int StageSelectScene::UpdateGame()
{
	//	�V�[���ݒ�
	m_NextScene = SceneManager::SCENE::STAGE_SELECT;
	m_sceneBase = SceneManager::SCENE::STAGE_SELECT;

	auto& key = Keyboards::GetInstance();
	key.TrackerUpdate();

	ADX2Le* adx2le = ADX2Le::GetInstance();

	//	�J�����X�V
	m_camera->Update();

	//	���f���̍X�V
	m_cubeRight->Update(m_cubeLeft->m_obbNode);
	m_cubeLeft->Update(m_cubeRight->m_obbNode);

	//	���Ԍo��
	if (m_isTimer) m_endTime--;

	//	�o�߂�����
	if (m_endTime <= 0)
	{
		adx2le->Stop();
		//	�v���C�V�[���Ɉړ�
		switch (m_select)
		{
		case SELECT::STAGE_1:
			m_NextScene = SceneManager::SCENE::PLAY_STAGE1;
			break;
		case SELECT::STAGE_2:
			m_NextScene = SceneManager::SCENE::PLAY_STAGE2;
			break;
		default:
			break;
		}
	}

	//	�I��ύX
	if (key.CheckPressed("Space"))
	{
		adx2le->Play(CRI_CUESHEET_0_SELECT);
		m_select++;
		if (m_select >= SELECT::NUM)
		{
			m_select = SELECT::STAGE_1;
		}
	}
	//	�I�����ꂽ�V�[���Ɉړ�
	else if (key.CheckPressed("Enter"))
	{
		adx2le->Play(CRI_CUESHEET_0_DECISION);

		switch (m_select)
		{
		case SELECT::STAGE_1:
			m_isTimer = true;
			break;
		case SELECT::STAGE_2:
			m_isTimer = true;
			break;
		default:
			break;
		}
	}

	return m_NextScene;
}

void StageSelectScene::RenderGame()
{
	auto& devices = Devices::GetInstance();

	CommonStates states(devices.GetDevice().Get());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());
	//this->m_spriteBatch->Begin();

	//	���f���̕`��
	m_worldStage->Draw();
	m_cubeRight->Draw();
	m_cubeLeft->Draw();

	//	�e�N�X�`���`��
	m_spriteBatch->Draw(m_selectTexture.Get(), Vector2(256.0f, 150.0f), nullptr, Colors::White, 0.0f);
	
	//	�I��
	switch (m_select)
	{
	case SELECT::STAGE_1:
		m_spriteBatch->Draw(m_stage1Texture.Get(), Vector2(180.0f, 350.0f), nullptr, Colors::LightSkyBlue, 0.0f);
		m_spriteBatch->Draw(m_stage2Texture.Get(), Vector2(630.0f, 350.0f), nullptr, Colors::White, 0.0f);
		break;
	case SELECT::STAGE_2:
		m_spriteBatch->Draw(m_stage1Texture.Get(), Vector2(180.0f, 350.0f), nullptr, Colors::White, 0.0f);
		m_spriteBatch->Draw(m_stage2Texture.Get(), Vector2(630.0f, 350.0f), nullptr, Colors::LightSkyBlue, 0.0f);
		break;
	default:
		break;
	}

	//	�I���L�[�������ꂽ��
	if (m_isTimer)
	{
		//	�I��
		switch (m_select)
		{
		case SELECT::STAGE_1:
			//	�_�ł�����
			if (m_endTime & m_blinkMask)
				m_spriteBatch->Draw(m_stage1Texture.Get(), Vector2(180.0f, 350.0f), nullptr, Colors::LightSkyBlue, 0.0f);
			else
				m_spriteBatch->Draw(m_stage1Texture.Get(), Vector2(180.0f, 350.0f), nullptr, Colors::White, 0.0f);
			break;
		case SELECT::STAGE_2:
			//	�_�ł�����
			if (m_endTime & m_blinkMask)
				m_spriteBatch->Draw(m_stage2Texture.Get(), Vector2(630.0f, 350.0f), nullptr, Colors::LightSkyBlue, 0.0f);
			else
				m_spriteBatch->Draw(m_stage2Texture.Get(), Vector2(630.0f, 350.0f), nullptr, Colors::White, 0.0f);
			break;
		default:
			break;
		}
	}

	m_spriteBatch->End();
}

void StageSelectScene::Finalize()
{
	delete m_cubeLeft;
	delete m_cubeRight;
	delete m_worldStage;
}
