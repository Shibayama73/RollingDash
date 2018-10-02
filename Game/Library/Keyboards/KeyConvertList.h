//============================================================//
//*名　前	KeyConvertList.h
//*内　容	ASCIIコードからキーボードのキーに変換する
//*日　付	2017.8.28
//*更　新	2017.8.28
//*制作者	N.Shibayama
//============================================================//
#pragma once

class KeyConvertList
{
public:
	enum Keys
	{
		Enter = 0xd,
		Space = 0x20,
		End = 0x23,
		Left = 0x25,
		Up = 0x26,
		Right = 0x27,
		Down = 0x28,

		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4a,
		K = 0x4b,
		L = 0x4c,
		M = 0x4d,
		N = 0x4e,
		O = 0x4f,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5a,

		NumPad0 = 0x60,
		NumPad1 = 0x61,
		NumPad2 = 0x62,
		NumPad3 = 0x63,
		NumPad4 = 0x64,
		NumPad5 = 0x65,
		NumPad6 = 0x66,
		NumPad7 = 0x67,
		NumPad8 = 0x68,
		NumPad9 = 0x69,

		F1 = 0x70,
		F2 = 0x71,
		F3 = 0x72,
		F4 = 0x73,
		F5 = 0x74,
		F6 = 0x75,
		F7 = 0x76,
		F8 = 0x77,
		F9 = 0x78,
		F10 = 0x79,
		F11 = 0x7a,
		F12 = 0x7b

	};


public:
	KeyConvertList();
	~KeyConvertList();

	//	ASCIIコードからキーボードのキーに変換する
	int Convert(char* asciiCode);

};
