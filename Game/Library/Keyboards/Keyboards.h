//============================================================//
//*名　前	Keyboards.h
//*内　容	キーボード
//*日　付	2017.8.28
//*更　新	2017.8.28
//*制作者	N.Shibayama
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
	//	コンストラクタ
	Keyboards(){}
	//	キーボードの生成
	void CreateKeyboard();

public:
	//	インスタンス取得
	static Keyboards& GetInstance() {
		if (keyboard.get() == nullptr) {
			keyboard.reset(new Keyboards());
			keyboard->CreateKeyboard();
		}
		return *keyboard.get();
	}

	//	破棄する
	static void Dispose(){
		keyboard.reset();
	}

	//	状態所得
	DirectX::Keyboard::State GetState();
	//	トラッカー更新
	void TrackerUpdate();

	//	指定されたキーが押されているか
	bool CheckKey(char* keyName);
	//	指定されたキー押されたか
	bool CheckPressed(char* keyName);

private:
	//	キーボードクラス
	static std::unique_ptr<Keyboards> keyboard;
	//	キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	//	トラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_tracker;

	//	キー変換リスト
	std::unique_ptr<KeyConvertList> m_keyList;

};
