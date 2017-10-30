#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
{
	

	m_pImgGround = g_pImageManager->FindImage("Map");
	m_pImgGround2 = g_pImageManager->FindImage("Map2");
	m_pObject = g_pImageManager->FindImage("Object");

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_pImgMapBuffer2 = g_pImageManager->FindImage("MapBuffer2");
	//m_pObject->SetPosX(100);
	//m_pObject->SetPosY(100);
    //m_bMoveRight = true;

	


	m_MapSpeed = 0;
		m_GetX = 0; //¸ÊÀÇ À§Ä¡

	
}

cMap::~cMap()
{
}

void cMap::Setup()
{
}

void cMap::Update()
{
	MoveObject();

	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 50);


}

void cMap::Render()
{
	
	//m_pImgGround->Render(g_hDC, 0, 0, WINSIZEX, WINSIZEY);
	//m_pObject->Render(g_hDC, 0, 300, 100, 100);

	m_pImgGround2->Render(m_pImgMapBuffer2->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5);
	m_pImgGround->Render(m_pImgMapBuffer->GetMemDC(), 0,0,3000,600);
	
	m_pObject->Render(m_pImgMapBuffer->GetMemDC(), 0, 300, 100, 100);
	


	m_pImgMapBuffer2->Render(g_hDC, 0, 0);
	m_pImgMapBuffer->Render(g_hDC, 0, 0);
	





	
}

void cMap::MoveObject()
{
	

}

