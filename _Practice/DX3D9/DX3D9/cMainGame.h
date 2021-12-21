#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cCubeMan;
class cGroup;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	/*std::vector<ST_PC_VERTEX>	m_vecLineVertex;
	std::vector<ST_PC_VERTEX>	m_vecTriangleVertex;*/
	cCubePC*					m_pCubePC;
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	cCubeMan*					m_pCubeMan;
	std::vector<cGroup*>		m_vecGroup;

	LPDIRECT3DTEXTURE9			m_pTexture;
	std::vector<ST_PT_VERTEX>	m_vecVertex;

	iMap*						m_pMap;
	std::vector<cGroup*>		m_vecMap;
public:
	void Setup();
	void Update();
	void Render();

	void Set_Light();
	void Set_Texture();
	/*void Setup_Line();
	void Draw_Line();

	void Setup_Triangle();
	void Draw_Triangle();*/

	void Draw_Texture();

	void Setup_Obj();
	void Draw_Obj();

	void Setup_Map();
	void Draw_Map();

	void Setup_Surface();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

