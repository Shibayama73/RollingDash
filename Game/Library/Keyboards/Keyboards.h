//============================================================//
//*���@�O	Keyboards.h
//*���@�e	�L�[�{�[�h
//*���@�t	2017.8.28
//*�X�@�V	2017.8.28
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "..\Framework\pch.h"
#include <keyboard.h>
#include <memory>
#include <string>
#include "KeyConvertList.h"

class Keyboards
{
private:
	//	�R���X�g���N�^
	Keyboards(){}
	//	�L�[�{�[�h�̐���
	void CreateKeyboard();

public:
	//	�C���X�^���X�擾
	static Keyboards& GetInstance() {
		if (keyboard.get() == nullptr) {
			keyboard.reset(new Keyboards());
			keyboard->CreateKeyboard();
		}
		return *keyboard.get();
	}

	//	�j������
	static void Dispose(){
		keyboard.reset();
	}

	//	��ԏ���
	DirectX::Keyboard::State GetState();
	//	�g���b�J�[�X�V
	void TrackerUpdate();

	//	�w�肳�ꂽ�L�[��������Ă��邩
	bool CheckKey(char* keyName);
	//	�w�肳�ꂽ�L�[�����ꂽ��
	bool CheckPressed(char* keyName);

private:
	//	�L�[�{�[�h�N���X
	static std::unique_ptr<Keyboards> keyboard;
	//	�L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	//	�g���b�J�[
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_tracker;

	//	�L�[�ϊ����X�g
	std::unique_ptr<KeyConvertList> m_keyList;

};
