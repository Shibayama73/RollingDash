//============================================================//
//*名　前	FileIO.cpp
//*内　容	ファイル読み込み/書き込み
//*日　付	2017.7.6
//*更　新	2017.7.6
//*制作者	N.Shibayama
//============================================================//
#include "FileIO.h"
#include <fstream>

using namespace std;

//	ファイル名の登録
void FileIO::SetFileName(string name)
{
	m_fileName = name;
}

//	指定された行の読込み
wchar_t* FileIO::LoadText(int row)
{
	setlocale(LC_ALL, "japanese");

	std::ifstream ifs(m_fileName.c_str());
	char fileText[256];		//ファイル読込み用
	wchar_t text[256];		//読み込んだ文字を表示変換用

	if (ifs.fail())
	{
		return NULL;
	}
	//	指定された行
	for (int i = 0; i <= row; i++)
	{
		//	1行読み込み
		ifs.getline(fileText, 256 - 1);
	}
	//	ファイルから読み込んだ文字の変換(charからwchar_tに変換)
	mbstowcs(text, fileText, sizeof(fileText));		//text(decimal)

	return text;
}

//	指定された行の数値読込み
int FileIO::LoadNum(int row)
{
	int data;
	std::ifstream ifs(m_fileName.c_str());
	char str[256];

	if (ifs.fail())
	{
		return NULL;
	}
	//	指定された行
	for (int i = 0; i <= row; i++)
	{
		//	1行読み込み
		ifs.getline(str, 256 - 1);
	}
	data = atoi(str);

	return data;
}

//	行数の取得
int FileIO::GetRow()
{
	std::ifstream ifs(m_fileName.c_str());
	int row = 0;	//行数

	char fileText[256];		//ファイル読込み用

	if (ifs.fail())
	{
		return -1;
	}
	//	1行ずつ読み込み
	while (ifs.getline(fileText, sizeof(fileText)))
	{
		row++;
	}

	return row;
}

int FileIO::FileWrite(int num)
{
	int writeNum = num;
	FILE *fp;

	fp = fopen(m_fileName.c_str(), "w");
	//	書込みが失敗したとき
	if (fp == NULL) {
		return 1;
	}
	//	1行書込み
	fprintf(fp, "%d\n", writeNum);

	fclose(fp);
	return 0;
}
