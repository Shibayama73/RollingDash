//============================================================//
//*名　前	ModelEffectManager.h
//*内　容	モデルエフェクトの管理
//*日　付	2017.8.01
//*更　新	2017.8.01
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <list>
#include "Object3D.h"

class ModelEffectManager
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	// シングルトンインスタンスの取得
	static ModelEffectManager* getInstance();
	// 破棄
	void Dispose();
	// 発生させる
	void Entry(const wchar_t*filename, int frame, Vector3 position, Vector3 velocity, Vector3 accel, Vector3 start_rotation, Vector3 end_rotation, Vector3 start_scale, Vector3 end_scale);
	void Update();
	void Draw();
private:
	ModelEffectManager();	

	// エフェクト1個分
	class ModelEffect
	{
	public:
		ModelEffect()
		{
			frame = 0;
			num_frame = 0;
		}

		bool Update(const Vector3& gravity);

		// オブジェクト
		Object3D object;
		// 座標
		Vector3 position;
		// 速度
		Vector3 velocity;
		// 加速度
		Vector3 accel;
		// 初期値
		Vector3 s_rotation;
		Vector3 s_scale;
		// 最終値
		Vector3 e_rotation;
		Vector3 e_scale;
		// 現在フレーム
		int   frame;
		// 終了フレーム
		int   num_frame;
	};

	// モデルエフェクトの配列
	std::list<ModelEffect> modelEffects;
	// 重力加速度
	Vector3 gravity;
};
