#pragma once
#include "cGameNode.h"

#define RECT_SIZE 50

struct tagPos
{
	float x;
	float y;
};

struct tagNode;

struct tagEdgeInfo
{
	tagNode*	pNode;
	float		fEdgeCost;
};

struct tagDijkstra
{
	float	fCost;
	int		nVia;
	bool	isClosed;
};

struct tagNode
{
	tagPos					stPos;
	int						nIndex;
	vector<tagEdgeInfo*>	vecEdgeInfos;
	tagDijkstra				stDijkInfo;
};

class cDijkstraTest : public cGameNode
{
private:
	tagPos				m_stPos;		// 플레이어 오브젝트
	int					m_nTargetIndex;	// 목적지 노드

	vector<tagNode*>	m_vecNodes;		// 전체 노드를 담을 벡터
	bool				m_isMoving;		// 움직임 시작

	int					m_nStartIndex;	// 시작 노드 인덱스 번호
	int					m_nDestIndex;	// 도착 노드 인덱스 번호

	vector<int>			m_vecPathIndex;	// 경로 설정 벡터

	//map<int, int>		m_mapTest;
	map<float, int>		m_mapOpenNodes; // 코스트, 노드인덱스

private:
	// 1. 노드 추가 : 다익스트라 정보 초기화
	int AddNewNode();
	// 2. 엣지 추가 : 엣지 정보 초기화(엣지 코스트)
	void MakeEdge(int edgeIndex);
	// 3. 출발지, 도착지 설정
	void SetStartNDest();
	/* 4. 다익스트라 알고리즘
		a. 시작 노드 정보 갱신(코스트: 0, 비아: 자기자신)
		=========================================================
		b. 클로즈 되지 않은 노드 중에 비용이 가장 작은 노드를 찾는다.
			- 오픈 노드들만 따로 관리하는 맵을 사용 하도록 수정
			- 흰트 : 맵은 레드블랙 트리로 키값에 대해서 자동 정렬이 된다.
			- 비용이 가장 작은 노드를 찾은 검색 과정을 삭제
		=========================================================
		c. 위에서 찾은 노드를 클로즈 하고 주변 노드를 갱신 한다.
			- 갱신:	현재 설정 된 코스트와 새로 설정 될 코스트를 비교하여
					새 코스트가 더 작은 경우만 갱신한다.

					코스트 = 현재 노드까지의 비용 + 엣지 코스트
					비아 = 현재 노드
		d. 도착지가 클로즈 될 때까지 b와 c를 반복한다.
		=========================================================
		e. 도착지에서 부터 출발지까지 거꾸로 Via를 타고 올라오면서 경로 설정
		f. 설정 된 경로대로 움직인다. */
	void ComputingDijkstra();

	// 플레이어 이동 함수
	void UpdateMoving();

public:
	cDijkstraTest() {};
	virtual ~cDijkstraTest() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};