//============================================================//
//*名　前	ShieldSum.h
//*内　容	シールドの数画像の表示
//*日　付	2018.7.02
//*更　新	2018.7.02
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <SpriteBatch.h>
#include <simplemath.h>

class ShieldSum
{
private:
	//	表示座標
	static const float NOW_POS_X;	//現在のシールド
	static const float NOW_POS_Y;	//現在のシールド
	static const float MAX_POS_X;	//最大のシールド
	static const float MAX_POS_Y;	//最大のシールド
	static const float SLASH_POS_X;	//斜線
	static const float SLASH_POS_Y;	//斜線

public:
	void Initialize();
	void Draw(std::unique_ptr<DirectX::SpriteBatch>& spriteBatch, int now_sum, int max);

private:
	//	テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shieldTex;	//シールド画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_slashTex;	//斜線
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_limitTex;	//現在のシールド数
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_maxTex;		//シールド最大数

};