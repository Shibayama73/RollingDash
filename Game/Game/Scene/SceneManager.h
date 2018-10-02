//============================================================//
//*名　前	SceneManager.h
//*内　容	シーンマネージャー
//*日　付	2017.12.06
//*更　新	2017.12.06
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include "SceneBase.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "PlayStage1Scene.h"
#include "PlayStage2Scene.h"
#include "ResultScene.h"

class SceneManager
{
public:
	enum SCENE
	{
		TITLE,
		STAGE_SELECT,
		PLAY_STAGE1,
		PLAY_STAGE2,
		RESULT,
	};

public:
	SceneManager(int width, int height);
	~SceneManager();
	void Scene();
	void Output();
	SceneBase* m_scene;

private:
	//	出力幅
	int m_outputWidth;
	//	出力高さ
	int m_outputHeight;

};
