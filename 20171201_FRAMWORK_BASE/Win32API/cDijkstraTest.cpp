#include "stdafx.h"
#include "cDijkstraTest.h"


void cDijkstraTest::Setup()
{
	m_stPos.x = 15;
	m_stPos.y = WINSIZEY / 2;
	m_isMoving = false;

	m_nStartIndex = -1;
	m_nDestIndex = -1;

	// 다익스트라 초기화
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
	//	cout << "키 값 : " << iter->first << " - 데이터값 : " << iter->second << endl;

	//m_mapTest.at(3); // 3번째 데이터를 불러온다. (정렬 된 순서 상에서의 3번째)
	//m_mapTest.find(5); // 키값이 5인 데이터를 찾아서 불러온다.
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

			cout << "선택 노드 : " << nEdgeIndex << endl;
		}
		else if (g_pKeyManager->isOnceKeyUp(VK_LBUTTON) && nEdgeIndex != -1)
		{
			// 엣지 인덱스가 -1이 아닌 경우 엣지 연결을 시도 한다.
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
	// 다익스트라 정보 초기화
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
			
			cout << "연결 노드 번호 : " << i << endl;

			// 엣지노드 정보 생성
			tagEdgeInfo* pEdgeInfo1 = new tagEdgeInfo;
			pEdgeInfo1->pNode = m_vecNodes[i];
			pEdgeInfo1->fEdgeCost = GetLength(m_vecNodes[i]->stPos.x, m_vecNodes[i]->stPos.y,
				m_vecNodes[edgeIndex]->stPos.x, m_vecNodes[edgeIndex]->stPos.y);
			// 엣지노드로 추가
			m_vecNodes[edgeIndex]->vecEdgeInfos.push_back(pEdgeInfo1);

			// 엣지노드 정보 생성
			tagEdgeInfo* pEdgeInfo2 = new tagEdgeInfo;
			pEdgeInfo2->pNode = m_vecNodes[edgeIndex];
			pEdgeInfo2->fEdgeCost = pEdgeInfo1->fEdgeCost;
			// 엣지노드로 추가
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
	//a.시작 노드 정보 갱신(코스트: 0, 비아 : 자기자신)
	m_vecNodes[m_nStartIndex]->stDijkInfo.fCost = 0;
	m_vecNodes[m_nStartIndex]->stDijkInfo.nVia = m_nStartIndex;
	m_mapOpenNodes.insert(make_pair(0, m_nStartIndex));

	while (true)
	{
		//b.클로즈 되지 않은 노드 중에 비용이 가장 작은 노드를 찾는다.
		float	fMinCost = m_mapOpenNodes.begin()->first;	// 최저 비용 코스트
		int		nMinIndex = m_mapOpenNodes.begin()->second;	// 최저 비용으로 선택된 노드의 인덱스 번호
		m_mapOpenNodes.erase(m_mapOpenNodes.begin());

		//for (int i = 0; i < m_vecNodes.size(); ++i)
		//{
		//	// 클로즈 된 노드는 넘어가라
		//	if (m_vecNodes[i]->stDijkInfo.isClosed) continue;

		//	if (m_vecNodes[i]->stDijkInfo.fCost < fMinCost)
		//	{
		//		fMinCost = m_vecNodes[i]->stDijkInfo.fCost;
		//		nMinIndex = i;
		//	}
		//}

		//c.위에서 찾은 노드를 클로즈 하고 주변 노드를 갱신 한다.
		m_vecNodes[nMinIndex]->stDijkInfo.isClosed = true;
		//d.도착지가 클로즈 되면 정지
		if (nMinIndex == m_nDestIndex) break;

		vector<tagEdgeInfo*> vecEdgeInfo = m_vecNodes[nMinIndex]->vecEdgeInfos;
		for (int i = 0; i < vecEdgeInfo.size(); ++i)
		{
			// 새로 설정 될 코스트 : 현재 노드 코스트 + 엣지 코스트
			float newCost = m_vecNodes[nMinIndex]->stDijkInfo.fCost + vecEdgeInfo[i]->fEdgeCost;

			// 새 코스트가 더 작은 경우만 갱신한다.
			if (newCost < vecEdgeInfo[i]->pNode->stDijkInfo.fCost)
			{
				vecEdgeInfo[i]->pNode->stDijkInfo.fCost = newCost;
				vecEdgeInfo[i]->pNode->stDijkInfo.nVia = nMinIndex;
				m_mapOpenNodes.insert(make_pair(newCost, vecEdgeInfo[i]->pNode->nIndex));
			}
		}
	} //d.도착지가 클로즈 될 때까지 b와 c를 반복한다.

	//e.도착지에서 부터 출발지까지 거꾸로 Via를 타고 올라오면서 경로 설정
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
	// 목표에 도착
	if (GetLength(m_vecNodes[m_nTargetIndex]->stPos.x, m_vecNodes[m_nTargetIndex]->stPos.y,
		m_stPos.x, m_stPos.y) <= 3.0f + FLT_EPSILON)
	{
		// 이동할 경로가 남아 있는 경우 (최종 목적지 도착하지 않은 경우)
		if (m_vecPathIndex.size() > 0)
		{
			m_nTargetIndex = m_vecPathIndex.back();
			m_vecPathIndex.pop_back();
		}
	}
	else // 도착하지 않은 경우 이동
	{
		float angle = GetAngle(m_stPos.x, m_stPos.y,
			m_vecNodes[m_nTargetIndex]->stPos.x, m_vecNodes[m_nTargetIndex]->stPos.y);

		m_stPos.x += cosf(angle / 180 * PI) * 3.0f;
		m_stPos.y += -sinf(angle / 180 * PI) * 3.0f;
	}
}