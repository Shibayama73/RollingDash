//============================================================//
//*名　前	PlayStage1Scene.cpp
//*内　容	ゲームプレイステージ１シーン
//*日　付	2017.7.13
//*更　新	2018.7.24
//*制作者	N.Shibayama
//============================================================//
#include "PlayStage1Scene.h"
#include <WICTextureLoader.h>
#include "SceneManager.h"
#include "..\..\Library\Files\FileIO.h"

#include "..\..\Library\Sounds\ADX2Le.h"
#include "..\..\Resources\Sounds\CueSheet_0.h"
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

//	シールドの出現位置
const Vector3 PlayStage1Scene::SHIELD_UP = Vector3(0.0f, 2.0f, 0.0f);
//	シールドの個数制限
const int PlayStage1Scene::SHIELD_MAX = 5;
//	敵の数制限
const int PlayStage1Scene::ENEMY_MAX = 10;
//	ゲームクリアしたときに一度だけtrueになる
bool PlayStage1Scene::m_justClear = false;
//	ゲームオーバーしたときに一度だけtrueになる
bool PlayStage1Scene::m_justOver = false;
//	ハートのゴールエリアの範囲(円の直径)
const int PlayStage1Scene::GOAL_AREA = 25;

PlayStage1Scene::PlayStage1Scene(int width, int height) :m_outputWidth(width), m_outputHeight(height)
{
}

int PlayStage1Scene::InitializeGame()
{
	auto& devices = Devices::GetInstance();
	auto& key = Keyboards::GetInstance();
	//	カメラ生成
	m_camera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);
	//	キーボードをセット
	m_camera->SetKeyboard(&key);

	//	スプライトバッチ生成
	m_spriteBatch = std::make_unique<SpriteBatch>(devices.GetDeviceContext().Get());
	//	グリッド生成
	//	this->m_gridFloor = std::make_unique<GridFloor>(20.0f,20);
	//	フォント生成
	m_spriteFont = std::make_unique<SpriteFont>(devices.GetDevice().Get(), L"myfile.spritefont");
	//	コモンステート生成する
	m_commonStates = std::make_unique<CommonStates>(devices.GetDevice().Get());
	//	エフェクトファクトリ生成
	m_effect = std::make_unique<BasicEffect>(devices.GetDevice().Get());
	m_effect->SetProjection(XMMatrixOrthographicOffCenterRH(0, m_outputWidth, m_outputHeight, 0, 0, 1));
	m_effect->SetVertexColorEnabled(true);
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	Object3D::InitializeStatic(m_camera.get());

	//	立方体ステージの生成
	m_cubeStage = new CubeStage();
	m_cubeStage->Initialize(Vector3(0.0f, -25.0f, 0.0f), Vector3(5.0f, 5.0f, 5.0f));

	//	世界ステージの生成
	m_worldStage = new World();
	m_worldStage->Initialize();

	//	プレイヤーの生成
	m_player = new Player();
	m_player->Initialize();

	//	ハートの生成
	m_heart = new Heart();
	m_heart->Initialize();

	//	制限時間の生成
	m_limitTime = new LimitTime(30.0f);
	m_limitTime->Initialize();
	m_limitTime->Forward();

	//	シールドの総数生成
	m_shieldSum = new ShieldSum();
	m_shieldSum->Initialize();

	//	リソース読み込み
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/win.png", resource.GetAddressOf(),
			m_winTexture.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/lose.png", resource.GetAddressOf(),
			m_loseTexture.ReleaseAndGetAddressOf()));

	//	現在の時間
	m_nowTime = 0;

	//	ゲームクリアフラグ
	m_isClear = false;
	m_justClear = false;
	//	ゲームオーバーフラグ
	m_isOver = false;
	m_justOver = false;

	//	タイマー開始しない
	m_isTimer = false;
	//	終了時間
	m_endTime = 50;

	//	サウンドファイルの読み込み
	ADX2Le* adx2le = ADX2Le::GetInstance();
	adx2le->Initialize(L"KoroDash.acf");
	adx2le->LoadAcb(L"CueSheet_0.acb", L"CueSheet_0.awb");

	//	プレイBGM再生
	adx2le->Play(CRI_CUESHEET_0_PLAY);
	//	開始SE再生
	adx2le->Play(CRI_CUESHEET_0_RE_START2);

	//	パーティクルエフェクトマネージャの作成
	ParticleEffectManager* particleManager = ParticleEffectManager::GetInstance();
	particleManager->Initialize();
	particleManager->SetCamera(m_camera.get());

	//	円エミッタ生成
	ImpactEmitter::LoadTexture(1, L"Resources/ShaderTextures/star2.png");
	m_impactEmitter = std::make_unique<ImpactEmitter>(Vector3(0, 0, 0));
	//	ゲームオーバーエミッタ生成
	OverEmitter::LoadTexture(2, L"Resources/ShaderTextures/effect1.png");
	m_overEmitter = std::make_unique<OverEmitter>(Vector3(0, 0, 0));
	//	ゲームクリアエミッタ生成
	ClearEmitter::LoadTexture(3, L"Resources/ShaderTextures/effect3.png");
	m_clearEmitter = std::make_unique<ClearEmitter>(Vector3(0, 0, 0));
	//	ゴールエミッタ生成
	GoalEmitter::LoadTexture(4, L"Resources/ShaderTextures/effect6.png");
	m_goalEmitter = std::make_unique<GoalEmitter>(Vector3(0, 0, 0));

	return 0;
}

int PlayStage1Scene::UpdateGame()
{
	//	追尾カメラの設定
	m_camera->SetTargetPos(m_player->GetTranslation());
	m_camera->SetTargetAngle(m_player->GetRotation().y);
	//	カメラ更新
	m_camera->Update();

	auto& key = Keyboards::GetInstance();
	key.TrackerUpdate();

	ADX2Le* adx2le = ADX2Le::GetInstance();

	//	パーティクルマネージャー
	ParticleEffectManager* particleEffectManager = ParticleEffectManager::GetInstance();

	//	モデルの更新
	m_cubeStage->Update();

	//	プレイヤーの更新
	m_player->Update();
	m_player->StageColSinkRestore(*m_cubeStage);

	//	一定時間毎に敵の生成と初期化
	if (m_nowTime % 60 == 0)
	{
		int create = m_enemy.size();
		//	生成の制限
		if (create < ENEMY_MAX)
		{
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
			enemy->Initialize();
			m_enemy.push_back(std::move(enemy));
		}
	}

	//	シールドの生成
	if (key.CheckPressed("Up"))
	{
		int create = m_shield.size();
		//	生成の制限
		if (create < SHIELD_MAX)
		{
			adx2le->Play(CRI_CUESHEET_0_SHIELD_CRE);
			std::unique_ptr<Shield> shield = std::make_unique<Shield>();
			shield->Initialize(m_player->GetTranslation() + SHIELD_UP);
			m_shield.push_back(std::move(shield));
		}
	}

	for (auto itr = m_shield.begin(); itr != m_shield.end();)
	{
		//	シールドの更新
		(*itr)->Update();
		//	プレイヤーとシールドが当たったらめり込み戻す
		m_player->ShieldColSinkRestore((*itr)->m_obbNode);
		//	シールドとステージが当たったら
		OBBCollision obbCollision;
		if (obbCollision.IsOBB2OBBCollision(m_cubeStage->m_obbNode, (*itr)->m_obbNode))
		{
			//	当ったったことを伝え、ステージの回転方向を変える
			m_cubeStage->OnCollision();

			//	シールド削除
			itr = m_shield.erase(itr);
		}
		else itr++;

	}

	for (std::unique_ptr<Enemy>& enemy : m_enemy)
	{
		//	敵の更新
		enemy->Update(m_player->GetCollisionNode());
		//	敵がステージに当たったらバウンドする
		enemy->Bound(m_cubeStage->m_obbNode);

		for (auto itr = m_shield.begin(); itr != m_shield.end();)
		{
			//	敵がシールドに当たったらバウンドする
			enemy->Bound((*itr)->m_obbNode);

			//	敵とシールドが当たったとき
			if (enemy->IsOBBCollision((*itr)->m_obbNode))
			{
				adx2le->Play(CRI_CUESHEET_0_COL2);

				//	シールドを削除
				itr = m_shield.erase(itr);
			}
			else itr++;

		}
		//	敵の重力
		enemy->Gravity();
	}

	//	一定時間経過したら
	if (m_nowTime >= 180.0f && m_nowTime % 120 == 0)
	{
		if (!m_enemy.empty())
		{
			//	一体ずつ敵を削除
			m_enemy.erase(m_enemy.begin());
		}
	}

	//	一定時間経過
	if (m_nowTime % 160 == 0)
	{
		if (!m_shield.empty())
		{
			//	一個ずつシールドを削除
			m_shield.erase(m_shield.begin());
		}
	}

	//	ハートの更新
	m_heart->Update();

	//	制限時間の更新
	m_limitTime->Update();

	//	エフェクト
	ModelEffectManager::getInstance()->Update();

	//	時間経過
	if (m_isTimer) m_endTime--;

	//	経過したら
	if (m_endTime <= 0)
	{
		adx2le->Stop();
		//	リスタート
		this->InitializeGame();
	}

	//	プレイヤーの当たり判定取得
	const SphereCollision& playerSphere = m_player->GetCollisionNode();

	for (std::unique_ptr<Enemy>& enemy : m_enemy)
	{
		//	敵の当たり判定取得
		const SphereCollision& enemySphere = enemy->GetCollisionNode();
		SphereCollision sphereCollision;
		//	プレイヤーと敵が当たっていたら
		if (sphereCollision.CheckSphere2Sphere(playerSphere, enemySphere))
		{
			if (!m_isClear && !m_isOver)
			{
				//	衝撃エフェクトエミッタの発生時間の設定
				m_impactEmitter->SetOccurLimitTime(30.0f);
				m_impactEmitter->SetPosition(m_player->GetTranslation());

				m_isTimer = true;
				adx2le->Play(CRI_CUESHEET_0_COL1);
			}
		}
	}

	//	現在の時間
	m_nowTime++;

	//	シーン設定
	m_NextScene = SceneManager::SCENE::PLAY_STAGE1;
	m_sceneBase = SceneManager::SCENE::PLAY_STAGE1;

	//	リセット
	if (key.CheckKey("R"))
	{
		this->InitializeGame();
	}

	Vector3 playerPos = m_player->GetTranslation();
	Vector3 heartPos = m_heart->GetTranslation();

	//	ゴールエフェクトエミッタの発生時間の設定
	m_goalEmitter->SetOccurLimitTime(m_limitTime->GetTime());
	m_goalEmitter->SetPosition(heartPos);

	//	プレイヤーがハートのゴールエリアに辿り着いたらゴール
	Vector3 dis = playerPos - heartPos;
	if ((dis.x*dis.x) + (dis.y*dis.y) + (dis.z*dis.z) < GOAL_AREA)
	{
		m_isClear = true;
		m_limitTime->Stop();

		//	一度だけSEを流す
		if (!m_justClear)
		{
			adx2le->Play(CRI_CUESHEET_0_CLEAR);

			//	ゲームクリアエフェクトエミッタの発生時間の設定
			m_clearEmitter->SetOccurLimitTime(300.0f);
			m_clearEmitter->SetPosition(m_player->GetTranslation());

			m_justClear = true;
		}

		//	タイムを書き込む
		FileIO fileOutput;
		fileOutput.SetFileName("Text/result.txt");
		fileOutput.FileWrite(m_limitTime->NowTime());
	}
	//	制限時間になるまえにプレイヤーがハートに辿り着かなかった、ゲームオーバーエリアに行ったら
	else if (m_limitTime->IsTimeOver() || m_player->IsAreaOver(m_cubeStage->m_obbNode))
	{
		m_isOver = true;
		m_limitTime->Stop();

		//	一度だけSEを流す
		if (!m_justOver)
		{
			adx2le->Play(CRI_CUESHEET_0_OVER);

			//	ゲームオーバーエフェクトエミッタの発生時間の設定
			m_overEmitter->SetOccurLimitTime(300.0f);
			m_overEmitter->SetPosition(m_player->GetTranslation());

			m_justOver = true;
		}

		//	タイムを書き込む
		FileIO fileOutput;
		fileOutput.SetFileName("Text/result.txt");
		fileOutput.FileWrite(0);
	}

	//	クリアまたはオーバー判定がでたとき
	if (m_isClear || m_isOver)
	{
		//	プレイヤーの操作を使用停止する
		m_player->StopControl();

		//	エフェクトを停止する
		m_goalEmitter->End();

		if (m_nowTime % 300 == 0)
		{
			adx2le->Stop();
			m_NextScene = SceneManager::SCENE::RESULT;
		}
	}

	//	エフェクトエミッタ更新
	m_impactEmitter->Update();
	m_overEmitter->Update();
	m_clearEmitter->Update();
	m_goalEmitter->Update();

	particleEffectManager->Update();

	return m_NextScene;
}

void PlayStage1Scene::RenderGame()
{
	m_spriteBatch->Begin();

	//	カメラの更新
	Matrix view = m_camera->GetViewMatrix();
	//	射影行列
	Matrix projection = Matrix::CreatePerspectiveFieldOfView(DirectX::XMConvertToDegrees(60.0f),
		(float)m_outputWidth / (float)m_outputHeight, 1.0f, 100.0f);

	//	デバッグ表示
#ifdef _DEBUG
	//	グリッド描画
	//	this->m_gridFloor->Render(view, projection);
//	this->m_spriteFont->DrawString(m_spriteBatch.get(), L"move : WSAD", SimpleMath::Vector2(0, 0), Colors::White);
//	this->m_spriteFont->DrawString(m_spriteBatch.get(), L"collision : F", SimpleMath::Vector2(0, 25), Colors::White);
	//	プレイヤーの座標
	//m_spriteFont->DrawString(m_spriteBatch.get(), L"X:", SimpleMath::Vector2(0, 50), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), std::to_wstring(m_player->GetTranslation().x).c_str(), SimpleMath::Vector2(50, 50), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), L"Y:", SimpleMath::Vector2(0, 100), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), std::to_wstring(m_player->GetTranslation().y).c_str(), SimpleMath::Vector2(50, 100), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), L"Z:", SimpleMath::Vector2(0, 150), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), std::to_wstring(m_player->GetTranslation().z).c_str(), SimpleMath::Vector2(50, 150), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	////	ステージの角度
	//m_spriteFont->DrawString(m_spriteBatch.get(), L"Radius:", SimpleMath::Vector2(0, 200), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), std::to_wstring(m_cubeStage->GetRotation().z).c_str(), SimpleMath::Vector2(150, 200), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	////	ステージの回転フラグ
	//m_spriteFont->DrawString(m_spriteBatch.get(), L"CollisionFlag:", SimpleMath::Vector2(0, 250), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), std::to_wstring(m_cubeStage->IsCollision()).c_str(), SimpleMath::Vector2(260, 250), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
#endif

	//	エフェクトの描画
	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);
	auto& devices = Devices::GetInstance();
	m_effect->Apply(devices.GetDeviceContext().Get());

	//	世界ステージ
	m_worldStage->Draw();
	//	モデルの描画
	m_cubeStage->Draw();
	//	プレイヤーの描画
	m_player->Draw();

	//	敵の描画
	for (std::unique_ptr<Enemy>& enemy : m_enemy)
	{
		enemy->Draw();
	}

	//	ハートの描画
	m_heart->Draw();

	//	シールドの描画
	for (std::unique_ptr<Shield>& shield : m_shield)
	{
		shield->Draw();
	}

	//	エフェクト
	ModelEffectManager::getInstance()->Draw();
	m_spriteBatch->End();

	//	制限時間の描画
	m_limitTime->Draw(m_spriteBatch);

	//	シールドの総数の描画
	int sum = 0;
	if (!m_shield.empty()) sum = m_shield.size();
	m_shieldSum->Draw(m_spriteBatch, SHIELD_MAX - sum, SHIELD_MAX);

	//	テクスチャの描画
	CommonStates states(devices.GetDevice().Get());

	ADX2Le* adx2le = ADX2Le::GetInstance();

	if (m_isClear)
	{
		//	ゲームクリア
		m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());
		m_spriteBatch->Draw(m_winTexture.Get(), Vector2(400.0f, 324.0f), nullptr, Colors::White, 0.0f);
		m_spriteBatch->End();
	}
	else if (m_isOver)
	{
		//	ゲームオーバー
		m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());
		m_spriteBatch->Draw(m_loseTexture.Get(), Vector2(368.0f, 324.0f), nullptr, Colors::White, 0.0f);
		m_spriteBatch->End();
	}

	//	パーティクルマネージャー
	ParticleEffectManager* particleEffectManager = ParticleEffectManager::GetInstance();
	particleEffectManager->Draw();

}

void PlayStage1Scene::Finalize()
{
	delete m_heart;
	delete m_player;
	delete m_worldStage;

}
