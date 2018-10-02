//============================================================//
//*���@�O	Window.h
//*���@�e	�E�B���h�E
//*���@�t	2017.8.29
//*�X�@�V	2017.8.29
//*�����	N.Shibayama
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

	//	������
	int Initialize(int width, int height);

	HWND HWnd() { return this->hWnd; }

	//	�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND hWnd;
	HINSTANCE hInstance;
	int nCmdShow;

};