#ifndef MESH_H
#define	MESH_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "GL/glew.h"
#include "glm/glm.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoords;
	//bone indexes which will influence this vertex
	GLint m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	GLfloat m_Weights[MAX_BONE_INFLUENCE];
	GLint vertexId;
};

struct BoneInfo
{
	/*id is index in finalBoneMatrices*/
	int id;

	/*offset matrix transforms vertex from model space to bone space*/
	glm::mat4 offset;

};

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool loadOBJ(const std::string& filename);
	bool loadFBX(const std::string& filename);
	void draw();

	std::map<std::string, GLint> m_BoneNameToIndexMap;
	GLint m_BoneCounter{0};

private:
	void initBuffers();

	bool mLoaded;
	std::vector<Vertex> mVertices;
	GLuint mVBO, mVAO;
};

#endif // !MESH_H

