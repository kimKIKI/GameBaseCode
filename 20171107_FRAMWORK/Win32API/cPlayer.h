#pragma once

class cProgressBar;
class cMap;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayerImage;		// �÷��̾� �̹��� ����

	float			m_fGravity;			// �߷� (������ ���)
	bool			m_isJumpping;		// ���� ���̳�?
	float			m_fJumpPower;		// ���� �Ŀ�
	float			m_fMoveSpeed;		// ĳ���� �̵� ���ǵ�
	bool			m_isMapMove;		// ���� �����̴°�?

	cProgressBar*	m_pHpBar;
	float			m_fMaxHp;
	float			m_fCurrHp;

	cMap*			m_pMap;
	cImage*			m_pImgMapBuffer;	// ��� ���� �̹���(����Ÿ�� ��� �ִ� �ȼ� �浹�� ��)

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();

	void SetMap(cMap* map) { m_pMap = map; }

	RECT GetBoundingBox() { return m_pPlayerImage->GetBoundingBox(); }
	float GetPosX() { return m_pPlayerImage->GetPosX(); }
	float GetPosY() { return m_pPlayerImage->GetPosY(); }
	float GetMoveSpeed() { return m_fMoveSpeed; }
	bool GetMapMove() { return m_isMapMove; }
	float GetSizeX() { return m_pPlayerImage->GetFrameWidth(); }
	float GetSizeY() { return m_pPlayerImage->GetFrameHeight(); }
};

