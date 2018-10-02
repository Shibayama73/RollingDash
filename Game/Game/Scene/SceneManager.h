//============================================================//
//*���@�O	SceneManager.h
//*���@�e	�V�[���}�l�[�W���[
//*���@�t	2017.12.06
//*�X�@�V	2017.12.06
//*�����	N.Shibayama
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
	//	�o�͕�
	int m_outputWidth;
	//	�o�͍���
	int m_outputHeight;

};
