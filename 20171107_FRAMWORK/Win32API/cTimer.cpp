#include "stdafx.h"
#include "cTimer.h"


cTimer::cTimer()
{
	// ���� Ÿ�̸� ���� ���� üũ
	// ����ũ�� ������ (1 / 1,000,000)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_nPeriodFrequency))
	{
		m_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);

		// �ʴ� �ð� ��� ����
		m_fTimeScale = 1.0f / m_nPeriodFrequency;
	}
	else
	{
		m_isHardware = false;
		m_nLastTime = timeGetTime();
		m_fTimeScale = 1.0f / 1000.0f; // �и������� (1 / 1,000)
	}

	// Ÿ�̸� ���� ������ �ʱ�ȭ
	m_nFrameRate = 0;
	m_nFPSFrameCount = 0;
	m_fFPSTimeElapsed = 0.0f;
	m_fWorldTime = 0.0f;
}


cTimer::~cTimer()
{
}

void cTimer::Tick(float lockFPS)
{
	// ���� Ÿ�̸� Ȯ��
	if (m_isHardware)
	{
		// ����ũ�μ����� ������ ����Ѵ�.
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrTime);
	}
	else
	{
		m_nCurrTime = timeGetTime();
	}

	// ������ �ð����� ���� ���� �ð������� �����
	m_fTimeElapsed = (m_nCurrTime - m_nLastTime) * m_fTimeScale;

	if (lockFPS > 0.0f)
	{
		while (m_fTimeElapsed < (1.0f / lockFPS))
		{
			if (m_isHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrTime);
			else
				m_nCurrTime = timeGetTime();

			m_fTimeElapsed = (m_nCurrTime - m_nLastTime) * m_fTimeScale;
		}
	}

	m_nLastTime = m_nCurrTime;
	++m_nFPSFrameCount;
	m_fFPSTimeElapsed += m_fTimeElapsed;
	m_fWorldTime += m_fTimeElapsed;

	// ������ ī���� ������ 1�ʰ� �Ѿ��
	if (m_fFPSTimeElapsed > 1.0f)
	{
		m_nFrameRate = m_nFPSFrameCount;
		m_nFPSFrameCount = 0;
		m_fFPSTimeElapsed = 0.0f;
	}
}

unsigned int cTimer::GetFPS(char* str) const
{
	return m_nFrameRate;
}
