//============================================================//
//*名　前	TitleScene.cpp
//*内　容	タイトルシーン
//*日　付	2017.12.05
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#include "TitleScene.h"
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

TitleScene::TitleScene(int width, int height) :m_outputWidth(width), m_outputHeight(height)
{
}

TitleScene::~TitleScene()
{
}

int TitleScene::InitializeGame()
{
	auto& devices = Devices::GetInstance();

	//	カメラ生成
	m_camera = std::make_unique<FollowCamera>(this->m_outputWidth, this->m_outputHeight);
	Object3D::InitializeStatic(m_camera.get());

	//	スプライトバッチ生成
	m_spriteBatch = std::make_unique<SpriteBatch>(devices.GetDeviceContext().Get());

	//	リソース読み込み
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/title_logo.png", resource.GetAddressOf(),
			m_titleTexture.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/start0.png", resource.GetAddressOf(),
			m_startTexture.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/start1.png", resource.GetAddressOf(),
			m_start1Texture.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/end0.png", resource.GetAddressOf(),
			m_endTexture.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/end1.png", resource.GetAddressOf(),
			m_end1Texture.ReleaseAndGetAddressOf()));

	//	世界ステージ
	m_worldStage = new World();
	m_worldStage->Initialize();

	//	立方体
	m_cubeRight = new Cube();
	m_cubeRight->Initialize(Vector3(3.0f, 0.0f, 0.0f), Vector3(0.5f, 0.5f, 0.5f), 0.005f);
	m_cubeRight->StartRot();
	m_cubeLeft = new Cube();
	m_cubeLeft->Initialize(Vector3(-3.0f, 0.0f, 0.0f), Vector3(0.5f, 0.5f, 0.5f), 0.005f);
	m_cubeLeft->StartRot();

	//	選択
	m_select = SELECT::START;
	//	タイマー開始しない
	m_isTimer = false;
	//	終了時間
	m_endTime = 60;

	//	サウンドファイルの読み込み
	ADX2Le* adx2le = ADX2Le::GetInstance();
	adx2le->Initialize(L"KoroDash.acf");
	adx2le->LoadAcb(L"CueSheet_0.acb", L"CueSheet_0.awb");

	//	サウンド再生
	adx2le->Play(CRI_CUESHEET_0_TITLE);

	return 0;
}

int TitleScene::UpdateGame()
{
	//	シーン設定
	m_NextScene = SceneManager::SCENE::TITLE;
	m_sceneBase = SceneManager::SCENE::TITLE;

	auto& key = Keyboards::GetInstance();
	key.TrackerUpdate();

	ADX2Le* adx2le = ADX2Le::GetInstance();

	//	カメラ更新
	m_camera->Update();

	//	モデルの更新
	m_cubeRight->Update(m_cubeLeft->m_obbNode);
	m_cubeLeft->Update(m_cubeRight->m_obbNode);

	//	時間経過
	if (m_isTimer) m_endTime--;

	//	経過したら
	if (m_endTime <= 0)
	{
		adx2le->Stop();
		//	ステージセレクトシーンに移動
		m_NextScene = SceneManager::SCENE::STAGE_SELECT;
	}

	//	選択変更
	if (key.CheckPressed("Space"))
	{
		adx2le->Play(CRI_CUESHEET_0_SELECT);
		m_select++;
		if (m_select >= SELECT::NUM)
		{
			m_select = SELECT::START;
		}
	}
	//	選択されたシーンに移動
	else if (key.CheckPressed("Enter"))
	{
		adx2le->Play(CRI_CUESHEET_0_DECISION);

		switch (m_select)
		{
		case SELECT::START:
			m_isTimer = true;
			break;
		case SELECT::END:
			adx2le->Stop();
			exit(0);
			//DestroyWindow(0);
			//PostQuitMessage(WM_CLOSE);
			break;
		default:
			break;
		}
	}

	return m_NextScene;
}

void TitleScene::RenderGame()
{
	auto& devices = Devices::GetInstance();

	CommonStates states(devices.GetDevice().Get());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());
	//this->m_spriteBatch->Begin();

	//	モデルの描画
	m_worldStage->Draw();
	m_cubeRight->Draw();
	m_cubeLeft->Draw();

	//	テクスチャ描画
	m_spriteBatch->Draw(m_titleTexture.Get(), Vector2(278.0f, 50.0f), nullptr, Colors::White, 0.0f);
	
	//	選択
	switch (m_select)
	{
	case SELECT::START:
		m_spriteBatch->Draw(m_start1Texture.Get(), Vector2(384.0f, 450.0f), nullptr, Colors::White, 0.0f);
		m_spriteBatch->Draw(m_endTexture.Get(), Vector2(434.0f, 550.0f), nullptr, Colors::White, 0.0f);
		break;
	case SELECT::END:
		m_spriteBatch->Draw(m_startTexture.Get(), Vector2(384.0f, 450.0f), nullptr, Colors::White, 0.0f);
		m_spriteBatch->Draw(m_end1Texture.Get(), Vector2(434.0f, 550.0f), nullptr, Colors::White, 0.0f);
		break;
	default:
		break;
	}

	//	選択キーが押されたら
	if (m_isTimer)
	{
		//	Start文字を点滅させる
		if (m_endTime % 10 == 0)
			m_spriteBatch->Draw(m_startTexture.Get(), Vector2(384.0f, 450.0f), nullptr, Colors::White, 0.0f);
	}
	
	m_spriteBatch->End();
}

void TitleScene::Finalize()
{
	delete m_cubeLeft;
	delete m_cubeRight;
	delete m_worldStage;
}
