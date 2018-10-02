//============================================================//
//*名　前	Emitter.h
//*内　容	エフェクトを発生させる
//*日　付	2018.7.18
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "ParticleEffectManager.h"

class Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	Emitter(Vector3 position);
	virtual void Update() = 0;

	//	テクスチャ読込み
	static void LoadTexture(int textureSlot, const wchar_t* filename);
	// 指定範囲の乱数を取得
	float RandomRange(float min_value, float max_value);
	// 指定範囲の乱数を取得
	int RandomRangInt(int min_value, int max_value);

	//	座標の設定
	void SetPosition(Vector3 position) { m_Position = position; }

	//	速度のアクセッサ
	void SetVelocity(Vector3 velocity) { m_Velocity = velocity; }
	//	発生制限時間
	void SetOccurLimitTime(float occurLimitTime) { m_occurLimitTime = occurLimitTime; }

protected:
	//	テクスチャ番号
	static int s_TextureSlot;
	//	座標
	Vector3 m_Position;
	//	速度
	Vector3 m_Velocity;
	//	角度
	float m_Param;
	//	発生制限時間
	float m_occurLimitTime;
	//	現在の発生時間
	float m_occurNowTime;

};
