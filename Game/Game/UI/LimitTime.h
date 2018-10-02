//============================================================//
//*名　前	LimitTime.h
//*内　容	制限時間
//*日　付	2017.7.28
//*更　新	2017.7.28
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <SpriteBatch.h>
#include <simplemath.h>

class LimitTime
{
private:
	//	座標
	static const float POS_X;
	static const float POS_Y;

public:
	LimitTime(float limitTime);
	~LimitTime();
	
	//	初期化
	void Initialize();
	//	更新
	void Update();
	//	描画
	void Draw(std::unique_ptr<DirectX::SpriteBatch>& spriteBatch);
	//	リセット
	void Reset(float limitTime);
	//	時間を進める
	void Forward();
	//	時間を止める
	void Stop();
	//	タイムオーバーかどうか
	bool IsTimeOver();
	//	現在の時間
	float NowTime();
	//	フレーム秒の取得
	int GetTime();

private:
	//	制限時間
	float m_time;
	//	針を動かす
	bool m_isHand;

	//	テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

};