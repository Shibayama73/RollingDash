//============================================================//
//*���@�O	GameMain.h
//*���@�e	���C��(���ƂȂ�Ƃ���)
//*���@�t	2017.7.13
//*�X�@�V	2017.7.13
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "Game.h"
#include "..\..\Game\Scene\SceneManager.h"

class Game;

class GameMain :public Game
{
public:
	GameMain(int width, int height);
	//	������
	int Initialize();
	//	��ʃT�C�Y�擾
	void GetDefaultSize(int& width, int& height);
	//	�쓮
	void Tick();
	//	�X�V
	void Update();
	//	�`��
	void Render();

private:
	Game* m_game;
	SceneManager* m_sceneManager;

};
