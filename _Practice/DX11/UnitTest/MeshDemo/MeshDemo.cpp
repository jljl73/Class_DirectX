#include "stdafx.h"
#include "MeshDemo.h"
#include "Viewer/FreeCam.h"
#include "Environment/Terrain.h"

void MeshDemo::Initialize()
{
	Context::Get()->GetCamera()->Position(0, 60, -80);
	Context::Get()->GetCamera()->RotationDegree(30.0f, 0, 0);

	//shader = new Shader(L"015_Mesh.fx");
	shader = new Shader(L"016_Model.fx");

	// : mesh
	floor = new Material(shader);
	floor->DiffuseMap("Floor.png");

	stone = new Material(shader);
	stone->DiffuseMap("Stones.png");

	brick = new Material(shader);
	brick->DiffuseMap("Bricks.png");

	wall = new Material(shader);
	wall->DiffuseMap("Wall.png");

	cube = new MeshCube(shader);
	cube->GetTransform()->Position(0, 5.0f, 0.0f);
	cube->GetTransform()->Scale(15.0f, 5.0f, 15.0f);

	grid = new MeshGrid(shader, 3, 3);
	grid->GetTransform()->Position(0, 0, 0);
	grid->GetTransform()->Scale(20, 1, 20);

	for (UINT i = 0; i < 5; ++i)
	{
		cylinder[i * 2] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder[i * 2]->GetTransform()->Position(-30, 6.0f, -15.0f + (float)i * 15.0f);
		cylinder[i * 2]->GetTransform()->Scale(5, 5, 5);
		 
		cylinder[i * 2 + 1] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder[i * 2 + 1]->GetTransform()->Position(30, 6.0f, -15.0f + (float)i * 15.0f);
		cylinder[i * 2 + 1]->GetTransform()->Scale(5, 5, 5);

		sphere[i * 2] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere[i * 2]->GetTransform()->Position(-30.0f, 15.0f, -15.0f + (float)i * 15.0f);
		sphere[i * 2]->GetTransform()->Scale(5, 5, 5);

		sphere[i * 2 + 1] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere[i * 2 + 1]->GetTransform()->Position(30.0f, 15.0f, -15.0f + (float)i * 15.0f);
		sphere[i * 2 + 1]->GetTransform()->Scale(5, 5, 5);
	}


	{ // : load model
		model = new Model();
		model->ReadMaterial(L"Eclipse/Eclipse");
		model->ReadMesh(L"Eclipse/Eclipse");

		modelRender = new ModelRender(shader, model);
		modelRender->GetTransform()->Position(0, 6.55f, 0);
		modelRender->GetTransform()->Scale(0.3f, 0.3f, 0.3f);
	}
}

void MeshDemo::Update()
{
	for (UINT i = 0; i < 10; i++)
	{
		sphere[i]->Update();
		cylinder[i]->Update();
	}

	cube->Update();
	grid->Update();
	modelRender->Update();
}

void MeshDemo::Render()
{
	wall->Render();
	for (UINT i = 0; i < 10; i++)
	{
		sphere[i]->Pass(0);
		sphere[i]->Render();
	}

	brick->Render();
	for (UINT i = 0; i < 10; ++i)
	{
		cylinder[i]->Pass(0);
		cylinder[i]->Render();
	}

	stone->Render();
	cube->Pass(0);
	cube->Render();

	floor->Render();
	grid->Pass(0);
	grid->Render();

	modelRender->Pass(1);
	modelRender->Render();
}