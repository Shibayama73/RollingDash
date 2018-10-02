//============================================================//
//*���@�O	SceneManager.cpp
//*���@�e	�V�[���}�l�[�W���[
//*���@�t	2017.12.06
//*�X�@�V	2017.12.06
//*�����	N.Shibayama
//============================================================//
#include "SceneManager.h"

SceneManager::SceneManager(int width, int height) :m_outputWidth(width), m_outputHeight(height)
{
	//	�^�C�g���V�[������
	m_scene = new TitleScene(width, height);
}

SceneManager::~SceneManager()
{
}

void SceneManager::Scene()
{
	int next_scene;
	next_scene = m_scene->UpdateGame();
	if (m_scene->m_sceneBase != next_scene)
	{
		switch (next_scene)
		{
		case SCENE::TITLE:
			m_scene = new TitleScene(m_outputWidth, m_outputHeight);
			m_scene->InitializeGame();
			break;
		case SCENE::STAGE_SELECT:
			m_scene = new StageSelectScene(m_outputWidth, m_outputHeight);
			m_scene->InitializeGame();
			break;
		case SCENE::PLAY_STAGE1:
			m_scene = new PlayStage1Scene(m_outputWidth, m_outputHeight);
			m_scene->InitializeGame();
			break;
		case SCENE::PLAY_STAGE2:
			m_scene = new PlayStage2Scene(m_outputWidth, m_outputHeight);
			m_scene->InitializeGame();
			break;
		case SCENE::RESULT:
			m_scene = new ResultScene(m_outputWidth, m_outputHeight);
			m_scene->InitializeGame();
			break;
		}
	}
}

void SceneManager::Output()
{
	m_scene->RenderGame();
}
