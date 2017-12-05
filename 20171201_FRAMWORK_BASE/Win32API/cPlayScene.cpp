#include "stdafx.h"
#include "cPlayScene.h"


void cPlayScene::Setup()
{
	m_stPos.x = WINSIZEX / 2;
	m_stPos.y = WINSIZEY / 2;

	m_nTargetIndex = -1;	// 타겟이 없는 경우 -1
}

void cPlayScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		AddNewTarget();
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
	{
		DeleteTarget();
	}
	else
		UpdateMoving();
}

void cPlayScene::Render()
{
	EllipseMakeCenter(g_hDC, m_stPos.x, m_stPos.y, 30, 30);

	for (int i = 0; i < m_vecTarget.size(); ++i)
		RectangleMakeCenter(g_hDC, m_vecTarget[i].x, m_vecTarget[i].y, RECT_SIZE, RECT_SIZE);

	//if (m_nTargetIndex != -1)
	//{
	//	float length = GetLength(m_stPos.x, m_stPos.y,
	//		m_vecTarget[m_nTargetIndex].x, m_vecTarget[m_nTargetIndex].y);

	//	char szBuf[128];

	//	// 1.2332146

	//	int n1 = length; // 1
	//	int n2 = (length - n1) * 100; // 23

	//	itoa(n1, szBuf, 10);
	//	TextOut(g_hDC, 10, 100, szBuf, strlen(szBuf));
	//	itoa(n2, szBuf, 10);
	//	TextOut(g_hDC, 10, 140, szBuf, strlen(szBuf));
	//}
}

void cPlayScene::Release()
{
}

void cPlayScene::AddNewTarget()
{
	tagPosition newPos = { g_ptMouse.x, g_ptMouse.y };
	m_vecTarget.push_back(newPos);
}

void cPlayScene::DeleteTarget()
{
	for (auto iter = m_vecTarget.begin(); iter != m_vecTarget.end(); ++iter)
	{
		RECT rt = RectMakeCenter(iter->x, iter->y, RECT_SIZE, RECT_SIZE);

		if (PtInRect(&rt, g_ptMouse))
		{
			m_vecTarget.erase(iter);
			break;
		}
	}
}

void cPlayScene::UpdateMoving()
{
	if (m_vecTarget.empty())		// 타겟 벡터가 비어있는 경우
		m_nTargetIndex = -1;
	else if (m_nTargetIndex == -1)	// 타겟 설정이 아직 되지 않은 경우
		m_nTargetIndex = 0;
	else							// 타겟이 설정 된 경우
	{
		// 목표에 도착 했냐? 안했냐?

		// 목표에 도착
		if (GetLength(m_stPos.x, m_stPos.y,
			m_vecTarget[m_nTargetIndex].x, m_vecTarget[m_nTargetIndex].y) <= 3.0f + FLT_EPSILON)
		{
			m_nTargetIndex = (m_nTargetIndex + 1) % m_vecTarget.size();
		}
		else // 도착하지 않은 경우 이동
		{
			float angle = GetAngle(m_stPos.x, m_stPos.y,
				m_vecTarget[m_nTargetIndex].x, m_vecTarget[m_nTargetIndex].y);

			m_stPos.x += cosf(angle / 180 * PI) * 3.0f;
			m_stPos.y += -sinf(angle / 180 * PI) * 3.0f;
		}
	}
}