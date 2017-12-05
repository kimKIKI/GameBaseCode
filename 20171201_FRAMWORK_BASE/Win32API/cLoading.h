#pragma once
#include "cProgressBar.h"

enum LOAD_KIND
{
	LOAD_KIND_EMPTY,		// �� ��Ʈ�� �̹���
	LOAD_KIND_IMAGE_0,		// �Ϲ� �̹���
	LOAD_KIND_FRAMEIMAGE_0,	// ������ �̹���
	LOAD_KIND_FRAMEIMAGE_1,	// ������ �̹���
	LOAD_KIND_SOUND,		// ����
	LOAD_KIND_END
};

struct tagImageResource
{
	string key;				// �̹��� Ű��
	const char* fileName;	// ���� �̸�
	int x, y;				// ��ġ ��ǥ
	int width, height;		// ���� ���� ũ��
	int frameX, frameY;		// ������ ����
	bool isTrans;			// ���(����Ÿ) ó��
	COLORREF transColor;	// ���(����Ÿ) ��
};

struct tagSoundResource
{
	string key;				//�̹��� Ű��
	const char* fileName;	//�����̸�
	bool bgm;				//��� �����̳�?
	bool loop;				//�ݺ� �Ҳ���?
};

class cLoadItem
{
private:
	LOAD_KIND			m_eKind;
	tagImageResource	m_stImageResource;
	tagSoundResource	m_stSoundResource;

public:
	cLoadItem() {};
	~cLoadItem() {};

	// �� ��Ʈ������ �ʱ�ȭ �� �߰�
	void InitForEmpty(string key, int width, int height);
	// �̹��� - ���Ϸ� �ʱ�ȭ �� �߰�
	void InitForImage(string key, const char* fileName,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// ������ �̹��� - ���Ϸ� �ʱ�ȭ �� �߰�
	void InitForFrameImage(string key, const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void InitForFrameImage(string key, const char* fileName, int width, int height,
		int frameX, int frameY, int x, int y, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// ���� - �ʱ�ȭ �� �߰�
	void InitForSound(string key, const char* fileName, bool bgm, bool loop);

	// �ε� ������ ���� ��������
	LOAD_KIND GetLoadingKind() { return m_eKind; }
	// �̹��� ���ҽ� ���� ��������
	tagImageResource GetImageResource() { return m_stImageResource; }
	// ���� ���ҽ� ���� ��������
	tagSoundResource GetSoundResource() { return m_stSoundResource; }
};

class cLoading
{
private:
	vector<cLoadItem*>		m_vLoadItem;		// �ε��� ���ҽ����� ���� ����
	cImage*					m_pImgBackground;	// �ε� ȭ�� ���
	cProgressBar*			m_pLoadingBar;		// �ε� ��
	int						m_nCurrentGauge;	// ���� �ε� ������

public:
	cLoading() {};
	~cLoading() {};

	void Setup();
	void Render();
	void Release();

	void LoadEmpty(string key, int width, int height);
	void LoadImageFile(string key, const char* fileName,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void LoadFrameImage(string key, const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void LoadFrameImage(string key, const char* fileName, int width, int height,
		int frameX, int frameY, int x, int y, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void LoadSound(string key, const char* fileName, bool bgm = false, bool loop = false);

	// �ε� �Ϸ� �ƴ°�?
	bool LoadingDone();

	// �ε� ������ ���� ��������
	vector<cLoadItem*> GetLoadItem() { return m_vLoadItem; }
};

