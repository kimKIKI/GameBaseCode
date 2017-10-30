#pragma once



class cMap
{
private:
	cImage*		m_pImgGround;		// �⺻ ���� �̹���
	cImage*		m_pImgGround2;		// �⺻ ���� �̹���
	cImage*		m_pObject;			// �����̴� ������Ʈ
	bool		m_bMoveRight;

	cImage*		m_pImgMapBuffer;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����
	cImage*		m_pImgMapBuffer2;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����

	float       m_MapSpeed;         //���̵�
	void        MoveObject();
	int         m_GetX;
	int         m_MapsizeX;         //������ �Ǵ��ϱ� ���ؼ� Xsize


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

