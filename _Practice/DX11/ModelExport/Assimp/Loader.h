#pragma once
class Loader
{
public:
	Loader();
	~Loader();

	void ReadFile(wstring file);
	void ExportMaterial(wstring savePath, bool bOverwrite = true);
	void ExportMesh(wstring savePath, bool bOverwrite = true);


private:
	void ReadMaterial();
	void WriteMaterial(wstring savePath, bool bOverwrite);
	string WriteTexture(string savePath, string file);

private:
	wstring file;
	Assimp::Importer* importer;
	const aiScene* scene;

	void ReadBoneData(aiNode* node, int index, int parent);
	void ReadMeshData(aiNode* node, int index);
	void WriteMeshData(wstring savePath, bool bOverwrite = true);

	vector<struct AsMaterial*> materials;
	vector<struct AsBone*> bones;
	vector<struct AsMesh*> meshes;
};