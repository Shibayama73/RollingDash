//============================================================//
//*名　前	StageSelectScene.h
//*内　容	ステージセレクトシーン
//*日　付	2018.7.27
//*更　新	2018.7.27
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

class StageSelectScene :public SceneBase
{
private:
	enum SELECT
	{
		STAGE_1,
		STAGE_2,
		NUM
	};

public:
	StageSelectScene(int width, int height);
	~StageSelectScene();
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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stage1Texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stage2Texture;

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
	//	点滅
	uint8_t m_blinkMask;

};
