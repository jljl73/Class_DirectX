#include "framework.h"
#include "cCubeMan.h"
#include "cCubeNode.h"
#include "cBody.h"
#include "cHead.h"
#include "cLeftArm.h"
#include "cLeftLeg.h"
#include "cRightArm.h"
#include "cRightLeg.h"

cCubeMan::cCubeMan()
	: m_pRoot(NULL)
	, m_pTexture(NULL)
{
}

cCubeMan::~cCubeMan()
{
	Safe_Release(m_pTexture);
	if (m_pRoot)
		m_pRoot->Destroy();
}

void cCubeMan::Setup()
{
	cCharacter::Setup();

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f); // 주변
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f); // 텍스처
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f); // 메탈릭

	D3DXCreateTextureFromFile(g_pD3DDevice, L"neon.png", &m_pTexture);

	cBody* pBody = new cBody;
	pBody->Setup();
	pBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = pBody;


	cHead* pHead = new cHead;
	pHead->Setup();
	m_pRoot->AddChild(pHead);

	cLeftArm* pLeftArm = new cLeftArm;
	pLeftArm->Setup();
	pLeftArm->SetRotDeltaX(0.05f);
	m_pRoot->AddChild(pLeftArm);

	cRightArm* pRightArm = new cRightArm;
	pRightArm->Setup();
	pRightArm->SetRotDeltaX(-0.05f);
	m_pRoot->AddChild(pRightArm);

	cLeftLeg* pLeftLeg = new cLeftLeg;
	pLeftLeg->Setup();
	pLeftLeg->SetRotDeltaX(-0.05f);
	m_pRoot->AddChild(pLeftLeg);

	cRightLeg* pRightLeg = new cRightLeg;
	pRightLeg->Setup();
	pRightLeg->SetRotDeltaX(0.05f);
	m_pRoot->AddChild(pRightLeg);
}

void cCubeMan::Update(iMap* pMap)
{
	cCharacter::Update(pMap);

	if(m_pRoot)
		m_pRoot->Update();
}

void cCubeMan::Render()
{

	if (g_pD3DDevice)
	{

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetMaterial(&m_stMtl);
		g_pD3DDevice->SetTexture(0, m_pTexture);

		cCharacter::Render();

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		if (m_pRoot)
			m_pRoot->Render();

		g_pD3DDevice->SetTexture(0, NULL);
	}
}
