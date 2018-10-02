//============================================================//
//*���@�O	ParticleEffectManager.cpp
//*���@�e	�p�[�e�B�N���G�t�F�N�g���Ǘ�����N���X
//*���@�t	2018.7.18
//*�X�@�V	2018.7.20
//*�����	N.Shibayama
//============================================================//
#include "ParticleEffectManager.h"
#include <WICTextureLoader.h>	//�e�N�X�`���ǂݍ��ݗp
#include "BinaryFile.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

//	�p�[�e�B�N���̍ő吔
const int ParticleEffectManager::PARTICLE_NUM_MUX = 10000;
//	�_�̐�
const int ParticleEffectManager::POINT_NUM = 200;

//	���̓��C�A�E�g�̒�`
const std::vector<D3D11_INPUT_ELEMENT_DESC> ParticleEffectManager::INPUT_LAYOUT = {
	{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	{ "COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,sizeof(Vector3),D3D11_INPUT_PER_VERTEX_DATA,0 },
	{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,sizeof(Vector3) + sizeof(Vector4),D3D11_INPUT_PER_VERTEX_DATA,0 },
};

ParticleEffectManager * ParticleEffectManager::GetInstance()
{
	static ParticleEffectManager instance;
	return &instance;
}

void ParticleEffectManager::Initialize()
{
	//	�J�����̏�����(�R���X�g���N�^��)
	m_Camera = nullptr;

	auto& devices = Devices::GetInstance();

	//	�R���p�C�����ꂽ�V�F�[�_�[�t�@�C���̓Ǎ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/VertexShader.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/GeometryShader.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/PixelShader.cso");

	//	���_�V�F�[�_�쐬
	if (FAILED(devices.GetDevice()->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateVertexShader Filed.", NULL, MB_OK);
		return;
	}
	//	�W�I���g���V�F�[�_�쐬
	if (FAILED(devices.GetDevice()->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateGeometryShader Filed.", NULL, MB_OK);
		return;
	}
	//	�s�N�Z���V�F�[�_�쐬
	if (FAILED(devices.GetDevice()->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreatePixelShader Filed.", NULL, MB_OK);
		return;
	}

	//	�v���~�e�B�u�o�b�`�쐬
	m_PrimitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(devices.GetDeviceContext().Get(), 1, PARTICLE_NUM_MUX);
	//	���_�t�H�[�}�b�g���w�肵�ē��̓��C�A�E�g�쐬
	devices.GetDevice()->CreateInputLayout(&INPUT_LAYOUT[0], INPUT_LAYOUT.size(), VSData.GetData(), VSData.GetSize(), m_InputLayout.GetAddressOf());

	//	�R���X�^���g�o�b�t�@�̐ݒ�(�V�F�[�_�ɋ��ʃf�[�^��n������)
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Constants);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	//	�R���X�^���g�o�b�t�@�̐���
	//	���s������
	if (FAILED(devices.GetDevice()->CreateBuffer(&cb, nullptr, m_ConstantBuffer.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateBuffer Filed.", NULL, MB_OK);
		return;
	}

	//	�ėp�`��ݒ�̐���
	m_CommonStates = std::make_unique<CommonStates>(devices.GetDevice().Get());

	//	�e�N�X�`���T���v���[����
	D3D11_SAMPLER_DESC sam;
	ZeroMemory(&sam, sizeof(sam));
	sam.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//sam.MaxAnisotropy = 4;
	//D3D11_TEXTURE_ADDRESS_WRAP
	//D3D11_TEXTURE_ADDRESS_CLAMP
	sam.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sam.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sam.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	if (FAILED(devices.GetDevice()->CreateSamplerState(&sam, m_Sampler.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateSamplerState Failed Filed.", NULL, MB_OK);
		return;
	}

	// ���Z�`��p�̃u�����h�X�e�[�g���쐬
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	devices.GetDevice()->CreateBlendState(&desc, &s_pBlendState);

	//	�e�N�X�`���ԍ�������
	m_TextureSlot = 0;
}

void ParticleEffectManager::Update()
{
	for (std::vector<ParticleInformation>::iterator it = m_ParticleInfo.begin();
		it != m_ParticleInfo.end();)
	{
		//	���Ŏ��ԂɂȂ�����
		if ((*it).GetNowTime() > (*it).GetExtinctTime())
		{
			//	����
			it = m_ParticleInfo.erase(it);
			//break;
		}
		else
		{
			(*it).Update();

			//	���ԎZ�o(�b)
			float time = (*it).GetNowTime() / (*it).GetExtinctTime();

			//	���W�ω�
			Vector3 pos = (1 - time / (*it).GetExtinctTime()*3.0f)*(*it).GetPosition() + (time / (*it).GetExtinctTime()*3.0f)*(*it).GetEndPosition();
			(*it).SetPosition(pos);

			//	�F�ω�
			//Vector4 color = (1 - time / (*it).GetExtinctTime())*(*it).GetColor() + (time / (*it).GetExtinctTime())*(*it).GetEndColor();
			Vector4 color = (1 - time / (*it).GetExtinctTime()*3.0f)*(*it).GetColor() + (time / (*it).GetExtinctTime()*3.0f)*(*it).GetEndColor();
			(*it).SetColor(color);

			//	�傫���ω�
			float scale = (1 - time / (*it).GetExtinctTime()*3.0f)*(*it).GetScale() + (time / (*it).GetExtinctTime()*3.0f)*(*it).GetEndScale();
			(*it).SetScale(scale);

			//	��]�p�x�ω�
			float rotation = (1 - time / (*it).GetExtinctTime()*3.0f)*(*it).GetRotation() + (time / (*it).GetExtinctTime()*3.0f)*(*it).GetEndRotation();
			(*it).SetRotation(rotation);
			it++;
		}
	}

}

void ParticleEffectManager::Draw()
{
	//if (m_Vertices.size() == 0)return; 
	if (m_ParticleInfo.size() == 0)return;

	//	�f�o�C�X�擾
	auto& devices = Devices::GetInstance();

	//	�R���X�^���g�o�b�t�@�ɓn���p�̍s��쐬
	Matrix world = Matrix::Identity;
	Matrix view = Matrix::Identity;
	Matrix proj = Matrix::Identity;

	//	�f�o�b�O�p
	world = Matrix::CreateScale(1.0f);

	//	�f�o�b�O�J�����̃r���[�v���W�F�N�V�����𔽉f
	//view = m_Camera->GetView();
	//proj = m_Camera->GetProj();
	view = m_Camera->GetViewMatrix();
	proj = m_Camera->GetProjectionMatrix();

	Matrix wvp = world * view * proj;

	//	�V�F�[�_�̃R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	//	����������
	if (SUCCEEDED(devices.GetDeviceContext()->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		Constants constants;
		constants.WVP = wvp;
		constants.Billboard = m_Camera->GetBillboard();
		//	�R�s�[����
		memcpy_s(pData.pData, pData.RowPitch, &constants, sizeof(constants));

		devices.GetDeviceContext()->Unmap(m_ConstantBuffer.Get(), 0);
	}

	//	���̃R���X�^���g�o�b�t�@���ǂ̃V�F�[�_�Ŏg����
	devices.GetDeviceContext()->VSSetConstantBuffers(0, 0, nullptr);
	devices.GetDeviceContext()->GSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());
	devices.GetDeviceContext()->PSSetConstantBuffers(0, 0, nullptr);

	//	�f�o�C�X�R���e�L�X�g�ɃV�F�[�_���Z�b�g
	devices.GetDeviceContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	devices.GetDeviceContext()->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	devices.GetDeviceContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	//	�f�o�C�X�R���e�L�X�g�ɓ��̓��C�A�E�g���Z�b�g
	devices.GetDeviceContext()->IASetInputLayout(m_InputLayout.Get());

	//	�A���t�@�u�����h�̐ݒ�
	//devices.GetDeviceContext()->OMSetBlendState(m_CommonStates->NonPremultiplied(), nullptr, 0xffffffff);

	//	���Z�����`��
	devices.GetDeviceContext()->OMSetBlendState(m_CommonStates->Additive(), nullptr, 0xffffffff);
	//	���Z�����`��
	//context->OMSetBlendState(s_pBlendState, nullptr, 0xffffffff);

	//	�[�x�e�X�g�̐ݒ�
	devices.GetDeviceContext()->OMSetDepthStencilState(m_CommonStates->DepthNone(), 0);
	//devices.GetDeviceContext()->OMSetDepthStencilState(m_CommonStates->DepthRead(), 0);

	//	�A�ʏ����̐ݒ�
	devices.GetDeviceContext()->RSSetState(m_CommonStates->CullNone());

	//	�e�N�X�`���T���v���[�ݒ�
	devices.GetDeviceContext()->PSSetSamplers(0, 1, m_Sampler.GetAddressOf());

	for (int i = 0; i < m_ParticleInfo.size(); i++)
	{
		m_TextureSlot = m_ParticleInfo[i].GetTextureSlot();	//�e�N�X�`���ԍ�
		//	�e�N�X�`�����V�F�[�_�ɓn��
		devices.GetDeviceContext()->PSSetShaderResources(0, 1, m_Texture[m_TextureSlot].GetAddressOf());

		m_PrimitiveBatch->Begin();
		m_PrimitiveBatch->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, &m_ParticleInfo[i].GetVertices(), 1);
		m_PrimitiveBatch->End();
	}

	//	�g���I������V�F�[�_��null
	devices.GetDeviceContext()->VSSetShader(nullptr, nullptr, 0);
	devices.GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);
	devices.GetDeviceContext()->PSSetShader(nullptr, nullptr, 0);

}

void ParticleEffectManager::Load(int texnumber, const wchar_t * filename)
{
	//	�f�o�C�X�擾
	auto& devices = Devices::GetInstance();

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> tex;

	//	�e�N�X�`���ǂݍ���
	if (FAILED(CreateWICTextureFromFile(devices.GetDevice().Get(), filename, nullptr, m_Texture[texnumber].ReleaseAndGetAddressOf())))
	{
		//	���s�����Ƃ��G���[�\��
		MessageBox(0, L"CreateTexture Failed Filed.", NULL, MB_OK);
		return;
	}

}

void ParticleEffectManager::Entry(int textureSlot, Vector3 pos, Vector3 endPos, Vector3 velocity, Vector4 color, Vector4 endColor, float scale, float endScale, float rotation, float endRotation, float extinctTime)
{
	ParticleInformation particleInfo;
	particleInfo.SetTextureSlot(textureSlot);
	particleInfo.SetPosition(pos);
	particleInfo.SetEndPosition(endPos);
	particleInfo.SetVelocity(velocity);
	particleInfo.SetColor(color);
	particleInfo.SetEndColor(endColor);
	particleInfo.SetScale(scale);
	particleInfo.SetEndScale(endScale);
	particleInfo.SetRotation(rotation);
	particleInfo.SetEndRotation(endRotation);
	particleInfo.SetExtinctTime(extinctTime);
	m_ParticleInfo.push_back(particleInfo);

}
