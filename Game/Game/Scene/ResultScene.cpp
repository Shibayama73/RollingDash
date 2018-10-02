//============================================================//
//*名　前	ResultScene.cpp
//*内　容	リザルトシーン
//*日　付	2018.5.24
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#include "ResultScene.h"
#include <WICTextureLoader.h>

#include <fstream>
#include <string>

#include "..\..\Library\Keyboards\Keyboards.h"

#include "..\..\Library\Framework\GameMain.h"
#include "PlayStage1Scene.h"
#include "SceneManager.h"

#include "..\..\Library\Sounds\ADX2Le.h"
#include "..\..\Resources\Sounds\CueSheet_0.h"
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

const float ResultScene::POS_X = 490.0f;
const float ResultScene::POS_Y = 380.0f;

ResultScene::ResultScene(int width, int height) :m_outputWidth(width), m_outputHeight(height)
{
}

ResultScene::~ResultScene()
{
}

int ResultScene::InitializeGame()
{
	auto& devices = Devices::GetInstance();

	//	カメラ生成
	m_camera = std::make_unique<FollowCamera>(this->m_outputWidth, this->m_outputHeight);
	Object3D::InitializeStatic(m_camera.get());

	//	スプライトバッチ生成
	this->m_spriteBatch = std::make_unique<SpriteBatch>(devices.GetDeviceContext().Get());

	//	リソース読み込み
	ComPtr<ID3D11Resource> resource;
	//	リザルト
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/result.png", resource.GetAddressOf(),
			m_TexResult.ReleaseAndGetAddressOf()));
	//	数字
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/numbers2.png", resource.GetAddressOf(),
			m_TexNumber.ReleaseAndGetAddressOf()));

	//	秒
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/minutes.png", resource.GetAddressOf(),
			m_TexMinutes.ReleaseAndGetAddressOf()));

	//	キーの指示
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/enter2title.png", resource.GetAddressOf(),
			m_TexKey.ReleaseAndGetAddressOf()));

	//	選択時のキーの指示
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/enter2title1.png", resource.GetAddressOf(),
			m_TexKey1.ReleaseAndGetAddressOf()));

	//	ファイルの読込み
	m_fileInput = new FileIO();
	m_fileInput->SetFileName("Text/result.txt");

	//	世界ステージ
	m_worldStage = new World();
	m_worldStage->Initialize();

	//	立方体
	m_cubeRight = new Cube();
	m_cubeRight->Initialize(Vector3(5.5f, 2.0f, 0.0f), Vector3(0.25f, 0.25f, 0.25f), 0.025f);
	m_cubeRight->StartRot();
	m_cubeLeft = new Cube();
	m_cubeLeft->Initialize(Vector3(3.0f, -0.8f, 0.0f), Vector3(0.4f, 0.1f, 0.3f), 0.01f);
	m_cubeLeft->StartRot();

	//	タイマー開始しない
	m_isTimer = false;
	//	終了時間
	m_endTime = 60;

	//	サウンドファイルの読み込み
	ADX2Le* adx2le = ADX2Le::GetInstance();
	adx2le->Initialize(L"KoroDash.acf");
	adx2le->LoadAcb(L"CueSheet_0.acb", L"CueSheet_0.awb");

	//	サウンド再生
	adx2le->Play(CRI_CUESHEET_0_RESULT);

	return 0;
}

int ResultScene::UpdateGame()
{
	//	シーン設定
	m_NextScene = SceneManager::SCENE::RESULT;
	m_sceneBase = SceneManager::SCENE::RESULT;

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
		//	プレイシーンに移動
		m_NextScene = SceneManager::SCENE::TITLE;
	}

	auto& key = Keyboards::GetInstance();
	key.TrackerUpdate();

	if (key.CheckPressed("Enter"))
	{
		adx2le->Play(CRI_CUESHEET_0_DECISION);
		m_isTimer = true;
	}

	return m_NextScene;
}

void ResultScene::RenderGame()
{
	auto& devices = Devices::GetInstance();

	//	ファイル読込み
	int value = m_fileInput->LoadNum(0);

	CommonStates states(devices.GetDevice().Get());
	this->m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	//	モデルの描画
	m_worldStage->Draw();
	m_cubeRight->Draw();
	m_cubeLeft->Draw();

	//	表示する数
	RECT rect;
	rect.top = 0;
	rect.bottom = 256;

	//	桁数分表示
	for (int i = 0; i <= value; i++)
	{
		rect.left = (value % 10) * 256;
		rect.right = (value % 10) * 256 + 256;

		m_spriteBatch->Draw(m_TexNumber.Get(), Vector2(POS_X - 128.0f * i, POS_Y), &rect, Colors::White, 0.0f, Vector2(0, 0), 0.5f);

		value = value / 10;
	}

	m_spriteBatch->Draw(m_TexResult.Get(), Vector2(256.0f, 150.0f), nullptr, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
	m_spriteBatch->Draw(m_TexMinutes.Get(), Vector2(600.0f, 400.0f), nullptr, Colors::White, 0.0f, Vector2(0, 0), 0.5f);
	m_spriteBatch->Draw(m_TexKey.Get(), Vector2(202.0f, 600.0f), nullptr, Colors::White, 0.0f, Vector2(0, 0), 1.0f);

	if (m_isTimer)
	{
		//	文字を点滅させる
		if (m_endTime % 20 == 0)
			m_spriteBatch->Draw(m_TexKey1.Get(), Vector2(202.0f, 600.0f), nullptr, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
	}

	this->m_spriteBatch->End();
}

void ResultScene::Finalize()
{
	delete m_cubeLeft;
	delete m_cubeRight;
	delete m_worldStage;
}
