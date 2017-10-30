#include "stdafx.h"
#include "cMainGame.h"
#include "cMap.h"
#include "cPlayer.h"


cMainGame::cMainGame()
   :m_Imagect(0)
  , m_Imagect2(0)
  , m_isPlaying(false)
  , m_isMain(false)
  , m_LoadingDelay(LOADINGDELAY)
  , m_ImagectDelay(IMAGEDELAY)
{


	
	LoadImageFromFile();

	//m_pMap = new cMap;
	//m_pPlayer = new cPlayer;
 
	

}

cMainGame::~cMainGame()
{
	
}

void cMainGame::Setup()
{

	//m_pMap->Setup();
	//m_pPlayer->SetMap(m_pMap);
	//m_pPlayer->Setup();

	
}

void cMainGame::Update()
{
	cGameNode::Update();

	// 시작과 동시 카운트 
	if (!m_isPlaying && !m_isMain)
		--m_LoadingDelay;


	if (m_isPlaying)
	{
	

	}
	else if (m_isMain)
	{
		if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
		{
			m_isMain = false;
			m_isPlaying = true;
			Setup();
		}
	}

	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		Setup();
		m_isMain = true;
		m_isPlaying = true;
	}
}

void cMainGame::Render()
{
	// 흰색으로 이미지를 칠한다.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
	
		
	


	}
	else if (m_isMain)
	{
		//메인화면-----------FADE IN---FACE  OUT----------------------------------------------
		//TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "메인입니다.", strlen("메인입니다."));
		g_pImageManager->FindImage("Main")->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);
		g_pImageManager->FindImage("StartText")->FrameRender(g_hDC, WINSIZEX / 4 + 175, WINSIZEY / 2 + 100, 0, 0, 1, 0, 20);
		//--------------------------------------------------------------------------------------

	}
	else
	{


		//첨시작 검은 화면       
		g_pImageManager->FindImage("Loading")->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);
		//로딩화면 마크또는 로그보여줌
		if (m_Imagect < 255 && m_ImagectDelay > 0)    //m_Iagect 0 ~255까지 increase
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, ++m_Imagect);
		//로딩화면이 보인상태로  감소카운팅시작  --로딩화면 유지 시간 = m_ImagetDelay
		if (m_Imagect >= 255 && m_ImagectDelay > 0)
		{
			--m_ImagectDelay;
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, 255);
		}

		//로딩로고  다시 어둡게 시작 
		if (m_Imagect > 0 && m_ImagectDelay <= 0)
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, --m_Imagect);
		//로딩이 사라짐 
		if (m_Imagect <= 0 && m_ImagectDelay <= 0)
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, 0);
		//----------------------------------------------------------------------------------------
	

	}
}
  
void cMainGame::LoadImageFromFile()
{


	//-------------로딩화면 fade IN  ,OUT----------------------------------
	g_pImageManager->AddImage("Loading", "images/BlockColor.bmp", 1200, 600);
	g_pImageManager->AddImage("LoadingLogo", "images/로딩화면.bmp", 1200, 600);
	g_pImageManager->AddImage("Main", "images/메인화면.bmp", 1200, 600);
	g_pImageManager->AddImage("StartText", "images/스타트로고.bmp", 700, 80, 2, 1,
		WINSIZEX / 4, WINSIZEY / 4 + 100, true, RGB(255, 0, 255));
	//---------------------------------------------------------------------------
   
}



     



