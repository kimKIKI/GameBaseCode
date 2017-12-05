#pragma once
#include "cSingletonBase.h"

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")	// lib ��ũ
using namespace FMOD;						// FMOD ���ӽ����̽�

// ���� ���� ����
#define SOUNDBUFFER (20)
// ä�� ����
#define EXTRACHANNELBUFFER (5)
// �� ���� ���� : ���۰� �۾Ƽ� ������ ������ �ذ��ϱ� ����
#define TOTALSOUNDBUFFER (SOUNDBUFFER + EXTRACHANNELBUFFER)

#define g_pSoundManager cSoundManager::GetInstance()

class cSoundManager : public cSingletonBase<cSoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System*		m_pSystem;		// �ý��� Ŭ���� ������
	Sound**		m_ppSound;		// ���� Ŭ���� ������
	Channel**	m_ppChannel;	// ä�� Ŭ���� ������

	arrSounds	m_mTotalSounds;	// ��ü ���� ���

public:
	cSoundManager();
	~cSoundManager();

	void Update();
	void AddSound(string key, string fileName, bool bgm = false, bool loop = false);
	void ReleaseSound(string key);

	void Play(string key, float volume = 1.0f); // ���� (0.0f ~ 1.0f)
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);
	bool IsPlaySound(string key);
	bool IsPauseSound(string key);
	void VolumeUp(string key);
	void VolumeDown(string key);
};

