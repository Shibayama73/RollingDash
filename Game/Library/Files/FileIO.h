//============================================================//
//*���@�O	FileIO.h
//*���@�e	�t�@�C���ǂݍ���/��������
//*���@�t	2017.7.6
//*�X�@�V	2017.7.6
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <string>

class FileIO
{
public:
	//	�t�@�C�����̓o�^
	void SetFileName(std::string name);
	//	�w�肳�ꂽ�s�̓Ǎ���
	wchar_t* LoadText(int row);
	//	�w�肳�ꂽ�s�̐��l�Ǎ���
	int LoadNum(int row);
	//	�s���̎擾
	int GetRow();
	//	1�s���t�@�C���ɏ�������
	int FileWrite(int num);

private:
	std::string m_fileName;	//�t�@�C����

};
