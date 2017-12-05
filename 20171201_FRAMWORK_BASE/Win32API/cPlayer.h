#pragma once
class cPlayer
{
private:
	RECT*	rt;

public:
	cPlayer();
	~cPlayer();

	void Update();
	void Render();
};

