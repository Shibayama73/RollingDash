//============================================================//
//*���@�O	Main.cpp
//*���@�e	���C��
//*���@�t	2017.8.29
//*�X�@�V	2017.8.29
//*�����	N.Shibayama
//============================================================//
#include "pch.h"
#include "GameMain.h"
#include "Window.h"

using namespace DirectX;
using namespace std;

unique_ptr<GameMain> g_gameMain;
unique_ptr<Window> g_window;

// �G���g���|�C���g Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (!XMVerifyCPUSupport())
		return 1;
	// COM���C�u����������������
	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	if (FAILED(hr))
		return 1;

	int width = 1024;
	int height = 768;

	// Window�I�u�W�F�N�g�𐶐�����
	g_window = std::make_unique<Window>(hInstance, nCmdShow);
	// Game�I�u�W�F�N�g�𐶐�����
	g_gameMain = std::make_unique<GameMain>(width, height);
	// Window�I�u�W�F�N�g������������
	//g_window->Initialize(width, height);
	// Game�I�u�W�F�N�g������������
	g_gameMain->Initialize();

	// �Q�[�����X�V����
	//MSG msg = g_game->Run();
	//g_gameMain->Tick();
	//	���b�Z�[�W
	MSG msg = {};

	//	�Q�[�����[�v
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//	�Q�[���쓮
			g_gameMain->Tick();
		}
	}

	// Window�I�u�W�F�N�g��j������
	g_window.reset();
	// Game�I�u�W�F�N�g��j������
	g_gameMain.reset();

	CoUninitialize();

	//return (int)msg.wParam;
	return 0;
}

