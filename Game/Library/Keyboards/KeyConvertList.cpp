//============================================================//
//*名　前	KeyConvertList.cpp
//*内　容	ASCIIコードからキーボードのキーに変換する
//*日　付	2017.8.28
//*更　新	2017.8.28
//*制作者	N.Shibayama
//============================================================//
#include "..\Framework\pch.h"
#include "KeyConvertList.h"

KeyConvertList::KeyConvertList()
{
}

KeyConvertList::~KeyConvertList()
{
}

int KeyConvertList::Convert(char* asciiCode)
{
	if (strcmp(asciiCode, "Enter") == 0) return Keys::Enter;
	else if (strcmp(asciiCode, "Space") == 0) return Keys::Space;
	else if (strcmp(asciiCode, "End") == 0) return Keys::End;
	else if (strcmp(asciiCode, "Left") == 0) return Keys::Left;
	else if (strcmp(asciiCode, "Up") == 0) return Keys::Up;
	else if (strcmp(asciiCode, "Right") == 0) return Keys::Right;
	else if (strcmp(asciiCode, "Down") == 0) return Keys::Down;
	else if ((strcmp(asciiCode, "A") == 0)) return Keys::A;
	else if ((strcmp(asciiCode, "B") == 0)) return Keys::B;
	else if ((strcmp(asciiCode, "C") == 0)) return Keys::C;
	else if ((strcmp(asciiCode, "D") == 0)) return Keys::D;
	else if ((strcmp(asciiCode, "E") == 0)) return Keys::E;
	else if ((strcmp(asciiCode, "F") == 0)) return Keys::F;
	else if ((strcmp(asciiCode, "G") == 0)) return Keys::G;
	else if ((strcmp(asciiCode, "H") == 0)) return Keys::H;
	else if ((strcmp(asciiCode, "I") == 0)) return Keys::I;
	else if ((strcmp(asciiCode, "J") == 0)) return Keys::J;
	else if ((strcmp(asciiCode, "K") == 0)) return Keys::K;
	else if ((strcmp(asciiCode, "L") == 0)) return Keys::L;
	else if ((strcmp(asciiCode, "M") == 0)) return Keys::M;
	else if ((strcmp(asciiCode, "N") == 0)) return Keys::N;
	else if ((strcmp(asciiCode, "O") == 0)) return Keys::O;
	else if ((strcmp(asciiCode, "P") == 0)) return Keys::P;
	else if ((strcmp(asciiCode, "Q") == 0)) return Keys::Q;
	else if ((strcmp(asciiCode, "R") == 0)) return Keys::R;
	else if ((strcmp(asciiCode, "S") == 0)) return Keys::S;
	else if ((strcmp(asciiCode, "T") == 0)) return Keys::T;
	else if ((strcmp(asciiCode, "U") == 0)) return Keys::U;
	else if ((strcmp(asciiCode, "V") == 0)) return Keys::V;
	else if ((strcmp(asciiCode, "W") == 0)) return Keys::W;
	else if ((strcmp(asciiCode, "X") == 0)) return Keys::X;
	else if ((strcmp(asciiCode, "Y") == 0)) return Keys::Y;
	else if ((strcmp(asciiCode, "Z") == 0)) return Keys::Z;
	else if ((strcmp(asciiCode, "NumPad0") == 0)) return Keys::NumPad0;
	else if ((strcmp(asciiCode, "NumPad1") == 0)) return Keys::NumPad1;
	else if ((strcmp(asciiCode, "NumPad2") == 0)) return Keys::NumPad2;
	else if ((strcmp(asciiCode, "NumPad3") == 0)) return Keys::NumPad3;
	else if ((strcmp(asciiCode, "NumPad4") == 0)) return Keys::NumPad4;
	else if ((strcmp(asciiCode, "NumPad5") == 0)) return Keys::NumPad5;
	else if ((strcmp(asciiCode, "NumPad6") == 0)) return Keys::NumPad6;
	else if ((strcmp(asciiCode, "NumPad7") == 0)) return Keys::NumPad7;
	else if ((strcmp(asciiCode, "NumPad8") == 0)) return Keys::NumPad8;
	else if ((strcmp(asciiCode, "NumPad9") == 0)) return Keys::NumPad9;
	else if ((strcmp(asciiCode, "F1") == 0)) return Keys::F1;
	else if ((strcmp(asciiCode, "F2") == 0)) return Keys::F2;
	else if ((strcmp(asciiCode, "F3") == 0)) return Keys::F3;
	else if ((strcmp(asciiCode, "F4") == 0)) return Keys::F4;
	else if ((strcmp(asciiCode, "F5") == 0)) return Keys::F5;
	else if ((strcmp(asciiCode, "F6") == 0)) return Keys::F6;
	else if ((strcmp(asciiCode, "F7") == 0)) return Keys::F7;
	else if ((strcmp(asciiCode, "F8") == 0)) return Keys::F8;
	else if ((strcmp(asciiCode, "F9") == 0)) return Keys::F9;
	else if ((strcmp(asciiCode, "F10") == 0)) return Keys::F10;
	else if ((strcmp(asciiCode, "F11") == 0)) return Keys::F11;
	else if ((strcmp(asciiCode, "F12") == 0)) return Keys::F12;
	else return 0;

	return 0;
}
