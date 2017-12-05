#pragma once
#include "cGameNode.h"

#define TILE_SIZE_X (40)
#define TILE_SIZE_Y (40)

#define NUM_TILE_X (WINSIZEX / TILE_SIZE_X)
#define NUM_TILE_Y (WINSIZEY / TILE_SIZE_Y)

#define IMAGE_X(x, y) ((x + y * 8) % 20)
#define IMAGE_Y(x, y) ((x + y * 8) / 20)

enum E_TERRAIN { TR_UNWALKERABLE, TR_WALKABLE, TR_SWIMMABLE, TR_MAX };
enum E_OBJECT { OBJ_NONE, OBJ_NONEBREAKABLE, OBJ_BREAKABLE, OBJ_MAX };

struct tagTileInfo
{
	E_TERRAIN	eTerrain;
	POINT		ptTerrain;

	E_OBJECT	eObject;
	POINT		ptObject;
};

class cMapTool : public cGameNode
{
private:
	cImage*			m_pImgTileMap;		// Ÿ�ϵ��� ��� �ִ� ������ �̹��� ����
	tagTileInfo		m_stSelect;			// ������ Ÿ�� ��ġ ����

	cImage*			m_pImgDrawMap;		// ����� ��� �̹���
	// �ʰ� Ÿ�� ������ ������ Ÿ�� ���� �迭 �Ҵ�
	tagTileInfo		m_stTileInfo[NUM_TILE_Y][NUM_TILE_X];
	int          PosX;
	int          PosY;
	RECT         m_rtViewPort;

private:
	void SelectTerrain();
	void SelectObject();
	void DeleteObject();
	void DrawMap();

	void LoadMap();		// Ÿ�ϸ� ������ Ȱ���Ͽ� ���� ���� �׸��� �Լ�

public:
	cMapTool() {};
	virtual ~cMapTool() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

