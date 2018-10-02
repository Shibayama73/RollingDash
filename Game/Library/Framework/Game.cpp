//============================================================//
//*名　前	Game.cpp
//*内　容	ゲーム
//*日　付	2017.8.29
//*更　新	2017.8.29
//*制作者	N.Shibayama
//============================================================//
#include "pch.h"
#include "Game.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

Game::Game(int width, int height)
	:hWnd(0),m_outputWidth(width),m_outputHeight(height),m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
	//	スタートアップ情報
	STARTUPINFO si{};
	//	インスタンス取得
	this->hInstance = ::GetModuleHandle(NULL);

	//	StartupInfo構造体の内容取得
	::GetStartupInfo(&si);
	this->nCmdShow = si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow :
		SW_SHOWDEFAULT;;

	//	ウィンドウオブジェクト生成
	this->m_window = std::make_unique<Window>(this->hInstance, this->nCmdShow);

}

void Game::Initialize()
{
	//	ウィンドウオブジェクトの初期化
	this->m_window->Initialize(this->m_outputWidth, this->m_outputHeight);
	//	ウィンドウハンドル取得
	this->hWnd = this->m_window->HWnd();
	//	デバイスクラスのインスタンス取得
	auto& devices = Devices::GetInstance();
	devices.SetHandleWind(this->hWnd);
	devices.SetWidth(this->m_outputWidth);
	devices.SetHeight(this->m_outputHeight);

	//	デバイス生成
	devices.CreateDevice();
	//	リソース生成
	devices.CreateResources();

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.

}

void Game::Run()
{
	//	ゲーム更新
	this->m_timer.Tick([&](){this->Update(this->m_timer); });
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.

}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }
    // TODO: Add your rendering code here.

}

// Helper method to clear the back buffers.
void Game::Clear()
{
	//	デバイスクラスのインスタンス取得
	auto& devices = Devices::GetInstance();
    // Clear the views.
	devices.GetDeviceContext()->ClearRenderTargetView(devices.GetRenderTargetView().Get(), Colors::DeepSkyBlue);
    devices.GetDeviceContext()->ClearDepthStencilView(devices.GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    devices.GetDeviceContext()->OMSetRenderTargets(1, devices.GetRenderTargetView().GetAddressOf(), devices.GetDepthStencilView().Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    devices.GetDeviceContext()->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
	//	デバイスクラスのインスタンス取得
	auto& devices = Devices::GetInstance();
	HRESULT hr = devices.GetSwapChain()->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
		devices.OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

void Game::DrawFPS()
{
	//	FPS文字列生成
	std::wstring fpsString = L"fps = " + std::to_wstring((unsigned int)this->m_timer.GetFramesPerSecond());
	//	FPS描画
//	this->m_spriteFont->DrawString(m_spriteBatch.get(), fpsString.c_str(), SimpleMath::Vector2(0, 0), Colors::White);
}

void Game::Finalize()
{
	//	デバイスオブジェクト削除
	Devices::Dispose();
	//	ウィンドウオブジェクト削除
	m_window.reset();
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    Devices::GetInstance().CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

void ExitGame() {
	PostQuitMessage(0);
}
