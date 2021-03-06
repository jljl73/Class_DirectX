#pragma once

#include "Systems//IExecute.h"

class DrawMesh : public IExecute
{
	// Inherited via IExecute
	virtual void Initialize() override;
	virtual void Ready() override {};
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

private:
	Shader* shader;
	class Mesh* quad;
	class MeshGrid* grid;
	class MeshCube* cube;
	class MeshCylinder* cylinder[10];
	class MeshSphere* sphere[10];
};