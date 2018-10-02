//============================================================//
//*名　前	Window.h
//*内　容	ウィンドウ
//*日　付	2017.8.29
//*更　新	2017.8.29
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <d3d11_1.h>
#include <Mouse.h>
#include <keyboard.h>
#include "Game.h"

class Window
{
public:
	Window(HINSTANCE hInstance,int nCmdShow):hInstance(hInstance),nCmdShow(nCmdShow){}

	//	初期化
	int Initialize(int width, int height);

	HWND HWnd() { return this->hWnd; }

	//	ウィンドウプロシージャ
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND hWnd;
	HINSTANCE hInstance;
	int nCmdShow;

};