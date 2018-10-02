//============================================================//
//*���@�O	StageSelectScene.h
//*���@�e	�X�e�[�W�Z���N�g�V�[��
//*���@�t	2018.7.27
//*�X�@�V	2018.7.27
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "SceneBase.h"
#include <SpriteBatch.h>
#include <CommonStates.h>
#include "..\..\Library\Devices\Devices.h"
#include "..\..\Library\Camera\Camera.h"
#include "..\..\Game\Objects\World.h"
#include "..\..\Game\Objects\Cube.h"

class StageSelectScene :public SceneBase
{
private:
	enum SELECT
	{
		STAGE_1,
		STAGE_2,
		NUM
	};

public:
	StageSelectScene(int width, int height);
	~StageSelectScene();
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
	std::unique_ptr<Camera> m_camera;
	//	�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stage1Texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stage2Texture;

	//	���E�X�e�[�W
	World* m_worldStage;
	//	������
	Cube* m_cubeRight;
	Cube* m_cubeLeft;
	//	�I��
	int m_select;
	//	�^�C�}�[�J�n���ǂ���
	bool m_isTimer;
	//	�o�ߎ���
	int m_endTime;
	//	�_��
	uint8_t m_blinkMask;

};
