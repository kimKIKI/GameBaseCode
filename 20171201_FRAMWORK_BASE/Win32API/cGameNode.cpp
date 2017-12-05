#include "stdafx.h"
#include "cGameNode.h"


cGameNode::cGameNode()
{
	m_pImgBackBuffer = new cImage;
	m_pImgBackBuffer->SetupEmpty(WINSIZEX, WINSIZEY);
}


cGameNode::~cGameNode()
{
	SAFE_DELETE(m_pImgBackBuffer);
}

void cGameNode::Update()
{
	InvalidateRect(g_hWnd, NULL, false);
}

LRESULT cGameNode::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_hDC = m_pImgBackBuffer->GetMemDC();

	switch (message)
	{
	case WM_CREATE:
		srand(time(NULL));
		rand();
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}