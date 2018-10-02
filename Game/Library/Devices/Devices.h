//============================================================//
//*名　前	Devices.h
//*内　容	デバイス情報
//*日　付	2017.7.6
//*更　新	2017.7.6
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\Framework\pch.h"
#include <SimpleMath.h>

class Devices
{
private:
	Devices(){}

public:
	//	インスタンスの取得
	static Devices& GetInstance(){
		if (device.get() == nullptr){
			device.reset(new Devices());
		}
		return *device.get();
	}

	//	破棄する
	static void Dispose() {
		device.reset();
	}

	//	ウィンドウハンドルの取得
	HWND GetHandleWind() { return this->m_window; }
	//	ウィンドウ幅取得
	int GetWidth() { return this->m_outputWidth; }
	//	ウィンドウ高さ取得
	int GetHeight() { return this->m_outputHeight; }
	//	デバイス取得
	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() { return this->m_d3dDevice; }
	//	デバイスコンテキスト取得
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() { return this->m_d3dContext; }
	//	スワップチェーン取得
	Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() { return this->m_swapChain; }
	//	レンダーターゲット取得
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() { return this->m_renderTargetView; }
	//	デプスステンシルビュー取得
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() { return this->m_depthStencilView; }

	//	ウィンドウハンドルの設定
	void SetHandleWind(HWND window) { this->m_window = window; }
	//	ウィンドウ幅設定
	void SetWidth(int width) { this->m_outputWidth = width; }
	//	ウィンドウ高さ設定
	void SetHeight(int height) { this->m_outputHeight = height; }
	//	デバイス設定
	void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device) { this->m_d3dDevice = device; }
	//	デバイスコンテキスト設定
	void SetDeviceContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context) { this->m_d3dContext = context; }
	//	スワップチェーン設定
	void SetSwapChain(Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain) { this->m_swapChain = swapChain; }
	//	レンダーターゲット設定
	void SetRenderTargetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> targetView) { this->m_renderTargetView = targetView; }
	//	デプスステンシルビュー設定
	void SetDepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView) { this->m_depthStencilView = depthStencilView; }

	//	デバイス生成
	void CreateDevice();
	//	リソース生成
	void CreateResources();
	//	デバイスが失われた時
	void OnDeviceLost();

private:
	//	デバイス情報
	static std::unique_ptr<Devices> device;
	//	ウィンドウの幅と高さ
	HWND m_window;
	int m_outputWidth;
	int m_outputHeight;

	Microsoft::WRL::ComPtr<ID3D11Device>			m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11Device1>			m_d3dDevice1;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>		m_d3dContext;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1>	m_d3dContext1;

	Microsoft::WRL::ComPtr<IDXGISwapChain>			m_swapChain;
	Microsoft::WRL::ComPtr<IDXGISwapChain1>			m_swapChain1;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_depthStencilView;
	D3D_FEATURE_LEVEL								m_featureLevel;

};
