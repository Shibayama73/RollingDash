//============================================================//
//*名　前	FileIO.h
//*内　容	ファイル読み込み/書き込み
//*日　付	2017.7.6
//*更　新	2017.7.6
//*制作者	N.Shibayama
//============================================================//
#pragma once
#include <string>

class FileIO
{
public:
	//	ファイル名の登録
	void SetFileName(std::string name);
	//	指定された行の読込み
	wchar_t* LoadText(int row);
	//	指定された行の数値読込み
	int LoadNum(int row);
	//	行数の取得
	int GetRow();
	//	1行分ファイルに書き込む
	int FileWrite(int num);

private:
	std::string m_fileName;	//ファイル名

};
