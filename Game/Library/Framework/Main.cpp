//============================================================//
//*名　前	Main.cpp
//*内　容	メイン
//*日　付	2017.8.29
//*更　新	2017.8.29
//*制作者	N.Shibayama
//============================================================//
#include "pch.h"
#include "GameMain.h"
#include "Window.h"

using namespace DirectX;
using namespace std;

unique_ptr<GameMain> g_gameMain;
unique_ptr<Window> g_window;

// エントリポイント Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (!XMVerifyCPUSupport())
		return 1;
	// COMライブラリを初期化する
	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	if (FAILED(hr))
		return 1;

	int width = 1024;
	int height = 768;

	// Windowオブジェクトを生成する
	g_window = std::make_unique<Window>(hInstance, nCmdShow);
	// Gameオブジェクトを生成する
	g_gameMain = std::make_unique<GameMain>(width, height);
	// Windowオブジェクトを初期化する
	//g_window->Initialize(width, height);
	// Gameオブジェクトを初期化する
	g_gameMain->Initialize();

	// ゲームを更新する
	//MSG msg = g_game->Run();
	//g_gameMain->Tick();
	//	メッセージ
	MSG msg = {};

	//	ゲームループ
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//	ゲーム作動
			g_gameMain->Tick();
		}
	}

	// Windowオブジェクトを破棄する
	g_window.reset();
	// Gameオブジェクトを破棄する
	g_gameMain.reset();

	CoUninitialize();

	//return (int)msg.wParam;
	return 0;
}

