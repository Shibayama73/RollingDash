//============================================================//
//*名　前	Game.h
//*内　容	ゲーム
//*日　付	2017.8.29
//*更　新	2017.8.29
//*制作者	N.Shibayama
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

	//	ゲームループの実行
	void Run();
	//	終了する
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
	//	インスタンスハンドル
	HINSTANCE hInstance;
	//	実行時のウィンドウの大きさ
	int nCmdShow;

	//	デバイスリソース.
	HWND hWnd;
	//	出力幅
	int m_outputWidth;
	//	出力高さ
	int m_outputHeight;
	//	レベル
	D3D_FEATURE_LEVEL m_featureLevel;
	// Rendering loop timer.
	DX::StepTimer m_timer;
	//	デバイス
	std::unique_ptr<Devices> devices;
	//	ウィンドウ
	std::unique_ptr<Window> m_window;

};
