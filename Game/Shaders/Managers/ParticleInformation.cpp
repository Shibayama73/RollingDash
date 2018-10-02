//============================================================//
//*名　前	ParticleInformation.cpp
//*内　容	パーティクル情報
//*日　付	2018.7.18
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#include "ParticleInformation.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

ParticleInformation::ParticleInformation()
{
	m_Vertices.position = Vector3(0, 0, 0);
	m_Vertices.color = Vector4(255, 255, 255, 1);
	m_Vertices.textureCoordinate.x = float(1.0f);
	m_Vertices.textureCoordinate.y = float(0.0f);
	m_nowTime = 0.0f;
	m_extinctTime = 0.0f;

}

void ParticleInformation::Update()
{
	//	時間更新(1フレームずつ)
	m_nowTime++;

	//	速度による移動
	m_Vertices.position.x += m_velocity.x;
	m_Vertices.position.y += m_velocity.y;
	m_Vertices.position.z += m_velocity.z;

}
//*設定関数============================================================
//	テクスチャ番号設定
void ParticleInformation::SetTextureSlot(int textureSlot)
{
	m_textureSlot = textureSlot;
}

//	座標設定
void ParticleInformation::SetPosition(DirectX::SimpleMath::Vector3 postion)
{
	m_Vertices.position = postion;
}

//	最後の座標設定
void ParticleInformation::SetEndPosition(Vector3 position)
{
	m_endPosition = position;
}

//	速度設定
void ParticleInformation::SetVelocity(Vector3 velocity)
{
	m_velocity = velocity;
}

//	色設定
void ParticleInformation::SetColor(DirectX::SimpleMath::Vector4 color)
{
	m_Vertices.color = color;
}

//	最後の色設定
void ParticleInformation::SetEndColor(Vector4 color)
{
	m_endColor = color;
}

//	大きさ設定
void ParticleInformation::SetScale(float scale)
{
	m_Vertices.textureCoordinate.x = scale;
}

//	最後の大きさ取得
void ParticleInformation::SetEndScale(float scale)
{
	m_endScale = scale;
}

//	角度設定
void ParticleInformation::SetRotation(float rotation)
{
	m_Vertices.textureCoordinate.y = rotation;
}

//	最後の角度設定
void ParticleInformation::SetEndRotation(float rotation)
{
	m_endRotation = rotation;
}

//	消滅時間設定
void ParticleInformation::SetExtinctTime(float extinctTime)
{
	m_extinctTime = extinctTime;
}

//*取得関数============================================================
//	テクスチャ番号取得
int ParticleInformation::GetTextureSlot()
{
	return m_textureSlot;
}

//	頂点データ取得
DirectX::VertexPositionColorTexture ParticleInformation::GetVertices()
{
	return m_Vertices;
}

//	座標取得information
Vector3 ParticleInformation::GetPosition()
{
	return m_Vertices.position;
}

//	最後の座標取得
Vector3 ParticleInformation::GetEndPosition()
{
	return m_endPosition;
}

//	速度取得
Vector3 ParticleInformation::GetVelocity()
{
	return m_velocity;
}

//	色取得
Vector4 ParticleInformation::GetColor()
{
	return m_Vertices.color;
}

//	最後の色取得
Vector4 ParticleInformation::GetEndColor()
{
	return m_endColor;
}

//	大きさ取得
float ParticleInformation::GetScale()
{
	return m_Vertices.textureCoordinate.x;
}

//	最後の大きさ取得
float ParticleInformation::GetEndScale()
{
	return m_endScale;
}

//	回転角度の取得
float ParticleInformation::GetRotation()
{
	return m_Vertices.textureCoordinate.y;
}

//	最後の回転角度の取得
float ParticleInformation::GetEndRotation()
{
	return m_endRotation;
}

//	現在時間取得
float ParticleInformation::GetNowTime()
{
	return m_nowTime;
}

//	消滅時間取得
float ParticleInformation::GetExtinctTime()
{
	return m_extinctTime;
}
