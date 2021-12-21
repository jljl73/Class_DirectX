#pragma once
#include "cCharacter.h"

class cCubeNode;
class cCubeMan : public cCharacter
{
public:
	cCubeMan();
	virtual ~cCubeMan();

protected:
	cCubeNode*		m_pRoot;
	cCubeNode*		m_pHead;
	D3DMATERIAL9	m_stMtl;
	LPDIRECT3DTEXTURE9 m_pTexture;

public:
	virtual void Setup() override;
	virtual void Update(iMap* pMap) override;
	virtual void Render() override;


};

