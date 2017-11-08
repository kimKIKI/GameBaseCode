#pragma once
#include "cSingletonBase.h"

#define g_pIniData cIniData::GetInstance()

// INI ������ ����ü
struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class cIniData : public cSingletonBase<cIniData>
{
private:
	// typedef: �� ������
	typedef vector<tagIniData> arrIniData;
	typedef vector<tagIniData>::iterator arrIniDataIter;

	//typedef vector<arrIniData> arrIniDatas;
	//typedef vector<arrIniData>::iterator arrIniDatasIter;

private:
	arrIniData m_vIniDatas;

public:
	// ������ �߰� (����, Ű, ���)
	void AddData(char* section, char* key, char* value);
	// ���̺� (���� �̸�)
	void IniSave(char* fileName);
	// ���ڰ� �ε� (����, ����, Ű)
	char* LoadDataString(char* fileName, char* section, char* key);
	// ������ �ε� (����, ����, Ű)
	int LoadDataInteger(char* fileName, char* section, char* key);
};

