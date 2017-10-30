#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"


cPlayer::cPlayer()
{
	//m_pPlayerImage = new cImage;
	//m_pPlayerImage->Setup("images/ch.bmp", 960, 960, 12, 12,
	//	200, MAP1_Y, true, RGB(255, 0, 255));

	m_pPlayerImage = g_pImageManager->FindImage("Player");

	m_pHpBar = new cProgressBar("ProgressBack", "ProgressFront",
		m_pPlayerImage->GetFrameWidth(), 10);

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");

	
	
}


cPlayer::~cPlayer()
{
	vector<string> saveData;
	char temp[128];

	saveData.push_back(itoa(m_fPosX, temp, 10));
	saveData.push_back(itoa(m_fPosY, temp, 10));
	saveData.push_back(itoa(m_fCurrHp, temp, 10));

	g_pFileDataManager->txtSave("PlayerData.txt", saveData);
}

void cPlayer::Setup()
{
	m_nDamageDelay = 0;
	m_nMapYPos = MAP1_Y;
	m_fJumpPower = 10.0f;

	m_fMaxHp = 100;
	m_fCurrHp = 100;
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);

	SetLanding();

	//vector<string> vecLoad = g_pFileDataManager->txtLoad("PlayerData.txt");

	//if (!vecLoad.empty())
	//{
	//	m_pPlayerImage->SetPosX(atoi(vecLoad[0].c_str()));
	//	m_pPlayerImage->SetPosY(atoi(vecLoad[1].c_str()));
	//	m_fCurrHp = atoi(vecLoad[2].c_str());
	//}
}

void cPlayer::Update()
{
	



	


	

	
}

void cPlayer::MiniRender()
{
	
}

void cPlayer::Render()
{
	

	m_pPlayerImage->FrameRender(g_hDC,
		m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2,
		m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2,
		1, 0, 8, 0, 3);

	
}

void cPlayer::SetLanding()
{
	
}