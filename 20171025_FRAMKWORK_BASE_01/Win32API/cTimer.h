#pragma once
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
// timeGetTime �Լ��� ����ϱ� ���� ���̺귯�� �߰�
// �����찡 ���۵ǰ� �� �� �ð��� ���Ͻ��� �ش�.

class cTimer
{
private:
	bool			m_isHardware;		// ���� Ÿ�̸Ӹ� �����ϳ�?
	float			m_fTimeScale;		// �ð� �����
	float			m_fTimeElapsed;		// �������� �� ��� �ð� (1 / 60)
	__int64			m_nCurrTime;		// ���� �ð�
	__int64			m_nLastTime;		// ������ �ð�
	__int64			m_nPeriodFrequency;	// �ð� �ֱ�

	unsigned int	m_nFrameRate;		// FPS (Frame Per Second)
	unsigned int	m_nFPSFrameCount;	// FPS ī����
	float			m_fFPSTimeElapsed;	// FPS ������ �ð��� ���� �ð� �����
	float			m_fWorldTime;		// ��ü ��� �ð�

public:
	cTimer();
	~cTimer();

	// ���� �ð� ���
	void Tick(float lockFPS = 0.0f);
	// ���� FPS ��������
	unsigned int GetFPS(char* str = NULL) const;
	// �� �����Ӵ� ��� �ð� (1 / 60)
	float GetElapsedTime() const { return m_fFPSTimeElapsed; }
	// ��ü ��� �ð� ��������
	float GetWorldTime() const { return m_fWorldTime; }
};