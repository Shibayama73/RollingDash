//============================================================//
//*名　前	ParticleInformation.h
//*内　容	パーティクル情報
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
#include "VertexTypes.h"

class ParticleInformation
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;

public:
	ParticleInformation();
	void Update();

	//*設定関数==========================================
	//	テクスチャ番号設定
	void SetTextureSlot(int textureSlot);
	//	座標設定
	void SetPosition(Vector3 position);
	//	最後の座標設定
	void SetEndPosition(Vector3 position);
	//	速度設定
	void SetVelocity(Vector3 velocity);
	//	色設定
	void SetColor(Vector4 color);
	//	最後の色設定
	void SetEndColor(Vector4 color);
	//	大きさ設定
	void SetScale(float scale);
	//	最後の大きさ設定
	void SetEndScale(float scale);
	//	角度設定
	void SetRotation(float rotation);
	//	最後の角度設定
	void SetEndRotation(float rotation);

	//	消滅時間設定
	void SetExtinctTime(float extinctTime);

	//*取得関数==========================================
	//	テクスチャ番号取得
	int GetTextureSlot();
	//	頂点データ取得
	DirectX::VertexPositionColorTexture GetVertices();
	//	座標取得
	Vector3 GetPosition();
	//	最後の座標取得
	Vector3 GetEndPosition();
	//	速度取得
	Vector3 GetVelocity();
	//	色取得
	Vector4 GetColor();
	//	最後の色取得
	Vector4 GetEndColor();
	//	大きさ取得
	float GetScale();
	//	最後の大きさ取得
	float GetEndScale();
	//	回転角度の取得
	float GetRotation();
	//	最後の回転角度の取得
	float GetEndRotation();
	//	現在時間取得
	float GetNowTime();
	//	消滅時間取得
	float GetExtinctTime();

private:
	//	テクスチャ番号
	int m_textureSlot;
	//	頂点データ
	DirectX::VertexPositionColorTexture m_Vertices;
	//	速度
	Vector3 m_velocity;
	//	現在時間
	float m_nowTime;
	//	消滅時間
	float m_extinctTime;

	//	最後の座標
	Vector3 m_endPosition;
	//	最後の色
	DirectX::SimpleMath::Vector4 m_endColor;
	//	最後の大きさ
	float m_endScale;
	//	最後の回転角度
	float m_endRotation;

};
