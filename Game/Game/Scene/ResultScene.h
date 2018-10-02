//============================================================//
//*���@�O	ResultScene.h
//*���@�e	���U���g�V�[��
//*���@�t	2018.5.24
//*�X�@�V	2018.5.24
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "SceneBase.h"
#include <SpriteBatch.h>
#include <CommonStates.h>
#include "..\..\Library\Devices\Devices.h"
#include "..\..\Library\Files\FileIO.h"
#include "..\Objects\World.h"
#include "..\Objects\Cube.h"

class ResultScene :public SceneBase
{
private:
	//	���W
	static const float POS_X;
	static const float POS_Y;

public:
	ResultScene(int width, int height);
	~ResultScene();
	int InitializeGame();
	int UpdateGame();
	void RenderGame();
	void Finalize();

private:
	//	�o�͕�
	int m_outputWidth;
	//	�o�͍���
	int m_outputHeight;

	//	�J����
	std::unique_ptr<Camera> m_camera;
	//	�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//	�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TexResult;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TexNumber;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TexMinutes;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TexKey;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TexKey1;

	//	�t�@�C���ǂݍ���
	FileIO* m_fileInput;

	//	���E�X�e�[�W
	World* m_worldStage;
	//	������
	Cube* m_cubeRight;
	Cube* m_cubeLeft;

	//	�^�C�}�[�J�n���ǂ���
	bool m_isTimer;
	//	�o�ߎ���
	int m_endTime;

};
