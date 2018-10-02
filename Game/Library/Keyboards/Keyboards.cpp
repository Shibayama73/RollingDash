//============================================================//
//*名　前	Keyboards.cpp
//*内　容	キーボード
//*日　付	2017.8.28
//*更　新	2017.8.28
//*制作者	N.Shibayama
//============================================================//
#include "Keyboards.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

std::unique_ptr<Keyboards> Keyboards::keyboard(nullptr);

void Keyboards::CreateKeyboard()
{
	//	キーボードの生成
	this->m_keyboard = std::make_unique<Keyboard>();
	//	トラッカー生成
	this->m_tracker = std::make_unique<Keyboard::KeyboardStateTracker>();
	//	キー変換リストの生成
	this->m_keyList = std::make_unique<KeyConvertList>();

}

//	状態取得
DirectX::Keyboard::State Keyboards::GetState()
{
	return this->m_keyboard->GetState();
}

//	トラッカー更新
void Keyboards::TrackerUpdate()
{
	auto state = m_keyboard->GetState();
	m_tracker->Update(state);
}

//	指定されたキーが押されているか
bool Keyboards::CheckKey(char* keyName)
{
	//	指定されたキー(ASCIIコード)からキーボードの値に変換する
	int keyCodeNum = m_keyList->Convert(keyName);
	//	キーの状態取得
	Keyboard::State key = m_keyboard->GetState();

	//	キーボードを変換された値に入れる
	switch (keyCodeNum)
	{
	case KeyConvertList::Enter:
		if (key.Enter)	return true;
		return false;
	case KeyConvertList::Space:
		if (key.Space)	return true;
		return false;
	case KeyConvertList::End:
		if (key.End)	return true;
		return false;
	case KeyConvertList::Left:
		if (key.Left)	return true;
		return false;
	case KeyConvertList::Up:
		if (key.Up)	return true;
		return false;
	case KeyConvertList::Right:
		if (key.Right)	return true;
		return false;
	case KeyConvertList::Down:
		if (key.Down)	return true;
		return false;
	case KeyConvertList::A:
		if (key.A)	return true;
		return false;
	case KeyConvertList::B:
		if (key.B)	return true;
		return false;
	case KeyConvertList::C:
		if (key.C)	return true;
		return false;
	case KeyConvertList::D:
		if (key.D)	return true;
		return false;
	case KeyConvertList::E:
		if (key.E)	return true;
		return false;
	case KeyConvertList::F:
		if (key.F)	return true;
		return false;
	case KeyConvertList::G:
		if (key.G)	return true;
		return false;
	case KeyConvertList::H:
		if (key.H)	return true;
		return false;
	case KeyConvertList::I:
		if (key.I)	return true;
		return false;
	case KeyConvertList::J:
		if (key.J)	return true;
		return false;
	case KeyConvertList::K:
		if (key.K)	return true;
		return false;
	case KeyConvertList::L:
		if (key.L)	return true;
		return false;
	case KeyConvertList::M:
		if (key.M)	return true;
		return false;
	case KeyConvertList::N:
		if (key.N)	return true;
		return false;
	case KeyConvertList::O:
		if (key.O)	return true;
		return false;
	case KeyConvertList::P:
		if (key.P)	return true;
		return false;
	case KeyConvertList::Q:
		if (key.Q)	return true;
		return false;
	case KeyConvertList::R:
		if (key.R)	return true;
		return false;
	case KeyConvertList::S:
		if (key.S)	return true;
		return false;
	case KeyConvertList::T:
		if (key.T)	return true;
		return false;
	case KeyConvertList::U:
		if (key.U)	return true;
		return false;
	case KeyConvertList::V:
		if (key.V)	return true;
		return false;
	case KeyConvertList::W:
		if (key.W)	return true;
		return false;
	case KeyConvertList::X:
		if (key.X)	return true;
		return false;
	case KeyConvertList::Y:
		if (key.Y)	return true;
		return false;
	case KeyConvertList::Z:
		if (key.Z)	return true;
		return false;
	case KeyConvertList::NumPad0:
		if (key.NumPad0)	return true;
		return false;
	case KeyConvertList::NumPad1:
		if (key.NumPad1)	return true;
		return false;
	case KeyConvertList::NumPad2:
		if (key.NumPad2)	return true;
		return false;
	case KeyConvertList::NumPad3:
		if (key.NumPad3)	return true;
		return false;
	case KeyConvertList::NumPad4:
		if (key.NumPad4)	return true;
		return false;
	case KeyConvertList::NumPad5:
		if (key.NumPad5)	return true;
		return false;
	case KeyConvertList::NumPad6:
		if (key.NumPad6)	return true;
		return false;
	case KeyConvertList::NumPad7:
		if (key.NumPad7)	return true;
		return false;
	case KeyConvertList::NumPad8:
		if (key.NumPad8)	return true;
		return false;
	case KeyConvertList::NumPad9:
		if (key.NumPad9)	return true;
		return false;
	case KeyConvertList::F1:
		if (key.F1)	return true;
		return false;
	case KeyConvertList::F2:
		if (key.F2)	return true;
		return false;
	case KeyConvertList::F3:
		if (key.F3)	return true;
		return false;
	case KeyConvertList::F4:
		if (key.F4)	return true;
		return false;
	case KeyConvertList::F5:
		if (key.F5)	return true;
		return false;
	case KeyConvertList::F6:
		if (key.F6)	return true;
		return false;
	case KeyConvertList::F7:
		if (key.F7)	return true;
		return false;
	case KeyConvertList::F8:
		if (key.F8)	return true;
		return false;
	case KeyConvertList::F9:
		if (key.F9)	return true;
		return false;
	case KeyConvertList::F10:
		if (key.F10)	return true;
		return false;
	case KeyConvertList::F11:
		if (key.F11)	return true;
		return false;
	case KeyConvertList::F12:
		if (key.F12)	return true;
		return false;
	default:
		return false;
	}
}

//	指定されたキー押されたか
bool Keyboards::CheckPressed(char* keyName)
{
	//	キーの状態取得
	//auto state = m_keyboard->GetState();
	//m_tracker->Update(state);

	//	指定されたキー(ASCIIコード)からキーボードの値に変換する
	int keyCodeNum = m_keyList->Convert(keyName);

	//	キーボードを変換された値に入れる
	switch (keyCodeNum)
	{
	case KeyConvertList::Enter:
		if (m_tracker->pressed.Enter)	return true;
		return false;
	case KeyConvertList::Space:
		if (m_tracker->pressed.Space)	return true;
		return false;
	case KeyConvertList::End:
		if (m_tracker->pressed.End)	return true;
		return false;
	case KeyConvertList::Left:
		if (m_tracker->pressed.Left)	return true;
		return false;
	case KeyConvertList::Up:
		if (m_tracker->pressed.Up)	return true;
		return false;
	case KeyConvertList::Right:
		if (m_tracker->pressed.Right)	return true;
		return false;
	case KeyConvertList::Down:
		if (m_tracker->pressed.Down)	return true;
		return false;
	case KeyConvertList::A:
		if (m_tracker->pressed.A)	return true;
		return false;
	case KeyConvertList::B:
		if (m_tracker->pressed.B)	return true;
		return false;
	case KeyConvertList::C:
		if (m_tracker->pressed.C)	return true;
		return false;
	case KeyConvertList::D:
		if (m_tracker->pressed.D)	return true;
		return false;
	case KeyConvertList::E:
		if (m_tracker->pressed.E)	return true;
		return false;
	case KeyConvertList::F:
		if (m_tracker->pressed.F)	return true;
		return false;
	case KeyConvertList::G:
		if (m_tracker->pressed.G)	return true;
		return false;
	case KeyConvertList::H:
		if (m_tracker->pressed.H)	return true;
		return false;
	case KeyConvertList::I:
		if (m_tracker->pressed.I)	return true;
		return false;
	case KeyConvertList::J:
		if (m_tracker->pressed.J)	return true;
		return false;
	case KeyConvertList::K:
		if (m_tracker->pressed.K)	return true;
		return false;
	case KeyConvertList::L:
		if (m_tracker->pressed.L)	return true;
		return false;
	case KeyConvertList::M:
		if (m_tracker->pressed.M)	return true;
		return false;
	case KeyConvertList::N:
		if (m_tracker->pressed.N)	return true;
		return false;
	case KeyConvertList::O:
		if (m_tracker->pressed.O)	return true;
		return false;
	case KeyConvertList::P:
		if (m_tracker->pressed.P)	return true;
		return false;
	case KeyConvertList::Q:
		if (m_tracker->pressed.Q)	return true;
		return false;
	case KeyConvertList::R:
		if (m_tracker->pressed.R)	return true;
		return false;
	case KeyConvertList::S:
		if (m_tracker->pressed.S)	return true;
		return false;
	case KeyConvertList::T:
		if (m_tracker->pressed.T)	return true;
		return false;
	case KeyConvertList::U:
		if (m_tracker->pressed.U)	return true;
		return false;
	case KeyConvertList::V:
		if (m_tracker->pressed.V)	return true;
		return false;
	case KeyConvertList::W:
		if (m_tracker->pressed.W)	return true;
		return false;
	case KeyConvertList::X:
		if (m_tracker->pressed.X)	return true;
		return false;
	case KeyConvertList::Y:
		if (m_tracker->pressed.Y)	return true;
		return false;
	case KeyConvertList::Z:
		if (m_tracker->pressed.Z)	return true;
		return false;
	case KeyConvertList::NumPad0:
		if (m_tracker->pressed.NumPad0)	return true;
		return false;
	case KeyConvertList::NumPad1:
		if (m_tracker->pressed.NumPad1)	return true;
		return false;
	case KeyConvertList::NumPad2:
		if (m_tracker->pressed.NumPad2)	return true;
		return false;
	case KeyConvertList::NumPad3:
		if (m_tracker->pressed.NumPad3)	return true;
		return false;
	case KeyConvertList::NumPad4:
		if (m_tracker->pressed.NumPad4)	return true;
		return false;
	case KeyConvertList::NumPad5:
		if (m_tracker->pressed.NumPad5)	return true;
		return false;
	case KeyConvertList::NumPad6:
		if (m_tracker->pressed.NumPad6)	return true;
		return false;
	case KeyConvertList::NumPad7:
		if (m_tracker->pressed.NumPad7)	return true;
		return false;
	case KeyConvertList::NumPad8:
		if (m_tracker->pressed.NumPad8)	return true;
		return false;
	case KeyConvertList::NumPad9:
		if (m_tracker->pressed.NumPad9)	return true;
		return false;
	case KeyConvertList::F1:
		if (m_tracker->pressed.F1)	return true;
		return false;
	case KeyConvertList::F2:
		if (m_tracker->pressed.F2)	return true;
		return false;
	case KeyConvertList::F3:
		if (m_tracker->pressed.F3)	return true;
		return false;
	case KeyConvertList::F4:
		if (m_tracker->pressed.F4)	return true;
		return false;
	case KeyConvertList::F5:
		if (m_tracker->pressed.F5)	return true;
		return false;
	case KeyConvertList::F6:
		if (m_tracker->pressed.F6)	return true;
		return false;
	case KeyConvertList::F7:
		if (m_tracker->pressed.F7)	return true;
		return false;
	case KeyConvertList::F8:
		if (m_tracker->pressed.F8)	return true;
		return false;
	case KeyConvertList::F9:
		if (m_tracker->pressed.F9)	return true;
		return false;
	case KeyConvertList::F10:
		if (m_tracker->pressed.F10)	return true;
		return false;
	case KeyConvertList::F11:
		if (m_tracker->pressed.F11)	return true;
		return false;
	case KeyConvertList::F12:
		if (m_tracker->pressed.F12)	return true;
		return false;
	default:
		return false;
	}
}
