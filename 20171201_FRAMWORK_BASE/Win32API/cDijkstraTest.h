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
	tagPos				m_stPos;		// �÷��̾� ������Ʈ
	int					m_nTargetIndex;	// ������ ���

	vector<tagNode*>	m_vecNodes;		// ��ü ��带 ���� ����
	bool				m_isMoving;		// ������ ����

	int					m_nStartIndex;	// ���� ��� �ε��� ��ȣ
	int					m_nDestIndex;	// ���� ��� �ε��� ��ȣ

	vector<int>			m_vecPathIndex;	// ��� ���� ����

	//map<int, int>		m_mapTest;
	map<float, int>		m_mapOpenNodes; // �ڽ�Ʈ, ����ε���

private:
	// 1. ��� �߰� : ���ͽ�Ʈ�� ���� �ʱ�ȭ
	int AddNewNode();
	// 2. ���� �߰� : ���� ���� �ʱ�ȭ(���� �ڽ�Ʈ)
	void MakeEdge(int edgeIndex);
	// 3. �����, ������ ����
	void SetStartNDest();
	/* 4. ���ͽ�Ʈ�� �˰���
		a. ���� ��� ���� ����(�ڽ�Ʈ: 0, ���: �ڱ��ڽ�)
		=========================================================
		b. Ŭ���� ���� ���� ��� �߿� ����� ���� ���� ��带 ã�´�.
			- ���� ���鸸 ���� �����ϴ� ���� ��� �ϵ��� ����
			- ��Ʈ : ���� ����� Ʈ���� Ű���� ���ؼ� �ڵ� ������ �ȴ�.
			- ����� ���� ���� ��带 ã�� �˻� ������ ����
		=========================================================
		c. ������ ã�� ��带 Ŭ���� �ϰ� �ֺ� ��带 ���� �Ѵ�.
			- ����:	���� ���� �� �ڽ�Ʈ�� ���� ���� �� �ڽ�Ʈ�� ���Ͽ�
					�� �ڽ�Ʈ�� �� ���� ��츸 �����Ѵ�.

					�ڽ�Ʈ = ���� �������� ��� + ���� �ڽ�Ʈ
					��� = ���� ���
		d. �������� Ŭ���� �� ������ b�� c�� �ݺ��Ѵ�.
		=========================================================
		e. ���������� ���� ��������� �Ųٷ� Via�� Ÿ�� �ö���鼭 ��� ����
		f. ���� �� ��δ�� �����δ�. */
	void ComputingDijkstra();

	// �÷��̾� �̵� �Լ�
	void UpdateMoving();

public:
	cDijkstraTest() {};
	virtual ~cDijkstraTest() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};