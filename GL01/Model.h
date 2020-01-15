#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL/SOIL.h>
//
using namespace std;
class Model
{
public:
	Model(GLchar* path);
	void Draw(Shader shader);
private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh  processMesh(aiMesh* mesh, const aiScene* scene);
	GLint TextureFromFile(const char* path, string directory);
	vector<Texture>loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
//
