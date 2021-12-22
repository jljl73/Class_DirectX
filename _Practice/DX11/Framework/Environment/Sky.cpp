#include "Framework.h"
#include "Sky.h"

Sky::Sky()
{
	shader = new Shader(L"018_Sky.fx");
	buffer = new ConstantBuffer(&desc, sizeof(Desc));
	sBuffer = shader->AsConstantBuffer("CB_Sky");
	sphere = new MeshSphere(shader, 0.5f);
}

Sky::~Sky()
{
	SafeDelete(shader);
	SafeDelete(sphere);
	SafeDelete(buffer);
}

void Sky::Update()
{
	ImGui::ColorEdit3("Center", (float*)&desc.Center);
	ImGui::ColorEdit3("Apex", (float*)&desc.Apex);
	ImGui::InputFloat("Sky Height", &desc.Height, 0.1f);

	Vector3 position;
	Context::Get()->GetCamera()->Position(&position);
	sphere->GetTransform()->Position(position);
	sphere->Update();
}

void Sky::Render()
{
//	sphere->Pass(1); // : Wireframe
	buffer->Apply();
	sBuffer->SetConstantBuffer(buffer->Buffer());
	sphere->Render();
}
