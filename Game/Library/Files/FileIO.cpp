//============================================================//
//*���@�O	FileIO.cpp
//*���@�e	�t�@�C���ǂݍ���/��������
//*���@�t	2017.7.6
//*�X�@�V	2017.7.6
//*�����	N.Shibayama
//============================================================//
#include "FileIO.h"
#include <fstream>

using namespace std;

//	�t�@�C�����̓o�^
void FileIO::SetFileName(string name)
{
	m_fileName = name;
}

//	�w�肳�ꂽ�s�̓Ǎ���
wchar_t* FileIO::LoadText(int row)
{
	setlocale(LC_ALL, "japanese");

	std::ifstream ifs(m_fileName.c_str());
	char fileText[256];		//�t�@�C���Ǎ��ݗp
	wchar_t text[256];		//�ǂݍ��񂾕�����\���ϊ��p

	if (ifs.fail())
	{
		return NULL;
	}
	//	�w�肳�ꂽ�s
	for (int i = 0; i <= row; i++)
	{
		//	1�s�ǂݍ���
		ifs.getline(fileText, 256 - 1);
	}
	//	�t�@�C������ǂݍ��񂾕����̕ϊ�(char����wchar_t�ɕϊ�)
	mbstowcs(text, fileText, sizeof(fileText));		//text(decimal)

	return text;
}

//	�w�肳�ꂽ�s�̐��l�Ǎ���
int FileIO::LoadNum(int row)
{
	int data;
	std::ifstream ifs(m_fileName.c_str());
	char str[256];

	if (ifs.fail())
	{
		return NULL;
	}
	//	�w�肳�ꂽ�s
	for (int i = 0; i <= row; i++)
	{
		//	1�s�ǂݍ���
		ifs.getline(str, 256 - 1);
	}
	data = atoi(str);

	return data;
}

//	�s���̎擾
int FileIO::GetRow()
{
	std::ifstream ifs(m_fileName.c_str());
	int row = 0;	//�s��

	char fileText[256];		//�t�@�C���Ǎ��ݗp

	if (ifs.fail())
	{
		return -1;
	}
	//	1�s���ǂݍ���
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
	//	�����݂����s�����Ƃ�
	if (fp == NULL) {
		return 1;
	}
	//	1�s������
	fprintf(fp, "%d\n", writeNum);

	fclose(fp);
	return 0;
}
