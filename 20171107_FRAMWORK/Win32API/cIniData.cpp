#include "stdafx.h"
#include "cIniData.h"


// ������ �߰� (����, Ű, ���)
void cIniData::AddData(char* section, char* key, char* value)
{
	// INI ������ ����ü ���� �� �ʱ�ȭ
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	// ini������ ����ü ���Ϳ� ���
	arrIniData vIniData;
	m_vIniDatas.push_back(iniData);
}

// ���̺� (���� �̸�)
void cIniData::IniSave(char* fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	for (int i = 0; i < m_vIniDatas.size(); ++i)
	{
		WritePrivateProfileString(m_vIniDatas[i].section, m_vIniDatas[i].key, m_vIniDatas[i].value, str);
	}

	//for (arrIniDataIter iter = m_vIniDatas.begin(); iter != m_vIniDatas.end(); ++iter)
	//{
	//	WritePrivateProfileString(iter->section, iter->key, iter->value, str);
	//}

	m_vIniDatas.clear();
}

// ���ڰ� �ε� (����, ����, Ű)
char* cIniData::LoadDataString(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	char data[64] = { NULL };
	GetPrivateProfileString(section, key, "", data, 64, str);

	return data;
}

// ������ �ε� (����, ����, Ű)
int cIniData::LoadDataInteger(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	return GetPrivateProfileInt(section, key, 0, str);
}
