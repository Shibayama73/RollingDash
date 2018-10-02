//============================================================//
//*名　前	ParticleEffectManager.h
//*内　容	パーティクルエフェクトを管理する
//*日　付	2018.7.18
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <vector>
#include <Windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <simplemath.h>
#include <PrimitiveBatch.h>
#include <CommonStates.h>
#include <map>
#include "VertexTypes.h"
#include "..\..\Library\Devices\Devices.h"
#include "..\..\Library\Camera\Camera.h"
#include "ParticleInformation.h"

class ParticleEffectManager
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;

	//	パーティクルの最大数
	static const int PARTICLE_NUM_MUX;
	//	入力レイアウトの定義
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//	コンスタントバッファ
	struct Constants {
		//	ワールドビュープロジェクション合成行列
		DirectX::SimpleMath::Matrix WVP;
		//	ビルボード行列
		DirectX::SimpleMath::Matrix Billboard;
	};
	//	点の数
	static const int POINT_NUM;

	//	インスタンス取得
	static ParticleEffectManager* GetInstance();

	//	初期化
	void Initialize();
	//	更新
	void Update();
	//	描画
	void Draw();

	//	テクスチャ読込み
	void Load(int texnumber, const wchar_t* filename);

	//	パーティクルの登録(テクスチャ番号、座標、最後の座標、速度、色、最後の色、大きさ、最後の大きさ、回転角度、最後の回転角度、消滅時間)
	void Entry(
		int textureSlot,
		Vector3 pos, Vector3 endPos,
		Vector3 velocity,
		Vector4 color, Vector4 endColor,
		float scale, float endScale,
		float rotation, float endRotation,
		float extinctTime
	);

	//	アクセッサ
	void SetCamera(Camera* camera) { m_Camera = camera; }

protected:
	//	頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	//	ジオメトリシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;
	//	ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_PrimitiveBatch;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	//	汎用描画設定
	std::unique_ptr<DirectX::CommonStates> m_CommonStates;
	//	コンスタントバッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;
	//	テクスチャ
	std::map<int, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_Texture;
	//	テクスチャサンプラー
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
	// 減算描画用のブレンドステート
	ID3D11BlendState* s_pBlendState;

	// デバッグカメラ
	Camera* m_Camera;
	//	パーティクル情報配列
	std::vector<ParticleInformation> m_ParticleInfo;
	//	テクスチャ番号
	int m_TextureSlot;

};
