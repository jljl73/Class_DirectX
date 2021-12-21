#include "stdafx.h"
#include "DrawTerrain.h"
#include "Viewer/FreeCam.h"
#include "Environment/Terrain.h"

void DrawTerrain::Initialize()
{
	((FreeCam*)Context::Get()->GetCamera())->Speed(40, 10);
	//shader = new Shader(L"010_Terrain.fx");
	//shader = new Shader(L"011_Terrain.fx");
	//shader = new Shader(L"012_TerrainGridLine.fx");
	shader = new Shader(L"013_Terrain_Splatting.fx");

	terrain = new Terrain(shader, L"HeightMap/HeightMapTest.png");
	//terrain = new Terrain(shader, L"Test2.png");
	terrain->BaseMap(L"Terrain/Dirt.png");
	terrain->LayerMap(L"Terrain/Grass (Lawn).jpg", L"HeightMap/AlphaMap256.png");

}


void DrawTerrain::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrain);
}

void DrawTerrain::Update()
{
	static Vector3 direction(-1, -1, 1);
	ImGui::SliderFloat3("LightDirection", (float*)&direction, -1, 1);
	Context::Get()->LightDirection(direction);
	   	
	terrain->Update();
}

void DrawTerrain::Render()
{
	terrain->Render();
}