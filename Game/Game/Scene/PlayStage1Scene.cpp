//============================================================//
//*���@�O	PlayStage1Scene.cpp
//*���@�e	�Q�[���v���C�X�e�[�W�P�V�[��
//*���@�t	2017.7.13
//*�X�@�V	2018.7.24
//*�����	N.Shibayama
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

//	�V�[���h�̏o���ʒu
const Vector3 PlayStage1Scene::SHIELD_UP = Vector3(0.0f, 2.0f, 0.0f);
//	�V�[���h�̌�����
const int PlayStage1Scene::SHIELD_MAX = 5;
//	�G�̐�����
const int PlayStage1Scene::ENEMY_MAX = 10;
//	�Q�[���N���A�����Ƃ��Ɉ�x����true�ɂȂ�
bool PlayStage1Scene::m_justClear = false;
//	�Q�[���I�[�o�[�����Ƃ��Ɉ�x����true�ɂȂ�
bool PlayStage1Scene::m_justOver = false;
//	�n�[�g�̃S�[���G���A�͈̔�(�~�̒��a)
const int PlayStage1Scene::GOAL_AREA = 25;

PlayStage1Scene::PlayStage1Scene(int width, int height) :m_outputWidth(width), m_outputHeight(height)
{
}

int PlayStage1Scene::InitializeGame()
{
	auto& devices = Devices::GetInstance();
	auto& key = Keyboards::GetInstance();
	//	�J��������
	m_camera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);
	//	�L�[�{�[�h���Z�b�g
	m_camera->SetKeyboard(&key);

	//	�X�v���C�g�o�b�`����
	m_spriteBatch = std::make_unique<SpriteBatch>(devices.GetDeviceContext().Get());
	//	�O���b�h����
	//	this->m_gridFloor = std::make_unique<GridFloor>(20.0f,20);
	//	�t�H���g����
	m_spriteFont = std::make_unique<SpriteFont>(devices.GetDevice().Get(), L"myfile.spritefont");
	//	�R�����X�e�[�g��������
	m_commonStates = std::make_unique<CommonStates>(devices.GetDevice().Get());
	//	�G�t�F�N�g�t�@�N�g������
	m_effect = std::make_unique<BasicEffect>(devices.GetDevice().Get());
	m_effect->SetProjection(XMMatrixOrthographicOffCenterRH(0, m_outputWidth, m_outputHeight, 0, 0, 1));
	m_effect->SetVertexColorEnabled(true);
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	Object3D::InitializeStatic(m_camera.get());

	//	�����̃X�e�[�W�̐���
	m_cubeStage = new CubeStage();
	m_cubeStage->Initialize(Vector3(0.0f, -25.0f, 0.0f), Vector3(5.0f, 5.0f, 5.0f));

	//	���E�X�e�[�W�̐���
	m_worldStage = new World();
	m_worldStage->Initialize();

	//	�v���C���[�̐���
	m_player = new Player();
	m_player->Initialize();

	//	�n�[�g�̐���
	m_heart = new Heart();
	m_heart->Initialize();

	//	�������Ԃ̐���
	m_limitTime = new LimitTime(30.0f);
	m_limitTime->Initialize();
	m_limitTime->Forward();

	//	�V�[���h�̑�������
	m_shieldSum = new ShieldSum();
	m_shieldSum->Initialize();

	//	���\�[�X�ǂݍ���
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/win.png", resource.GetAddressOf(),
			m_winTexture.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(devices.GetDevice().Get(), L"Resources/lose.png", resource.GetAddressOf(),
			m_loseTexture.ReleaseAndGetAddressOf()));

	//	���݂̎���
	m_nowTime = 0;

	//	�Q�[���N���A�t���O
	m_isClear = false;
	m_justClear = false;
	//	�Q�[���I�[�o�[�t���O
	m_isOver = false;
	m_justOver = false;

	//	�^�C�}�[�J�n���Ȃ�
	m_isTimer = false;
	//	�I������
	m_endTime = 50;

	//	�T�E���h�t�@�C���̓ǂݍ���
	ADX2Le* adx2le = ADX2Le::GetInstance();
	adx2le->Initialize(L"KoroDash.acf");
	adx2le->LoadAcb(L"CueSheet_0.acb", L"CueSheet_0.awb");

	//	�v���CBGM�Đ�
	adx2le->Play(CRI_CUESHEET_0_PLAY);
	//	�J�nSE�Đ�
	adx2le->Play(CRI_CUESHEET_0_RE_START2);

	//	�p�[�e�B�N���G�t�F�N�g�}�l�[�W���̍쐬
	ParticleEffectManager* particleManager = ParticleEffectManager::GetInstance();
	particleManager->Initialize();
	particleManager->SetCamera(m_camera.get());

	//	�~�G�~�b�^����
	ImpactEmitter::LoadTexture(1, L"Resources/ShaderTextures/star2.png");
	m_impactEmitter = std::make_unique<ImpactEmitter>(Vector3(0, 0, 0));
	//	�Q�[���I�[�o�[�G�~�b�^����
	OverEmitter::LoadTexture(2, L"Resources/ShaderTextures/effect1.png");
	m_overEmitter = std::make_unique<OverEmitter>(Vector3(0, 0, 0));
	//	�Q�[���N���A�G�~�b�^����
	ClearEmitter::LoadTexture(3, L"Resources/ShaderTextures/effect3.png");
	m_clearEmitter = std::make_unique<ClearEmitter>(Vector3(0, 0, 0));
	//	�S�[���G�~�b�^����
	GoalEmitter::LoadTexture(4, L"Resources/ShaderTextures/effect6.png");
	m_goalEmitter = std::make_unique<GoalEmitter>(Vector3(0, 0, 0));

	return 0;
}

int PlayStage1Scene::UpdateGame()
{
	//	�ǔ��J�����̐ݒ�
	m_camera->SetTargetPos(m_player->GetTranslation());
	m_camera->SetTargetAngle(m_player->GetRotation().y);
	//	�J�����X�V
	m_camera->Update();

	auto& key = Keyboards::GetInstance();
	key.TrackerUpdate();

	ADX2Le* adx2le = ADX2Le::GetInstance();

	//	�p�[�e�B�N���}�l�[�W���[
	ParticleEffectManager* particleEffectManager = ParticleEffectManager::GetInstance();

	//	���f���̍X�V
	m_cubeStage->Update();

	//	�v���C���[�̍X�V
	m_player->Update();
	m_player->StageColSinkRestore(*m_cubeStage);

	//	��莞�Ԗ��ɓG�̐����Ə�����
	if (m_nowTime % 60 == 0)
	{
		int create = m_enemy.size();
		//	�����̐���
		if (create < ENEMY_MAX)
		{
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
			enemy->Initialize();
			m_enemy.push_back(std::move(enemy));
		}
	}

	//	�V�[���h�̐���
	if (key.CheckPressed("Up"))
	{
		int create = m_shield.size();
		//	�����̐���
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
		//	�V�[���h�̍X�V
		(*itr)->Update();
		//	�v���C���[�ƃV�[���h������������߂荞�ݖ߂�
		m_player->ShieldColSinkRestore((*itr)->m_obbNode);
		//	�V�[���h�ƃX�e�[�W������������
		OBBCollision obbCollision;
		if (obbCollision.IsOBB2OBBCollision(m_cubeStage->m_obbNode, (*itr)->m_obbNode))
		{
			//	�������������Ƃ�`���A�X�e�[�W�̉�]������ς���
			m_cubeStage->OnCollision();

			//	�V�[���h�폜
			itr = m_shield.erase(itr);
		}
		else itr++;

	}

	for (std::unique_ptr<Enemy>& enemy : m_enemy)
	{
		//	�G�̍X�V
		enemy->Update(m_player->GetCollisionNode());
		//	�G���X�e�[�W�ɓ���������o�E���h����
		enemy->Bound(m_cubeStage->m_obbNode);

		for (auto itr = m_shield.begin(); itr != m_shield.end();)
		{
			//	�G���V�[���h�ɓ���������o�E���h����
			enemy->Bound((*itr)->m_obbNode);

			//	�G�ƃV�[���h�����������Ƃ�
			if (enemy->IsOBBCollision((*itr)->m_obbNode))
			{
				adx2le->Play(CRI_CUESHEET_0_COL2);

				//	�V�[���h���폜
				itr = m_shield.erase(itr);
			}
			else itr++;

		}
		//	�G�̏d��
		enemy->Gravity();
	}

	//	��莞�Ԍo�߂�����
	if (m_nowTime >= 180.0f && m_nowTime % 120 == 0)
	{
		if (!m_enemy.empty())
		{
			//	��̂��G���폜
			m_enemy.erase(m_enemy.begin());
		}
	}

	//	��莞�Ԍo��
	if (m_nowTime % 160 == 0)
	{
		if (!m_shield.empty())
		{
			//	����V�[���h���폜
			m_shield.erase(m_shield.begin());
		}
	}

	//	�n�[�g�̍X�V
	m_heart->Update();

	//	�������Ԃ̍X�V
	m_limitTime->Update();

	//	�G�t�F�N�g
	ModelEffectManager::getInstance()->Update();

	//	���Ԍo��
	if (m_isTimer) m_endTime--;

	//	�o�߂�����
	if (m_endTime <= 0)
	{
		adx2le->Stop();
		//	���X�^�[�g
		this->InitializeGame();
	}

	//	�v���C���[�̓����蔻��擾
	const SphereCollision& playerSphere = m_player->GetCollisionNode();

	for (std::unique_ptr<Enemy>& enemy : m_enemy)
	{
		//	�G�̓����蔻��擾
		const SphereCollision& enemySphere = enemy->GetCollisionNode();
		SphereCollision sphereCollision;
		//	�v���C���[�ƓG���������Ă�����
		if (sphereCollision.CheckSphere2Sphere(playerSphere, enemySphere))
		{
			if (!m_isClear && !m_isOver)
			{
				//	�Ռ��G�t�F�N�g�G�~�b�^�̔������Ԃ̐ݒ�
				m_impactEmitter->SetOccurLimitTime(30.0f);
				m_impactEmitter->SetPosition(m_player->GetTranslation());

				m_isTimer = true;
				adx2le->Play(CRI_CUESHEET_0_COL1);
			}
		}
	}

	//	���݂̎���
	m_nowTime++;

	//	�V�[���ݒ�
	m_NextScene = SceneManager::SCENE::PLAY_STAGE1;
	m_sceneBase = SceneManager::SCENE::PLAY_STAGE1;

	//	���Z�b�g
	if (key.CheckKey("R"))
	{
		this->InitializeGame();
	}

	Vector3 playerPos = m_player->GetTranslation();
	Vector3 heartPos = m_heart->GetTranslation();

	//	�S�[���G�t�F�N�g�G�~�b�^�̔������Ԃ̐ݒ�
	m_goalEmitter->SetOccurLimitTime(m_limitTime->GetTime());
	m_goalEmitter->SetPosition(heartPos);

	//	�v���C���[���n�[�g�̃S�[���G���A�ɒH�蒅������S�[��
	Vector3 dis = playerPos - heartPos;
	if ((dis.x*dis.x) + (dis.y*dis.y) + (dis.z*dis.z) < GOAL_AREA)
	{
		m_isClear = true;
		m_limitTime->Stop();

		//	��x����SE�𗬂�
		if (!m_justClear)
		{
			adx2le->Play(CRI_CUESHEET_0_CLEAR);

			//	�Q�[���N���A�G�t�F�N�g�G�~�b�^�̔������Ԃ̐ݒ�
			m_clearEmitter->SetOccurLimitTime(300.0f);
			m_clearEmitter->SetPosition(m_player->GetTranslation());

			m_justClear = true;
		}

		//	�^�C������������
		FileIO fileOutput;
		fileOutput.SetFileName("Text/result.txt");
		fileOutput.FileWrite(m_limitTime->NowTime());
	}
	//	�������ԂɂȂ�܂��Ƀv���C���[���n�[�g�ɒH�蒅���Ȃ������A�Q�[���I�[�o�[�G���A�ɍs������
	else if (m_limitTime->IsTimeOver() || m_player->IsAreaOver(m_cubeStage->m_obbNode))
	{
		m_isOver = true;
		m_limitTime->Stop();

		//	��x����SE�𗬂�
		if (!m_justOver)
		{
			adx2le->Play(CRI_CUESHEET_0_OVER);

			//	�Q�[���I�[�o�[�G�t�F�N�g�G�~�b�^�̔������Ԃ̐ݒ�
			m_overEmitter->SetOccurLimitTime(300.0f);
			m_overEmitter->SetPosition(m_player->GetTranslation());

			m_justOver = true;
		}

		//	�^�C������������
		FileIO fileOutput;
		fileOutput.SetFileName("Text/result.txt");
		fileOutput.FileWrite(0);
	}

	//	�N���A�܂��̓I�[�o�[���肪�ł��Ƃ�
	if (m_isClear || m_isOver)
	{
		//	�v���C���[�̑�����g�p��~����
		m_player->StopControl();

		//	�G�t�F�N�g���~����
		m_goalEmitter->End();

		if (m_nowTime % 300 == 0)
		{
			adx2le->Stop();
			m_NextScene = SceneManager::SCENE::RESULT;
		}
	}

	//	�G�t�F�N�g�G�~�b�^�X�V
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

	//	�J�����̍X�V
	Matrix view = m_camera->GetViewMatrix();
	//	�ˉe�s��
	Matrix projection = Matrix::CreatePerspectiveFieldOfView(DirectX::XMConvertToDegrees(60.0f),
		(float)m_outputWidth / (float)m_outputHeight, 1.0f, 100.0f);

	//	�f�o�b�O�\��
#ifdef _DEBUG
	//	�O���b�h�`��
	//	this->m_gridFloor->Render(view, projection);
//	this->m_spriteFont->DrawString(m_spriteBatch.get(), L"move : WSAD", SimpleMath::Vector2(0, 0), Colors::White);
//	this->m_spriteFont->DrawString(m_spriteBatch.get(), L"collision : F", SimpleMath::Vector2(0, 25), Colors::White);
	//	�v���C���[�̍��W
	//m_spriteFont->DrawString(m_spriteBatch.get(), L"X:", SimpleMath::Vector2(0, 50), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), std::to_wstring(m_player->GetTranslation().x).c_str(), SimpleMath::Vector2(50, 50), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), L"Y:", SimpleMath::Vector2(0, 100), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), std::to_wstring(m_player->GetTranslation().y).c_str(), SimpleMath::Vector2(50, 100), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), L"Z:", SimpleMath::Vector2(0, 150), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), std::to_wstring(m_player->GetTranslation().z).c_str(), SimpleMath::Vector2(50, 150), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	////	�X�e�[�W�̊p�x
	//m_spriteFont->DrawString(m_spriteBatch.get(), L"Radius:", SimpleMath::Vector2(0, 200), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), std::to_wstring(m_cubeStage->GetRotation().z).c_str(), SimpleMath::Vector2(150, 200), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	////	�X�e�[�W�̉�]�t���O
	//m_spriteFont->DrawString(m_spriteBatch.get(), L"CollisionFlag:", SimpleMath::Vector2(0, 250), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
	//m_spriteFont->DrawString(m_spriteBatch.get(), std::to_wstring(m_cubeStage->IsCollision()).c_str(), SimpleMath::Vector2(260, 250), Colors::Red, 0, Vector3(0, 0, 0), Vector3(2, 2, 2));
#endif

	//	�G�t�F�N�g�̕`��
	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);
	auto& devices = Devices::GetInstance();
	m_effect->Apply(devices.GetDeviceContext().Get());

	//	���E�X�e�[�W
	m_worldStage->Draw();
	//	���f���̕`��
	m_cubeStage->Draw();
	//	�v���C���[�̕`��
	m_player->Draw();

	//	�G�̕`��
	for (std::unique_ptr<Enemy>& enemy : m_enemy)
	{
		enemy->Draw();
	}

	//	�n�[�g�̕`��
	m_heart->Draw();

	//	�V�[���h�̕`��
	for (std::unique_ptr<Shield>& shield : m_shield)
	{
		shield->Draw();
	}

	//	�G�t�F�N�g
	ModelEffectManager::getInstance()->Draw();
	m_spriteBatch->End();

	//	�������Ԃ̕`��
	m_limitTime->Draw(m_spriteBatch);

	//	�V�[���h�̑����̕`��
	int sum = 0;
	if (!m_shield.empty()) sum = m_shield.size();
	m_shieldSum->Draw(m_spriteBatch, SHIELD_MAX - sum, SHIELD_MAX);

	//	�e�N�X�`���̕`��
	CommonStates states(devices.GetDevice().Get());

	ADX2Le* adx2le = ADX2Le::GetInstance();

	if (m_isClear)
	{
		//	�Q�[���N���A
		m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());
		m_spriteBatch->Draw(m_winTexture.Get(), Vector2(400.0f, 324.0f), nullptr, Colors::White, 0.0f);
		m_spriteBatch->End();
	}
	else if (m_isOver)
	{
		//	�Q�[���I�[�o�[
		m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());
		m_spriteBatch->Draw(m_loseTexture.Get(), Vector2(368.0f, 324.0f), nullptr, Colors::White, 0.0f);
		m_spriteBatch->End();
	}

	//	�p�[�e�B�N���}�l�[�W���[
	ParticleEffectManager* particleEffectManager = ParticleEffectManager::GetInstance();
	particleEffectManager->Draw();

}

void PlayStage1Scene::Finalize()
{
	delete m_heart;
	delete m_player;
	delete m_worldStage;

}
