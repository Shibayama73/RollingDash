//============================================================//
//*���@�O	Game.h
//*���@�e	�Q�[��
//*���@�t	2017.8.29
//*�X�@�V	2017.8.29
//*�����	N.Shibayama
//============================================================//
#pragma once

#include <d3d11_1.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Effects.h>
#include <CommonStates.h>
#include <Model.h>
#include <GeometricPrimitive.h>
#include <keyboard.h>

#include "StepTimer.h"
#include "Window.h"
#include "..\Devices\Devices.h"
#include "..\Camera\DebugCamera.h"
#include "..\..\Game\Objects\Object3D.h"
#include "..\Camera\Camera.h"

class Window;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:
	Game(int width, int height);

    // Initialization and management
    void Initialize();
	void Render();
	void Clear();
	void Present();

	//	�Q�[�����[�v�̎��s
	void Run();
	//	�I������
	void Finalize();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize(int& width, int& height ) const;

private:
    void Update(DX::StepTimer const& timer);
	void DrawFPS();

private:
	//	�C���X�^���X�n���h��
	HINSTANCE hInstance;
	//	���s���̃E�B���h�E�̑傫��
	int nCmdShow;

	//	�f�o�C�X���\�[�X.
	HWND hWnd;
	//	�o�͕�
	int m_outputWidth;
	//	�o�͍���
	int m_outputHeight;
	//	���x��
	D3D_FEATURE_LEVEL m_featureLevel;
	// Rendering loop timer.
	DX::StepTimer m_timer;
	//	�f�o�C�X
	std::unique_ptr<Devices> devices;
	//	�E�B���h�E
	std::unique_ptr<Window> m_window;

};
