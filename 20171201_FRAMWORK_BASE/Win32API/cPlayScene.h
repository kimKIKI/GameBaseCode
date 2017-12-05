#pragma once
#include "cGameNode.h"

#define RECT_SIZE 50

struct tagPosition
{
	float x;
	float y;
};

class cPlayScene : public cGameNode
{
private:
	tagPosition			m_stPos;
	vector<tagPosition>	m_vecTarget;
	int					m_nTargetIndex;

private:
	void AddNewTarget();
	void DeleteTarget();
	void UpdateMoving();

public:
	cPlayScene() {};
	virtual ~cPlayScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

