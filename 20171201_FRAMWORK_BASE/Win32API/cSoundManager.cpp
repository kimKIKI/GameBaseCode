#include "stdafx.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
{
	// ���� �ý��� ����
	System_Create(&m_pSystem);

	// ���� ä�μ� ����
	m_pSystem->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	// ����, ä�� ���� �Ҵ�
	m_ppSound = new Sound*[TOTALSOUNDBUFFER];
	m_ppChannel = new Channel*[TOTALSOUNDBUFFER];

	// �޸� �ʱ�ȭ
	memset(m_ppSound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(m_ppChannel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);
}


cSoundManager::~cSoundManager()
{
	// ���� �� ä�� ����
	if (m_ppChannel != NULL || m_ppSound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; ++i)
		{
			if (m_ppChannel != NULL)
			{
				if (m_ppChannel[i])
				{
					m_ppChannel[i]->stop();
				}
			}

			if (m_ppSound != NULL)
			{
				if (m_ppSound[i])
				{
					m_ppSound[i]->release();
				}
			}
		}
	}

	// �޸� �����
	SAFE_DELETE_ARRAY(m_ppChannel);
	SAFE_DELETE_ARRAY(m_ppSound);

	// ���� �ý��� �ݱ�
	if (m_pSystem != NULL)
	{
		m_pSystem->release();
		m_pSystem->close();
	}
}

void cSoundManager::Update()
{
	// ���� �ý����� ��� ������Ʈ �����
	// ������ �ٲ�ų�, ����� ���� ���带 ä�ο��� ���� ����
	// �پ��� �۾��� �ڵ����� ���ش�.
	m_pSystem->update();
}

void cSoundManager::AddSound(string key, string fileName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm) // ������̳�?
		{
			m_pSystem->createStream(fileName.c_str(), FMOD_LOOP_NORMAL, NULL, &m_ppSound[m_mTotalSounds.size()]);
		}
		else // ����Ʈ��?
		{
			m_pSystem->createSound(fileName.c_str(), FMOD_LOOP_NORMAL, NULL, &m_ppSound[m_mTotalSounds.size()]);
		}
	}
	else
	{
		m_pSystem->createSound(fileName.c_str(), FMOD_DEFAULT, NULL, &m_ppSound[m_mTotalSounds.size()]);
	}

	// �ʿ� ���带 �߰� �Ѵ�.
	m_mTotalSounds.insert(make_pair(key, &m_ppSound[m_mTotalSounds.size()]));
}

void cSoundManager::ReleaseSound(string key)
{
	int count = 0;
	arrSoundIter iter = m_mTotalSounds.begin();
	for (; iter != m_mTotalSounds.end(); ++iter, ++count)
	{
		if (key == iter->first)
		{
			if (m_ppChannel != NULL)
			{
				if (m_ppChannel[count])
					m_ppChannel[count]->stop();
			}

			if (m_ppSound != NULL)
			{
				if (m_ppSound[count])
					m_ppSound[count]->release();

				//(*(iter->second))->release();
			}

			m_mTotalSounds.erase(iter);
			break;
		}
	}
}

void cSoundManager::Play(string key, float volume)
{
	int count = 0;
	arrSoundIter iter = m_mTotalSounds.begin();
	for (; iter != m_mTotalSounds.end(); ++iter, ++count)
	{
		if (key == iter->first)
		{
			// ���� �÷���
			m_pSystem->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &m_ppChannel[count]);
			// ���� ����
			m_ppChannel[count]->setVolume(volume);
			break;
		}
	}
}

void cSoundManager::Stop(string key)
{
	int count = 0;
	arrSoundIter iter = m_mTotalSounds.begin();
	for (; iter != m_mTotalSounds.end(); ++iter, ++count)
	{
		if (key == iter->first)
		{
			m_ppChannel[count]->stop();
			break;
		}
	}
}

void cSoundManager::Pause(string key)
{
	int count = 0;
	arrSoundIter iter = m_mTotalSounds.begin();
	for (; iter != m_mTotalSounds.end(); ++iter, ++count)
	{
		if (key == iter->first)
		{
			m_ppChannel[count]->setPaused(true);
			break;
		}
	}
}

void cSoundManager::Resume(string key)
{
	int count = 0;
	arrSoundIter iter = m_mTotalSounds.begin();
	for (; iter != m_mTotalSounds.end(); ++iter, ++count)
	{
		if (key == iter->first)
		{
			m_ppChannel[count]->setPaused(false);
			break;
		}
	}
}

bool cSoundManager::IsPlaySound(string key)
{
	bool isPlay = false;
	int count = 0;
	arrSoundIter iter = m_mTotalSounds.begin();
	for (; iter != m_mTotalSounds.end(); ++iter, ++count)
	{
		if (key == iter->first)
		{
			m_ppChannel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool cSoundManager::IsPauseSound(string key)
{
	bool isPause = false;
	int count = 0;
	arrSoundIter iter = m_mTotalSounds.begin();
	for (; iter != m_mTotalSounds.end(); ++iter, ++count)
	{
		if (key == iter->first)
		{
			m_ppChannel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}

void cSoundManager::VolumeUp(string key)
{
	float volume;
	int count = 0;
	arrSoundIter iter = m_mTotalSounds.begin();
	for (; iter != m_mTotalSounds.end(); ++iter, ++count)
	{
		if (key == iter->first)
		{
			m_ppChannel[count]->getVolume(&volume);
			m_ppChannel[count]->setVolume(volume + 0.1f);
			break;
		}
	}
}

void cSoundManager::VolumeDown(string key)
{
	float volume;
	int count = 0;
	arrSoundIter iter = m_mTotalSounds.begin();
	for (; iter != m_mTotalSounds.end(); ++iter, ++count)
	{
		if (key == iter->first)
		{
			m_ppChannel[count]->getVolume(&volume);
			m_ppChannel[count]->setVolume(volume - 0.1f);
			break;
		}
	}
}
