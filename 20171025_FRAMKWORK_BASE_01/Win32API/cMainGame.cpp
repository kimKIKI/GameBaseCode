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

	// ���۰� ���� ī��Ʈ 
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
	// ������� �̹����� ĥ�Ѵ�.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
	
		
	


	}
	else if (m_isMain)
	{
		//����ȭ��-----------FADE IN---FACE  OUT----------------------------------------------
		//TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "�����Դϴ�.", strlen("�����Դϴ�."));
		g_pImageManager->FindImage("Main")->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);
		g_pImageManager->FindImage("StartText")->FrameRender(g_hDC, WINSIZEX / 4 + 175, WINSIZEY / 2 + 100, 0, 0, 1, 0, 20);
		//--------------------------------------------------------------------------------------

	}
	else
	{


		//÷���� ���� ȭ��       
		g_pImageManager->FindImage("Loading")->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);
		//�ε�ȭ�� ��ũ�Ǵ� �α׺�����
		if (m_Imagect < 255 && m_ImagectDelay > 0)    //m_Iagect 0 ~255���� increase
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, ++m_Imagect);
		//�ε�ȭ���� ���λ��·�  ����ī���ý���  --�ε�ȭ�� ���� �ð� = m_ImagetDelay
		if (m_Imagect >= 255 && m_ImagectDelay > 0)
		{
			--m_ImagectDelay;
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, 255);
		}

		//�ε��ΰ�  �ٽ� ��Ӱ� ���� 
		if (m_Imagect > 0 && m_ImagectDelay <= 0)
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, --m_Imagect);
		//�ε��� ����� 
		if (m_Imagect <= 0 && m_ImagectDelay <= 0)
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, 0);
		//----------------------------------------------------------------------------------------
	

	}
}
  
void cMainGame::LoadImageFromFile()
{


	//-------------�ε�ȭ�� fade IN  ,OUT----------------------------------
	g_pImageManager->AddImage("Loading", "images/BlockColor.bmp", 1200, 600);
	g_pImageManager->AddImage("LoadingLogo", "images/�ε�ȭ��.bmp", 1200, 600);
	g_pImageManager->AddImage("Main", "images/����ȭ��.bmp", 1200, 600);
	g_pImageManager->AddImage("StartText", "images/��ŸƮ�ΰ�.bmp", 700, 80, 2, 1,
		WINSIZEX / 4, WINSIZEY / 4 + 100, true, RGB(255, 0, 255));
	//---------------------------------------------------------------------------
   
}



     



