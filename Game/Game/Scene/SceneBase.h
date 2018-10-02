//==========================================================================================//
//*���@�O	SceneBase
//*���@�e	�V�[���x�[�X
//*���@�t	2017.7.13
//*�X�@�V	2017.7.13
//*�����	N.Shibayama
//*�ǁ@�L	�J�ڂ�ǉ�����Ȃ�ABase���p�����v���C�Ɠ����悤�ɂ���AGameMain�ŊǗ�����
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
