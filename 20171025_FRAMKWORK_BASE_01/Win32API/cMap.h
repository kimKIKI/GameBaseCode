#pragma once



class cMap
{
private:
	cImage*		m_pImgGround;		// 기본 지형 이미지
	cImage*		m_pImgGround2;		// 기본 지형 이미지
	cImage*		m_pObject;			// 움직이는 오브젝트
	bool		m_bMoveRight;

	cImage*		m_pImgMapBuffer;	// 최종적으로 픽셀 충돌을 위해서 만들어질 지형 이미지 버퍼
	cImage*		m_pImgMapBuffer2;	// 최종적으로 픽셀 충돌을 위해서 만들어질 지형 이미지 버퍼

	float       m_MapSpeed;         //맵이동
	void        MoveObject();
	int         m_GetX;
	int         m_MapsizeX;         //조건을 판단하기 위해서 Xsize


public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();
    
	void SetMoveSpeed(float Speed) { m_MapSpeed = Speed; }
	float GetMoveSpeed() { return  m_MapSpeed; };
   
	int  GetMapSize() { return m_MapsizeX; };
	
	int  GetX() { return m_GetX; };
	void SetX(int move) { m_GetX = move; };
	//void SetMap() {}

};

