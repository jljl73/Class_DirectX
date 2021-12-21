#include "framework.h"
#include "cMainGame.h"
#include "cDeviceManager.h"

#include "cCubeMan.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cObjectLoader.h"
#include "cGroup.h"
#include "cObjMap.h"

cMainGame::cMainGame()
	:m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL)
	, m_pTexture(NULL)
	, m_pMap(NULL)
{}

cMainGame::~cMainGame()
{
	Safe_Delete(m_pGrid);
	Safe_Delete(m_pCubePC);
	Safe_Delete(m_pCamera);
	Safe_Delete(m_pCubeMan);
	Safe_Delete(m_pMap);
	Safe_Release(m_pTexture);

	for (auto p : m_vecGroup)
	{
		Safe_Release(p);
	}
	m_vecGroup.clear();

	for (auto p : m_vecMap)
	{
		Safe_Release(p);
	}
	m_vecMap.clear();

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCubePC = new cCubePC;
	m_pCubePC->Setup();
	
	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

	m_pCamera = new cCamera;
	//m_pCamera->Setup(m_pCubePC->GetPosition());
	m_pCamera->Setup(m_pCubeMan->GetPosition());

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	//Setup_Obj();
	Setup_Map();
	Set_Light();
	//Set_Texture();
	Setup_Surface();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void cMainGame::Update()
{
	if (m_pCubePC)
		m_pCubePC->Update();

	if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap);

	if (m_pCamera)
		m_pCamera->Update();

}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(36, 52, 73),
		1.0F, 0);

	g_pD3DDevice->BeginScene();
	
	// >> : Draw
	if (m_pGrid)
		m_pGrid->Render();
	/*if(m_pCubePC)
		m_pCubePC->Render();*/

	if (m_pCubeMan)
		m_pCubeMan->Render();
	
	//Draw_Texture();

	//Draw_Obj();
	Draw_Map();
	
	// << : Draw
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::Set_Light()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f); // 주변
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f); // 텍스처
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f); // 메탈릭

	D3DXVECTOR3		vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
}

void cMainGame::Set_Texture()
{

	D3DXCreateTextureFromFile(g_pD3DDevice, L"지수.jpg", &m_pTexture);

	ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);
	// : CW
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);
	
	v.p = D3DXVECTOR3(2, 0, 0);
	v.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(v);
	

}

void cMainGame::Draw_Texture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetTexture(0, NULL);

}

void cMainGame::Setup_Obj()
{
	cObjectLoader loader;
	loader.Load(m_vecGroup, (char*)"obj", (char*)"box.obj");
	//loader.Load(m_vecGroup, (char*)"obj", (char*)"map.obj");
}

void cMainGame::Draw_Obj()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	for (auto p : m_vecGroup)
	{
		p->Render();
	}
}

void cMainGame::Setup_Map()
{
	cObjectLoader loader;
	//loader.Load(m_vecGroup, (char*)"obj", (char*)"box.obj");
	loader.Load(m_vecMap, (char*)"obj", (char*)"map.obj");
}

void cMainGame::Draw_Map()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	for (auto p : m_vecMap)
	{
		p->Render();
	}
}

void cMainGame::Setup_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	m_pMap = new cObjMap((char*)"obj", (char*)"map_surface.obj", &matWorld);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
