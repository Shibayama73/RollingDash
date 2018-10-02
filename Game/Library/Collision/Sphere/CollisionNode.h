//============================================================//
//*名　前	CollisionNode.h
//*内　容	球当たり判定ノード
//*日　付	2017.9.20
//*更　新	2018.5.10
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\..\..\Game\Objects\Object3D.h"

class CollisionNode
{
public:
	//	デバッグ表示フラグ取得
	static bool GetDebugVisible() { return m_debugVisible; }
	//	デバッグ表示フラグセット
	static void SetDebugVisible(bool visible) { m_debugVisible = visible; }

protected:
	//	デバッグフラグ表示ON
	static bool m_debugVisible;

public:
	//	初期化
	virtual void Initialize() = 0;
	//	更新
	virtual void Update() = 0;
	//	描画
	virtual void Draw() = 0;

	//	親子関係構築
	void SetParent(Object3D* parent);
	//	親からのオフセット
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_trans = trans; }


protected:
	//	デバッグ表示用オブジェクト
	Object3D m_object;
	//	親からのオフセット
	DirectX::SimpleMath::Vector3 m_trans;

};
