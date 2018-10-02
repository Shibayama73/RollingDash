//============================================================//
//*���@�O	Devices.h
//*���@�e	�f�o�C�X���
//*���@�t	2017.7.6
//*�X�@�V	2017.7.6
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "..\Framework\pch.h"
#include <SimpleMath.h>

class Devices
{
private:
	Devices(){}

public:
	//	�C���X�^���X�̎擾
	static Devices& GetInstance(){
		if (device.get() == nullptr){
			device.reset(new Devices());
		}
		return *device.get();
	}

	//	�j������
	static void Dispose() {
		device.reset();
	}

	//	�E�B���h�E�n���h���̎擾
	HWND GetHandleWind() { return this->m_window; }
	//	�E�B���h�E���擾
	int GetWidth() { return this->m_outputWidth; }
	//	�E�B���h�E�����擾
	int GetHeight() { return this->m_outputHeight; }
	//	�f�o�C�X�擾
	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() { return this->m_d3dDevice; }
	//	�f�o�C�X�R���e�L�X�g�擾
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() { return this->m_d3dContext; }
	//	�X���b�v�`�F�[���擾
	Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() { return this->m_swapChain; }
	//	�����_�[�^�[�Q�b�g�擾
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() { return this->m_renderTargetView; }
	//	�f�v�X�X�e���V���r���[�擾
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() { return this->m_depthStencilView; }

	//	�E�B���h�E�n���h���̐ݒ�
	void SetHandleWind(HWND window) { this->m_window = window; }
	//	�E�B���h�E���ݒ�
	void SetWidth(int width) { this->m_outputWidth = width; }
	//	�E�B���h�E�����ݒ�
	void SetHeight(int height) { this->m_outputHeight = height; }
	//	�f�o�C�X�ݒ�
	void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device) { this->m_d3dDevice = device; }
	//	�f�o�C�X�R���e�L�X�g�ݒ�
	void SetDeviceContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context) { this->m_d3dContext = context; }
	//	�X���b�v�`�F�[���ݒ�
	void SetSwapChain(Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain) { this->m_swapChain = swapChain; }
	//	�����_�[�^�[�Q�b�g�ݒ�
	void SetRenderTargetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> targetView) { this->m_renderTargetView = targetView; }
	//	�f�v�X�X�e���V���r���[�ݒ�
	void SetDepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView) { this->m_depthStencilView = depthStencilView; }

	//	�f�o�C�X����
	void CreateDevice();
	//	���\�[�X����
	void CreateResources();
	//	�f�o�C�X������ꂽ��
	void OnDeviceLost();

private:
	//	�f�o�C�X���
	static std::unique_ptr<Devices> device;
	//	�E�B���h�E�̕��ƍ���
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
