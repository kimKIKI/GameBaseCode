#pragma once
#include "cGameNode.h"

class cMap;
class cPlayer;

#define LOADINGDELAY 350
#define IMAGEDELAY 100


class cMainGame : public cGameNode
{
private:
	bool			m_isPlaying;
	bool			m_isMain;

	int				m_LoadingDelay;
	int				m_Imagect;
	int				m_Imagect2;
	int				m_ImagectDelay;




	




	

	void LoadImageFromFile();


public:
	cMainGame();
	~cMainGame();

	void Setup();
	
	
	virtual void Update() override;
	virtual void Render() override;
};