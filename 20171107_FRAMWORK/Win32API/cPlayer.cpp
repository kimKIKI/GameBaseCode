#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"


cPlayer::cPlayer()
{
	m_pPlayerImage = g_pImageManager->FindImage("Player");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");

	m_pHpBar = new cProgressBar("ProgressBack", "ProgressFront",
		m_pPlayerImage->GetFrameWidth(), 10);
}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	m_fJumpPower = 10.0f;
	m_fMoveSpeed = 3.0f; //  *g_pTimeManager->GetDeltaTime();
	m_isMapMove = false;

	m_fMaxHp = 100;
	m_fCurrHp = 100;
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
}

void cPlayer::Update()
{
	// �ȼ� �浹 ó�� ��ġ ����
	float probeX = m_pPlayerImage->GetPosX() + m_pMap->GetPosX();
	float probeY = m_pPlayerImage->GetPosY() + m_pMap->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2 + 1;

	// false ��� ������ ����
	if (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY))
	{
		
		// �������� �����ȼ� �˻�
		int deepY = 0;
		while (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - deepY - 1))
		{
			++deepY;
		}

		// ���� ���� �� �� ���ӿ� ������ŭ ���� �ø��� ���� ����
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - deepY);
		m_fGravity = 0.0f;
		m_isJumpping = false;
	}
	else
	{
		// �߷��� ����Ͽ� ����
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() + m_fGravity);
		m_fGravity += GRAVITY;
	}

	//else if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - 5) == false)
	//	m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - 5);

	// ȭ��󿡼��� ������ ���� ����
	if (g_pKeyManager->isStayKeyDown('A') && m_pPlayerImage->GetPosX() > WINSIZEX / 5)
	{
		m_isMapMove = false;
		m_pPlayerImage->SetPosX(m_pPlayerImage->GetPosX() - m_fMoveSpeed);
	}
	else if (g_pKeyManager->isStayKeyDown('D') && m_pPlayerImage->GetPosX() < WINSIZEX / 2)
	{
		m_isMapMove = false;
		m_pPlayerImage->SetPosX(m_pPlayerImage->GetPosX() + m_fMoveSpeed);
	}
	else
		m_isMapMove = true;

	if (!m_isJumpping && g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		m_isJumpping = true;
	}

	if (m_isJumpping)
	{
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - m_fJumpPower);
	}

	// ü�¹� ������Ʈ
	m_pHpBar->SetPosX(m_pPlayerImage->GetPosX());
	m_pHpBar->SetPosY(m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2 - 10);
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
	m_pHpBar->Update();
}

void cPlayer::Render()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	BoudingLineMake(g_hDC, m_pPlayerImage->GetBoundingBox().left,
		m_pPlayerImage->GetBoundingBox().top,
		m_pPlayerImage->GetFrameWidth(),
		m_pPlayerImage->GetFrameHeight());

	DeleteObject(hSelectPen);
	DeleteObject(hPen);

	m_pPlayerImage->FrameRender(g_hDC,
		m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2,
		m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2,
		1, 0, 8, 0, 3);

	m_pHpBar->Render();

	char szBuf[128];
	string str("ĳ���� ��ġ(X) : ");
	str += itoa(m_pPlayerImage->GetPosX(), szBuf, 10);
	TextOut(g_hDC, 10, 10, str.c_str(), str.length());

	str = "�� �̵� : ";
	str += itoa(m_isMapMove, szBuf, 10);
	TextOut(g_hDC, 10, 50, str.c_str(), str.length());
}