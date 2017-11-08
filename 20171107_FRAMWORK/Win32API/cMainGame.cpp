#include "stdafx.h"
#include "cMainGame.h"
#include "cMap.h"
#include "cPlayer.h"


cMainGame::cMainGame()
	: m_isPlaying(false)
{
	
}

cMainGame::~cMainGame()
{
	
}

void cMainGame::Setup()
{

}

void cMainGame::Update()
{
	cGameNode::Update();

	if (m_isPlaying)
	{
		

		if (g_pKeyManager->isOnceKeyDown('I'))
		{
			g_pIniData->AddData("�����", "�ּ�ȣ", "�ǳ� �����");
			g_pIniData->AddData("�����", "�ֵ�ö", "20");

			g_pIniData->AddData("������", "������", "�ǳ� ��簡");
			g_pIniData->AddData("������", "���μ�", "�ǳ� ���ߵ�");

			g_pIniData->IniSave("ClassData");
		}
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
	
		m_isPlaying = true;
	}
}

void cMainGame::Render()
{
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(g_hWnd, &ps);

	// ������� �̹����� ĥ�Ѵ�.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
	

		char* str = g_pIniData->LoadDataString("ClassData", "�����", "�ּ�ȣ");
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2 - 50, str, strlen(str));

		int age = g_pIniData->LoadDataInteger("ClassData", "�����", "�ֵ�ö");
		char szBuf[128];
		str = itoa(age, szBuf, 10);
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, str, strlen(str));
	}
	else
	{
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
	}

	g_pTimeManager->Render();
	m_pImgBackBuffer->Render(hdc);

	EndPaint(g_hWnd, &ps);
}




