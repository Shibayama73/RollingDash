//============================================================//
//*名　前	ResultScene.h
//*内　容	リザルトシーン
//*日　付	2018.5.24
//*更　新	2018.5.24
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "SceneBase.h"
#include <SpriteBatch.h>
#include <CommonStates.h>
#include "..\..\Library\Devices\Devices.h"
#include "..\..\Library\Files\FileIO.h"
#include "..\Objects\World.h"
#include "..\Objects\Cube.h"

class ResultScene :public SceneBase
{
private:
	//	座標
	static const float POS_X;
	static const float POS_Y;

public:
	ResultScene(int width, int height);
	~ResultScene();
	int InitializeGame();
	int UpdateGame();
	void RenderGame();
	void Finalize();

private:
	//	出力幅
	int m_outputWidth;
	//	出力高さ
	int m_outputHeight;

	//	カメラ
	std::unique_ptr<Camera> m_camera;
	//	スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//	テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TexResult;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TexNumber;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TexMinutes;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TexKey;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TexKey1;

	//	ファイル読み込み
	FileIO* m_fileInput;

	//	世界ステージ
	World* m_worldStage;
	//	立方体
	Cube* m_cubeRight;
	Cube* m_cubeLeft;

	//	タイマー開始かどうか
	bool m_isTimer;
	//	経過時間
	int m_endTime;

};
