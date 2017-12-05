#include "stdafx.h"
#include "cDijkstraTest.h"


void cDijkstraTest::Setup()
{
	m_stPos.x = 15;
	m_stPos.y = WINSIZEY / 2;
	m_isMoving = false;

	m_nStartIndex = -1;
	m_nDestIndex = -1;

	// ���ͽ�Ʈ�� �ʱ�ȭ
	m_vecPathIndex.clear();
	m_mapOpenNodes.clear();

	for (int i = 0; i < m_vecNodes.size(); ++i)
	{
		m_vecNodes[i]->stDijkInfo.fCost = FLT_MAX;
		m_vecNodes[i]->stDijkInfo.nVia = -1;
		m_vecNodes[i]->stDijkInfo.isClosed = false;
	}

	//m_mapTest.insert(make_pair(3, 1));
	//m_mapTest.insert(make_pair(6, 1));
	//m_mapTest.insert(make_pair(2, 1));
	//m_mapTest.insert(make_pair(4, 1));
	//m_mapTest.insert(make_pair(2, 2));
	//m_mapTest.insert(make_pair(4, 2));

	//for (auto iter = m_mapTest.begin(); iter != m_mapTest.end(); ++iter)
	//	cout << "Ű �� : " << iter->first << " - �����Ͱ� : " << iter->second << endl;

	//m_mapTest.at(3); // 3��° �����͸� �ҷ��´�. (���� �� ���� �󿡼��� 3��°)
	//m_mapTest.find(5); // Ű���� 5�� �����͸� ã�Ƽ� �ҷ��´�.
}

void cDijkstraTest::Update()
{
	static int nEdgeIndex = -1;

	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

	if (m_isMoving)
	{
		UpdateMoving();

		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		{
			Setup();
		}
	}
	else
	{
		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		{
			if (!m_vecNodes.empty())
			{
				m_isMoving = true;

				ComputingDijkstra();
				//m_pTargetNode = m_nStartIndex;
				m_nTargetIndex = m_vecPathIndex.back();
				m_vecPathIndex.pop_back();
			}
		}
		else if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
		{
			nEdgeIndex = AddNewNode();

			cout << "���� ��� : " << nEdgeIndex << endl;
		}
		else if (g_pKeyManager->isOnceKeyUp(VK_LBUTTON) && nEdgeIndex != -1)
		{
			// ���� �ε����� -1�� �ƴ� ��� ���� ������ �õ� �Ѵ�.
			MakeEdge(nEdgeIndex);
		}
		else if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
		{
			SetStartNDest();
		}
	}
}

void cDijkstraTest::Render()
{
	HPEN hPen;
	HPEN hOldPen;

	for (int i = 0; i < m_vecNodes.size(); ++i)
	{
		if (i == m_nStartIndex)
			hPen = (HPEN)CreatePen(0, 1, RGB(255, 0, 0));
		else if (i == m_nDestIndex)
			hPen = (HPEN)CreatePen(0, 1, RGB(0, 0, 255));
		else
			hPen = (HPEN)CreatePen(0, 1, RGB(0, 0, 0));

		hOldPen = (HPEN)SelectObject(g_hDC, hPen);

		RectangleMakeCenter(g_hDC, m_vecNodes[i]->stPos.x, m_vecNodes[i]->stPos.y,
			RECT_SIZE, RECT_SIZE);

		DeleteObject(hOldPen);
		DeleteObject(hPen);

		hPen = (HPEN)CreatePen(0, 1, RGB(0, 0, 0));
		hOldPen = (HPEN)SelectObject(g_hDC, hPen);

		float x1 = m_vecNodes[i]->stPos.x;
		float y1 = m_vecNodes[i]->stPos.y;

		for (int j = 0; j < m_vecNodes[i]->vecEdgeInfos.size(); ++j)
		{
			float x2 = m_vecNodes[i]->vecEdgeInfos[j]->pNode->stPos.x;
			float y2 = m_vecNodes[i]->vecEdgeInfos[j]->pNode->stPos.y;

			LineMake(g_hDC, x1, y1, x2, y2);
		}

		DeleteObject(hOldPen);
		DeleteObject(hPen);
	}

	EllipseMakeCenter(g_hDC, m_stPos.x, m_stPos.y, 30, 30);
}

void cDijkstraTest::Release()
{
	for (int i = 0; i < m_vecNodes.size(); ++i)
	{
		for (int j = 0; j < m_vecNodes[i]->vecEdgeInfos.size(); ++j)
			SAFE_DELETE(m_vecNodes[i]->vecEdgeInfos[j]);
		m_vecNodes[i]->vecEdgeInfos.clear();

		SAFE_DELETE(m_vecNodes[i]);
	}

	m_vecNodes.clear();
}

int cDijkstraTest::AddNewNode()
{
	for (int i = 0; i < m_vecNodes.size(); ++i)
	{
		RECT rt = RectMakeCenter(m_vecNodes[i]->stPos.x, m_vecNodes[i]->stPos.y, RECT_SIZE, RECT_SIZE);

		if (PtInRect(&rt, g_ptMouse))
			return i;
	}

	tagNode* newNode = new tagNode;
	newNode->stPos = { (float)g_ptMouse.x, (float)g_ptMouse.y };
	newNode->nIndex = m_vecNodes.size();
	// ���ͽ�Ʈ�� ���� �ʱ�ȭ
	newNode->stDijkInfo.fCost = FLT_MAX;
	newNode->stDijkInfo.nVia = -1;
	newNode->stDijkInfo.isClosed = false;

	m_vecNodes.push_back(newNode);

	return -1;
}

void cDijkstraTest::MakeEdge(int edgeIndex)
{
	for (int i = 0; i < m_vecNodes.size(); ++i)
	{
		RECT rt = RectMakeCenter(m_vecNodes[i]->stPos.x, m_vecNodes[i]->stPos.y, RECT_SIZE, RECT_SIZE);

		if (PtInRect(&rt, g_ptMouse))
		{
			if (i == edgeIndex) return;
			
			cout << "���� ��� ��ȣ : " << i << endl;

			// ������� ���� ����
			tagEdgeInfo* pEdgeInfo1 = new tagEdgeInfo;
			pEdgeInfo1->pNode = m_vecNodes[i];
			pEdgeInfo1->fEdgeCost = GetLength(m_vecNodes[i]->stPos.x, m_vecNodes[i]->stPos.y,
				m_vecNodes[edgeIndex]->stPos.x, m_vecNodes[edgeIndex]->stPos.y);
			// �������� �߰�
			m_vecNodes[edgeIndex]->vecEdgeInfos.push_back(pEdgeInfo1);

			// ������� ���� ����
			tagEdgeInfo* pEdgeInfo2 = new tagEdgeInfo;
			pEdgeInfo2->pNode = m_vecNodes[edgeIndex];
			pEdgeInfo2->fEdgeCost = pEdgeInfo1->fEdgeCost;
			// �������� �߰�
			m_vecNodes[i]->vecEdgeInfos.push_back(pEdgeInfo2);
		}
	}
}

void cDijkstraTest::SetStartNDest()
{
	for (int i = 0; i < m_vecNodes.size(); ++i)
	{
		RECT rt = RectMakeCenter(m_vecNodes[i]->stPos.x, m_vecNodes[i]->stPos.y, RECT_SIZE, RECT_SIZE);

		if (PtInRect(&rt, g_ptMouse))
		{
			if (m_nStartIndex == -1)
				m_nStartIndex = i;
			else if (m_nStartIndex == i)
				m_nStartIndex = -1;
			else if (m_nDestIndex == -1)
				m_nDestIndex = i;
			else if (m_nDestIndex == i)
				m_nDestIndex = -1;
		}
	}
}

void cDijkstraTest::ComputingDijkstra()
{
	//a.���� ��� ���� ����(�ڽ�Ʈ: 0, ��� : �ڱ��ڽ�)
	m_vecNodes[m_nStartIndex]->stDijkInfo.fCost = 0;
	m_vecNodes[m_nStartIndex]->stDijkInfo.nVia = m_nStartIndex;
	m_mapOpenNodes.insert(make_pair(0, m_nStartIndex));

	while (true)
	{
		//b.Ŭ���� ���� ���� ��� �߿� ����� ���� ���� ��带 ã�´�.
		float	fMinCost = m_mapOpenNodes.begin()->first;	// ���� ��� �ڽ�Ʈ
		int		nMinIndex = m_mapOpenNodes.begin()->second;	// ���� ������� ���õ� ����� �ε��� ��ȣ
		m_mapOpenNodes.erase(m_mapOpenNodes.begin());

		//for (int i = 0; i < m_vecNodes.size(); ++i)
		//{
		//	// Ŭ���� �� ���� �Ѿ��
		//	if (m_vecNodes[i]->stDijkInfo.isClosed) continue;

		//	if (m_vecNodes[i]->stDijkInfo.fCost < fMinCost)
		//	{
		//		fMinCost = m_vecNodes[i]->stDijkInfo.fCost;
		//		nMinIndex = i;
		//	}
		//}

		//c.������ ã�� ��带 Ŭ���� �ϰ� �ֺ� ��带 ���� �Ѵ�.
		m_vecNodes[nMinIndex]->stDijkInfo.isClosed = true;
		//d.�������� Ŭ���� �Ǹ� ����
		if (nMinIndex == m_nDestIndex) break;

		vector<tagEdgeInfo*> vecEdgeInfo = m_vecNodes[nMinIndex]->vecEdgeInfos;
		for (int i = 0; i < vecEdgeInfo.size(); ++i)
		{
			// ���� ���� �� �ڽ�Ʈ : ���� ��� �ڽ�Ʈ + ���� �ڽ�Ʈ
			float newCost = m_vecNodes[nMinIndex]->stDijkInfo.fCost + vecEdgeInfo[i]->fEdgeCost;

			// �� �ڽ�Ʈ�� �� ���� ��츸 �����Ѵ�.
			if (newCost < vecEdgeInfo[i]->pNode->stDijkInfo.fCost)
			{
				vecEdgeInfo[i]->pNode->stDijkInfo.fCost = newCost;
				vecEdgeInfo[i]->pNode->stDijkInfo.nVia = nMinIndex;
				m_mapOpenNodes.insert(make_pair(newCost, vecEdgeInfo[i]->pNode->nIndex));
			}
		}
	} //d.�������� Ŭ���� �� ������ b�� c�� �ݺ��Ѵ�.

	//e.���������� ���� ��������� �Ųٷ� Via�� Ÿ�� �ö���鼭 ��� ����
	int currIndex = m_nDestIndex;
	while (currIndex != m_nStartIndex)
	{
		m_vecPathIndex.push_back(currIndex);
		currIndex = m_vecNodes[currIndex]->stDijkInfo.nVia;
	}
	m_vecPathIndex.push_back(currIndex);
}

void cDijkstraTest::UpdateMoving()
{
	// ��ǥ�� ����
	if (GetLength(m_vecNodes[m_nTargetIndex]->stPos.x, m_vecNodes[m_nTargetIndex]->stPos.y,
		m_stPos.x, m_stPos.y) <= 3.0f + FLT_EPSILON)
	{
		// �̵��� ��ΰ� ���� �ִ� ��� (���� ������ �������� ���� ���)
		if (m_vecPathIndex.size() > 0)
		{
			m_nTargetIndex = m_vecPathIndex.back();
			m_vecPathIndex.pop_back();
		}
	}
	else // �������� ���� ��� �̵�
	{
		float angle = GetAngle(m_stPos.x, m_stPos.y,
			m_vecNodes[m_nTargetIndex]->stPos.x, m_vecNodes[m_nTargetIndex]->stPos.y);

		m_stPos.x += cosf(angle / 180 * PI) * 3.0f;
		m_stPos.y += -sinf(angle / 180 * PI) * 3.0f;
	}
}