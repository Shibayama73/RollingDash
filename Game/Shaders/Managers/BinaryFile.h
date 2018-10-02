//============================================================//
//*名　前	BinaryFile.h
//*内　容	バイナリファイル
//*日　付	2018.7.18
//*更　新	2018.7.20
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <memory>

class BinaryFile
{
public:
	// ファイル名を指定してロード
	static BinaryFile LoadFile(const wchar_t* fileName);

	BinaryFile();
	// ムーブコンストラクタ
	BinaryFile(BinaryFile&& in);

	// アクセッサ
	char* GetData() { return m_Data.get(); }
	unsigned int GetSize() { return m_Size; }

protected:
	// データ
	std::unique_ptr<char[]> m_Data;
	// サイズ
	unsigned int m_Size;
};
