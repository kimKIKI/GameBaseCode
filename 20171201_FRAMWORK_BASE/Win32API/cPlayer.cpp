#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
{
	rt = new RECT;
	*rt = RectMake(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(rt);
}

void cPlayer::Update()
{
	int rand = GetRandom(4);

	switch (rand)
	{
	case 0:
		cout << "오른쪽" << endl;
		rt->left += 1;
		rt->right += 1;
		break;
	case 1:
		cout << "왼쪽" << endl;
		rt->left -= 1;
		rt->right -= 1;
		break;
	case 2:
		cout << "위쪽" << endl;
		rt->top += 1;
		rt->bottom += 1;
		break;
	case 3:
		cout << "아래쪽" << endl;
		rt->top -= 1;
		rt->bottom -= 1;
		break;
	}
}

void cPlayer::Render()
{
	RectangleMake(g_hDC, *rt);
}