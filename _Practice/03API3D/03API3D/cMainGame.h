#pragma once
#include "cMatrix.h"
#include "cVector3.h"

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	HDC		m_MemDC;
	HBITMAP m_hOldBitmap, m_hBitmap;

	std::vector<cVector3>	m_vecVertex;
	std::vector<DWORD>		m_vecIndex;
	std::vector<cVector3>	m_vecLine;

	cMatrix					m_matWorld;
	cMatrix					m_matView;
	cMatrix					m_matProj;
	cMatrix					m_matViewport;

	cVector3				m_vEye;
	cVector3				m_vLookAt;
	cVector3				m_vUp;

	cVector3				m_vPosition;
	float					m_fBoxRotY;
	cVector3				m_vBoxDirection;

	// : Grid
	vector<cVector3>		m_vecLineVertex;
	cVector3				m_vAxisXTextPosition;
	cVector3				m_vAxisZTextPosition;

	// : Camera
	POINT					m_ptPrevMouse;
	bool					m_isLButtonDown;
	float					m_fCameraDistance;
	cVector3				m_vCamRotAngle;

	float					m_fScale;

public:
	void Setup();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// :
	void SetGrid();
	void DrawGrid();
	bool IsBackFace(cVector3& v1, cVector3& v2, cVector3& v3);

	void Update_Rotation();
	void Update_Move();
	void Update_Scale();
};