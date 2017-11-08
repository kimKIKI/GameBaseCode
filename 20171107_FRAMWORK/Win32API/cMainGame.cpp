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
			g_pIniData->AddData("국기반", "최수호", "맨날 디버깅");
			g_pIniData->AddData("국기반", "최동철", "20");

			g_pIniData->AddData("막나가", "정상현", "맨날 행사가");
			g_pIniData->AddData("막나가", "전민성", "맨날 다했데");

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

	// 흰색으로 이미지를 칠한다.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
	

		char* str = g_pIniData->LoadDataString("ClassData", "국기반", "최수호");
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2 - 50, str, strlen(str));

		int age = g_pIniData->LoadDataInteger("ClassData", "국기반", "최동철");
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




