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
	cImage*			m_pImgTileMap;		// 타일들이 들어 있는 프레임 이미지 파일
	tagTileInfo		m_stSelect;			// 선택한 타일 위치 저장

	cImage*			m_pImgDrawMap;		// 드로잉 대상 이미지
	// 맵과 타일 사이즈 비율로 타일 정보 배열 할당
	tagTileInfo		m_stTileInfo[NUM_TILE_Y][NUM_TILE_X];
	int          PosX;
	int          PosY;
	RECT         m_rtViewPort;

private:
	void SelectTerrain();
	void SelectObject();
	void DeleteObject();
	void DrawMap();

	void LoadMap();		// 타일맵 정보를 활용하여 실제 맵을 그리는 함수

public:
	cMapTool() {};
	virtual ~cMapTool() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

