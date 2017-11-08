#include "stdafx.h"
#include "cMap.h"
#include "cPlayer.h"


cMap::cMap()
{
	m_pImgMap = g_pImageManager->FindImage("Map");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
}

cMap::~cMap()
{
}

void cMap::Setup()
{
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
}

void cMap::Update()
{
	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		g_pPixelManager->RemoveBrush(m_pImgMap, g_ptMouse.x, g_ptMouse.y, 50);

	if (m_pPlayer->GetMapMove())
	{
		if (g_pKeyManager->isStayKeyDown('A') && m_fPosX >= m_pPlayer->GetMoveSpeed())
		{
			m_fPosX -= m_pPlayer->GetMoveSpeed();
		}
		else if (g_pKeyManager->isStayKeyDown('D') &&
			m_fPosX <= m_pImgMap->GetWidth() - WINSIZEX - m_pPlayer->GetMoveSpeed())
		{
			m_fPosX += m_pPlayer->GetMoveSpeed();
		}
	}
}

void cMap::Render()
{
	// �ȼ� �浹 ó���� �̹��� ���ۿ� �׸��� �׸���.
	m_pImgMap->Render(m_pImgMapBuffer->GetMemDC(), 0, 0);

	// ������Ʈ�� �ִٸ� m_pImgMapBuffer�� �׸���.


	// ����ۿ� �׸���.
	//m_pImgMapBuffer->SetTransColor(false, RGB(0, 0, 0));
	m_pImgMapBuffer->Render(g_hDC, 0, 0, m_fPosX, m_fPosY, WINSIZEX, WINSIZEY);
}