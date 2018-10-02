//============================================================//
//*名　前	ParticleEffectManager.cpp
//*内　容	パーティクルエフェクトを管理するクラス
//*日　付	2018.7.18
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#include "ParticleEffectManager.h"
#include <WICTextureLoader.h>	//テクスチャ読み込み用
#include "BinaryFile.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

//	パーティクルの最大数
const int ParticleEffectManager::PARTICLE_NUM_MUX = 10000;
//	点の数
const int ParticleEffectManager::POINT_NUM = 200;

//	入力レイアウトの定義
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
	//	カメラの初期化(コンストラクタで)
	m_Camera = nullptr;

	auto& devices = Devices::GetInstance();

	//	コンパイルされたシェーダーファイルの読込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/VertexShader.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/GeometryShader.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/PixelShader.cso");

	//	頂点シェーダ作成
	if (FAILED(devices.GetDevice()->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateVertexShader Filed.", NULL, MB_OK);
		return;
	}
	//	ジオメトリシェーダ作成
	if (FAILED(devices.GetDevice()->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateGeometryShader Filed.", NULL, MB_OK);
		return;
	}
	//	ピクセルシェーダ作成
	if (FAILED(devices.GetDevice()->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreatePixelShader Filed.", NULL, MB_OK);
		return;
	}

	//	プリミティブバッチ作成
	m_PrimitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(devices.GetDeviceContext().Get(), 1, PARTICLE_NUM_MUX);
	//	頂点フォーマットを指定して入力レイアウト作成
	devices.GetDevice()->CreateInputLayout(&INPUT_LAYOUT[0], INPUT_LAYOUT.size(), VSData.GetData(), VSData.GetSize(), m_InputLayout.GetAddressOf());

	//	コンスタントバッファの設定(シェーダに共通データを渡すため)
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Constants);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	//	コンスタントバッファの生成
	//	失敗したら
	if (FAILED(devices.GetDevice()->CreateBuffer(&cb, nullptr, m_ConstantBuffer.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateBuffer Filed.", NULL, MB_OK);
		return;
	}

	//	汎用描画設定の生成
	m_CommonStates = std::make_unique<CommonStates>(devices.GetDevice().Get());

	//	テクスチャサンプラー生成
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

	// 減算描画用のブレンドステートを作成
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

	//	テクスチャ番号初期化
	m_TextureSlot = 0;
}

void ParticleEffectManager::Update()
{
	for (std::vector<ParticleInformation>::iterator it = m_ParticleInfo.begin();
		it != m_ParticleInfo.end();)
	{
		//	消滅時間になったら
		if ((*it).GetNowTime() > (*it).GetExtinctTime())
		{
			//	消す
			it = m_ParticleInfo.erase(it);
			//break;
		}
		else
		{
			(*it).Update();

			//	時間算出(秒)
			float time = (*it).GetNowTime() / (*it).GetExtinctTime();

			//	座標変化
			Vector3 pos = (1 - time / (*it).GetExtinctTime()*3.0f)*(*it).GetPosition() + (time / (*it).GetExtinctTime()*3.0f)*(*it).GetEndPosition();
			(*it).SetPosition(pos);

			//	色変化
			//Vector4 color = (1 - time / (*it).GetExtinctTime())*(*it).GetColor() + (time / (*it).GetExtinctTime())*(*it).GetEndColor();
			Vector4 color = (1 - time / (*it).GetExtinctTime()*3.0f)*(*it).GetColor() + (time / (*it).GetExtinctTime()*3.0f)*(*it).GetEndColor();
			(*it).SetColor(color);

			//	大きさ変化
			float scale = (1 - time / (*it).GetExtinctTime()*3.0f)*(*it).GetScale() + (time / (*it).GetExtinctTime()*3.0f)*(*it).GetEndScale();
			(*it).SetScale(scale);

			//	回転角度変化
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

	//	デバイス取得
	auto& devices = Devices::GetInstance();

	//	コンスタントバッファに渡す用の行列作成
	Matrix world = Matrix::Identity;
	Matrix view = Matrix::Identity;
	Matrix proj = Matrix::Identity;

	//	デバッグ用
	world = Matrix::CreateScale(1.0f);

	//	デバッグカメラのビュープロジェクションを反映
	//view = m_Camera->GetView();
	//proj = m_Camera->GetProj();
	view = m_Camera->GetViewMatrix();
	proj = m_Camera->GetProjectionMatrix();

	Matrix wvp = world * view * proj;

	//	シェーダのコンスタントバッファに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	//	成功したら
	if (SUCCEEDED(devices.GetDeviceContext()->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		Constants constants;
		constants.WVP = wvp;
		constants.Billboard = m_Camera->GetBillboard();
		//	コピーする
		memcpy_s(pData.pData, pData.RowPitch, &constants, sizeof(constants));

		devices.GetDeviceContext()->Unmap(m_ConstantBuffer.Get(), 0);
	}

	//	このコンスタントバッファをどのシェーダで使うか
	devices.GetDeviceContext()->VSSetConstantBuffers(0, 0, nullptr);
	devices.GetDeviceContext()->GSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());
	devices.GetDeviceContext()->PSSetConstantBuffers(0, 0, nullptr);

	//	デバイスコンテキストにシェーダをセット
	devices.GetDeviceContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	devices.GetDeviceContext()->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	devices.GetDeviceContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	//	デバイスコンテキストに入力レイアウトをセット
	devices.GetDeviceContext()->IASetInputLayout(m_InputLayout.Get());

	//	アルファブレンドの設定
	//devices.GetDeviceContext()->OMSetBlendState(m_CommonStates->NonPremultiplied(), nullptr, 0xffffffff);

	//	加算合成描画
	devices.GetDeviceContext()->OMSetBlendState(m_CommonStates->Additive(), nullptr, 0xffffffff);
	//	減算合成描画
	//context->OMSetBlendState(s_pBlendState, nullptr, 0xffffffff);

	//	深度テストの設定
	devices.GetDeviceContext()->OMSetDepthStencilState(m_CommonStates->DepthNone(), 0);
	//devices.GetDeviceContext()->OMSetDepthStencilState(m_CommonStates->DepthRead(), 0);

	//	陰面消去の設定
	devices.GetDeviceContext()->RSSetState(m_CommonStates->CullNone());

	//	テクスチャサンプラー設定
	devices.GetDeviceContext()->PSSetSamplers(0, 1, m_Sampler.GetAddressOf());

	for (int i = 0; i < m_ParticleInfo.size(); i++)
	{
		m_TextureSlot = m_ParticleInfo[i].GetTextureSlot();	//テクスチャ番号
		//	テクスチャをシェーダに渡す
		devices.GetDeviceContext()->PSSetShaderResources(0, 1, m_Texture[m_TextureSlot].GetAddressOf());

		m_PrimitiveBatch->Begin();
		m_PrimitiveBatch->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, &m_ParticleInfo[i].GetVertices(), 1);
		m_PrimitiveBatch->End();
	}

	//	使い終わったシェーダをnull
	devices.GetDeviceContext()->VSSetShader(nullptr, nullptr, 0);
	devices.GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);
	devices.GetDeviceContext()->PSSetShader(nullptr, nullptr, 0);

}

void ParticleEffectManager::Load(int texnumber, const wchar_t * filename)
{
	//	デバイス取得
	auto& devices = Devices::GetInstance();

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> tex;

	//	テクスチャ読み込み
	if (FAILED(CreateWICTextureFromFile(devices.GetDevice().Get(), filename, nullptr, m_Texture[texnumber].ReleaseAndGetAddressOf())))
	{
		//	失敗したときエラー表示
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
