//============================================================//
//*名　前	GroundNode.h
//*内　容	OBB親子関係構築
//*日　付	2017.10.23
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "..\..\..\Game\Objects\Object3D.h"

class GroundNode
{
public:
	//	初期化
	virtual void Initialize() = 0;
	//	更新
	virtual void Update() = 0;
	//	描画
	virtual void Draw() = 0;

	//	親子関係構築
	void SetParent(Object3D* parent);

protected:
	//	デバッグ表示用オブジェクト
	Object3D m_model;

};
