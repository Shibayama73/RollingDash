//============================================================//
//*名　前	PlayStage2Scene.h
//*内　容	ゲームプレイステージ２シーン
//*日　付	2017.7.30
//*更　新	2017.7.30
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "SceneBase.h"
#include "..\..\Library\Devices\Devices.h"
#include <SpriteBatch.h>
#include "..\..\Library\Camera\Camera.h"
#include "..\..\Library\Camera\FollowCamera.h"
#include <SpriteFont.h>
#include <Effects.h>
#include <CommonStates.h>
#include "..\Objects\Object3D.h"
#include "..\Objects\CubeStage.h"
#include "..\Objects\Player.h"
#include "..\Objects\Enemy.h"
#include "..\Objects\ModelEffectManager.h"
#include "..\..\Library\Keyboards\Keyboards.h"
#include "..\Objects\Cube.h"
#include "..\..\Library\Collision\OBB2OBB\OBBCollision.h"
#include "..\..\Library\Collision\OBB2Sphere\OBB2SphereCollision.h"
#include "..\..\Library\Dialogs\Message.h"
#include "..\Objects\World.h"
#include "..\Objects\Heart.h"
#include "..\Objects\Shield.h"
#include "..\UI\LimitTime.h"
#include "..\UI\ShieldSum.h"

#include "..\..\Shaders\Emitters\ImpactEmitter.h"
#include "..\..\Shaders\Emitters\OverEmitter.h"
#include "..\..\Shaders\Emitters\ClearEmitter.h"
#include "..\..\Shaders\Emitters\GoalEmitter.h"

class PlayStage2Scene :public SceneBase
{
private:
	//	シールドの出現位置
	static const DirectX::SimpleMath::Vector3 SHIELD_UP;
	//	シールドの個数制限
	static const int SHIELD_MAX;
	//	敵の数制限
	static const int ENEMY_MAX;
	//	ハートのゴールエリアの範囲(円の直径)
	static const int GOAL_AREA;

public:
	PlayStage2Scene(int width, int height);
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
	std::unique_ptr<FollowCamera> m_camera;
	//	フォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	//	エフェクトファクトリ
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	//	コモンステート
	std::unique_ptr<DirectX::CommonStates> m_commonStates;

	//	ワールド
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
	//	スケール
	float m_scale;

	//	テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_winTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_loseTexture;

	//	立方体ステージ
	CubeStage* m_cubeStage;
	//	プレイヤー
	Player* m_player;
	//	敵
	std::vector<std::unique_ptr<Enemy>> m_enemy;
	//	世界
	World* m_worldStage;
	//	ハート
	Heart* m_heart;
	//	シールド
	std::vector<std::unique_ptr<Shield>> m_shield;
	//	制限時間
	LimitTime* m_limitTime;
	//	シールドの総数表示
	ShieldSum* m_shieldSum;

	//	現在の時間
	int m_nowTime;
	//	ゲームクリアフラグ
	bool m_isClear;
	static bool m_justClear;	//クリアしたときに一度だけtrueになる
								//	ゲームオーバーフラグ
	bool m_isOver;
	static bool m_justOver;		//ゲームオーバーしたときに一度だけtrueになる

	//	タイマー開始かどうか
	bool m_isTimer;
	//	経過時間
	int m_endTime;

	//	衝撃エフェクトエミッタ
	std::unique_ptr<ImpactEmitter> m_impactEmitter;
	//	ゲームオーバーエミッタ
	std::unique_ptr<OverEmitter> m_overEmitter;
	//	ゲームクリアエミッタ
	std::unique_ptr<ClearEmitter> m_clearEmitter;
	//	ゴールエミッタ
	std::unique_ptr<GoalEmitter> m_goalEmitter;

};
