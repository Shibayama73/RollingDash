//============================================================//
//*���@�O	TitleScene.h
//*���@�e	�^�C�g���V�[��
//*���@�t	2017.12.05
//*�X�@�V	2017.12.05
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

class TitleScene :public SceneBase
{
private:
	enum SELECT
	{
		START,
		END,
		NUM
	};

public:
	TitleScene(int width, int height);
	~TitleScene();
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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_startTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_start1Texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_endTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_end1Texture;

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

};
