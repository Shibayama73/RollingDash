//============================================================//
//*名　前	TitleScene.h
//*内　容	タイトルシーン
//*日　付	2017.12.05
//*更　新	2017.12.05
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "SceneBase.h"
#include <SpriteBatch.h>
#include <CommonStates.h>
#include "..\..\Library\Devices\Devices.h"
#include "..\..\Library\Camera\Camera.h"
#include "..\..\Game\Objects\World.h"
#include "..\..\Game\Objects\Cube.h"

class TitleScene :public SceneBase
{
private:
	enum SELECT
	{
		START,
		END,
		NUM
	};

public:
	TitleScene(int width, int height);
	~TitleScene();
	int InitializeGame();
	int UpdateGame();
	void RenderGame();
	void Finalize();

private:
	//	出力幅
	int m_outputWidth;
	//	出力高さ
	int m_outputHeight;

	//	スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//	カメラ
	std::unique_ptr<Camera> m_camera;
	//	テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_startTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_start1Texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_endTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_end1Texture;

	//	世界ステージ
	World* m_worldStage;
	//	立方体
	Cube* m_cubeRight;
	Cube* m_cubeLeft;
	//	選択
	int m_select;
	//	タイマー開始かどうか
	bool m_isTimer;
	//	経過時間
	int m_endTime;

};
