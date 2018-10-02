//==========================================================================================//
//*名　前	SceneBase
//*内　容	シーンベース
//*日　付	2017.7.13
//*更　新	2017.7.13
//*制作者	N.Shibayama
//*追　記	遷移を追加するなら、Baseを継承しプレイと同じようにつくり、GameMainで管理する
//==========================================================================================//
#pragma once

class SceneBase
{
protected:
	int m_TimeCnt = 0;
	int m_NextScene = 0;

public:
	virtual ~SceneBase() {}
	virtual int InitializeGame() = 0;
	virtual int UpdateGame() = 0;
	virtual void RenderGame() = 0;
	virtual void Finalize() = 0;
	int m_sceneBase = 0;

};
