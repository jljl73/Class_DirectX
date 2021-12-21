#include "stdafx.h"
#include "DrawTexture.h"
#include "Viewer/FreeCam.h"

void DrawTexture::Initialize()
{
	//((FreeCam*)Context::Get()->GetCamera())->Speed(40, 2);
	Context::Get()->GetCamera()->Position(0, 0, -3);
	shader = new Shader(L"005_Texture.fx");
	
	VertexTexture vertices[4];
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = Vector2(0, 1);
	vertices[1].Uv = Vector2(0, 0);
	vertices[2].Uv = Vector2(1, 1);
	vertices[3].Uv = Vector2(1, 0);

	{ // Vertex Buffer
		vertexCount = 4;
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;

		desc.ByteWidth = sizeof(VertexTexture) * vertexCount;

		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	//{ // Index Buffer
	//	indexCount = width * height * 6;
	//	indices = new UINT[indexCount];

	//	UINT index = 0;
	//	for (UINT z = 0; z < height; z++)
	//	{
	//		for (UINT x = 0; x < width; x++)
	//		{
	//			indices[index + 0] = (width + 1) * z + x;
	//			indices[index + 1] = (width + 1) * (z + 1) + x;
	//			indices[index + 2] = (width + 1) * z + x + 1;
	//			indices[index + 3] = (width + 1) * z + x + 1;
	//			indices[index + 4] = (width + 1) * (z + 1) + x;
	//			indices[index + 5] = (width + 1) * (z + 1) + x + 1;
	//			index += 6;
	//		}
	//	}

	UINT indices[6] = {0, 1, 2, 2, 1, 3};

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}

	//color = Color(0, 0, 0, 1);

	/*D3DX11CreateShaderResourceViewFromFile(D3D::GetDevice(),
		L"../../_Textures/Box.png", NULL, NULL, &srv, NULL);*/

	//shader->AsSRV("Map")->SetResource(srv);

	texture = new Texture(L"Box.png");
	shader->AsSRV("Map")->SetResource(texture->SRV());
}


void DrawTexture::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void DrawTexture::Update()
{
	/*ImGui::ColorEdit3("Color", (float*)&color);
	shader->AsVector("Color")->SetFloatVector(color);*/

	Matrix world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&world, 1, 1, 1);
	shader->AsMatrix("World")->SetMatrix(world);
	
	Matrix view = Context::Get()->View();
	shader->AsMatrix("View")->SetMatrix(view);
	
	Matrix projection = Context::Get()->Projection();
	shader->AsMatrix("Projection")->SetMatrix(projection);
}


void DrawTexture::Render()
{
	UINT stride = sizeof(VertexTexture);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Rect1
	{
		//static bool bWireframe = false;
		//ImGui::Checkbox("Wireframe", &bWireframe);
		////shader->Draw(0, (bWireframe? 0 : 1), 6);
		shader->DrawIndexed(0, 0, indexCount);
	}
	
}