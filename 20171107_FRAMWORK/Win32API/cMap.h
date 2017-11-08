#pragma once

class cPlayer;

class cMap
{
private:
	cImage*		m_pImgMap;			// �⺻ ���� �̹���(����Ÿ�� �ִ� ���� ����)
	cImage*		m_pImgMapBuffer;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����

	cPlayer*	m_pPlayer;

	float		m_fPosX;			// �� �̵���
	float		m_fPosY;			// �� �̵���

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	void SetPlayer(cPlayer* player) { m_pPlayer = player; }

	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
};