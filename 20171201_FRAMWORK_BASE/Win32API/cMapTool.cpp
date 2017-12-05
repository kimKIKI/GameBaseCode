#include "stdafx.h"
#include "cMapTool.h"


void cMapTool::Setup()
{
	m_pImgTileMap = g_pImageManager->AddFrameImage("TileMap", "images/tilemap.bmp",
		640, 256, 20, 8, true, RGB(255, 255, 255));

	m_pImgDrawMap = g_pImageManager->AddEmptyImage("DrawMap", WINSIZEX, WINSIZEY);
	for (int y = 0; y < NUM_TILE_Y; ++y)
	{
		for (int x = 0; x < NUM_TILE_X; ++x)
		{
			m_stTileInfo[y][x].eTerrain = TR_WALKABLE;
			m_stTileInfo[y][x].eObject = OBJ_NONE;
			m_stTileInfo[y][x].ptTerrain = { 2,0 };

		}
	}
	PosX = 320;
	PosY = 240;

}

void cMapTool::Update()
{
	
	
}

void cMapTool::Render()
{
	
	RectangleMake(g_hDC, 0, 0, 640, 480);
	m_pImgDrawMap->ViewPortRender(g_hDC, m_rtViewPort, 640, 480);
	for (int y = 0; y < 20; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			m_pImgTileMap->FrameRender(g_hDC, 640 + x * 20, y * 20,
				IMAGE_X(x, y), IMAGE_Y(x, y),20,20); //((x + y * 8) % 20)
				
		}
	}
	
}

void cMapTool::Release()
{
}

void cMapTool::SelectTerrain()
{
	
}

void cMapTool::SelectObject()
{
	if (g_ptMouse.y < 120)
		m_stSelect.eObject = OBJ_NONEBREAKABLE;
	else if (g_ptMouse.y < 140)
		m_stSelect.eObject = OBJ_BREAKABLE;

	m_stSelect.ptObject.x = (g_ptMouse.x - 640) / 20;
	m_stSelect.ptObject.y = g_ptMouse.y / 20;

}

void cMapTool::DeleteObject()
{
	
	
}

void cMapTool::DrawMap()
{
	
}

void cMapTool::LoadMap()
{
	POINT ptDraw;

	for (int y = 0; y < NUM_TILE_Y; ++y)
	{
		for (int x = 0; x < NUM_TILE_X; ++x)
		{
			if (m_stTileInfo[y][x].eObject == OBJ_NONE)
			{
				//ÁÖÈ²»ö ¹ÙÅÁ
				ptDraw.x = IMAGE_X(m_stTileInfo[y][x].ptTerrain.x, m_stTileInfo[y][x].ptTerrain.y);
				ptDraw.y = IMAGE_Y(m_stTileInfo[y][x].ptTerrain.x, m_stTileInfo[y][x].ptTerrain.y);

				m_pImgTileMap->FrameRender(m_pImgDrawMap->GetMemDC(), x * TILE_SIZE_X, y * TILE_SIZE_Y,
					ptDraw.x, ptDraw.y, TILE_SIZE_X, TILE_SIZE_Y);

			}
			else 
			{

				ptDraw.x = IMAGE_X(m_stTileInfo[y][x].ptObject.x, m_stTileInfo[y][x].ptObject.y);
				ptDraw.y = IMAGE_Y(m_stTileInfo[y][x].ptObject.x, m_stTileInfo[y][x].ptObject.y);

				m_pImgTileMap->FrameRender(m_pImgDrawMap->GetMemDC(), x*TILE_SIZE_X, y*TILE_SIZE_Y,
				 ptDraw.x,ptDraw.y,TILE_SIZE_X,TILE_SIZE_Y);

			}
		}

	}
}