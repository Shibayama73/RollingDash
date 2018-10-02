//============================================================//
//*���@�O	PlayStage2Scene.h
//*���@�e	�Q�[���v���C�X�e�[�W�Q�V�[��
//*���@�t	2017.7.30
//*�X�@�V	2017.7.30
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "SceneBase.h"
#include "..\..\Library\Devices\Devices.h"
#include <SpriteBatch.h>
#include "..\..\Library\Camera\Camera.h"
#include "..\..\Library\Camera\FollowCamera.h"
#include <SpriteFont.h>
#include <Effects.h>
#include <CommonStates.h>
#include "..\Objects\Object3D.h"
#include "..\Objects\CubeStage.h"
#include "..\Objects\Player.h"
#include "..\Objects\Enemy.h"
#include "..\Objects\ModelEffectManager.h"
#include "..\..\Library\Keyboards\Keyboards.h"
#include "..\Objects\Cube.h"
#include "..\..\Library\Collision\OBB2OBB\OBBCollision.h"
#include "..\..\Library\Collision\OBB2Sphere\OBB2SphereCollision.h"
#include "..\..\Library\Dialogs\Message.h"
#include "..\Objects\World.h"
#include "..\Objects\Heart.h"
#include "..\Objects\Shield.h"
#include "..\UI\LimitTime.h"
#include "..\UI\ShieldSum.h"

#include "..\..\Shaders\Emitters\ImpactEmitter.h"
#include "..\..\Shaders\Emitters\OverEmitter.h"
#include "..\..\Shaders\Emitters\ClearEmitter.h"
#include "..\..\Shaders\Emitters\GoalEmitter.h"

class PlayStage2Scene :public SceneBase
{
private:
	//	�V�[���h�̏o���ʒu
	static const DirectX::SimpleMath::Vector3 SHIELD_UP;
	//	�V�[���h�̌�����
	static const int SHIELD_MAX;
	//	�G�̐�����
	static const int ENEMY_MAX;
	//	�n�[�g�̃S�[���G���A�͈̔�(�~�̒��a)
	static const int GOAL_AREA;

public:
	PlayStage2Scene(int width, int height);
	int InitializeGame();
	int UpdateGame();
	void RenderGame();
	void Finalize();

private:
	//	�o�͕�
	int m_outputWidth;
	//	�o�͍���
	int m_outputHeight;

	//	�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//	�J����
	std::unique_ptr<FollowCamera> m_camera;
	//	�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	//	�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	//	�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_commonStates;

	//	���[���h
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
	//	�X�P�[��
	float m_scale;

	//	�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_winTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_loseTexture;

	//	�����̃X�e�[�W
	CubeStage* m_cubeStage;
	//	�v���C���[
	Player* m_player;
	//	�G
	std::vector<std::unique_ptr<Enemy>> m_enemy;
	//	���E
	World* m_worldStage;
	//	�n�[�g
	Heart* m_heart;
	//	�V�[���h
	std::vector<std::unique_ptr<Shield>> m_shield;
	//	��������
	LimitTime* m_limitTime;
	//	�V�[���h�̑����\��
	ShieldSum* m_shieldSum;

	//	���݂̎���
	int m_nowTime;
	//	�Q�[���N���A�t���O
	bool m_isClear;
	static bool m_justClear;	//�N���A�����Ƃ��Ɉ�x����true�ɂȂ�
								//	�Q�[���I�[�o�[�t���O
	bool m_isOver;
	static bool m_justOver;		//�Q�[���I�[�o�[�����Ƃ��Ɉ�x����true�ɂȂ�

	//	�^�C�}�[�J�n���ǂ���
	bool m_isTimer;
	//	�o�ߎ���
	int m_endTime;

	//	�Ռ��G�t�F�N�g�G�~�b�^
	std::unique_ptr<ImpactEmitter> m_impactEmitter;
	//	�Q�[���I�[�o�[�G�~�b�^
	std::unique_ptr<OverEmitter> m_overEmitter;
	//	�Q�[���N���A�G�~�b�^
	std::unique_ptr<ClearEmitter> m_clearEmitter;
	//	�S�[���G�~�b�^
	std::unique_ptr<GoalEmitter> m_goalEmitter;

};
