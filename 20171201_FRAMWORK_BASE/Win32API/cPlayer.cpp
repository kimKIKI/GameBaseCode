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
		cout << "������" << endl;
		rt->left += 1;
		rt->right += 1;
		break;
	case 1:
		cout << "����" << endl;
		rt->left -= 1;
		rt->right -= 1;
		break;
	case 2:
		cout << "����" << endl;
		rt->top += 1;
		rt->bottom += 1;
		break;
	case 3:
		cout << "�Ʒ���" << endl;
		rt->top -= 1;
		rt->bottom -= 1;
		break;
	}
}

void cPlayer::Render()
{
	RectangleMake(g_hDC, *rt);
}