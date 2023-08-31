#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Mesh.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class GameObject
{
public:
	GameObject(ShaderProgram* shader, string mesh_path, string texture_path);

	ShaderProgram *m_shaderProgram;
	Mesh m_mesh;
	Texture2D m_texture;

	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;

	void Update(float dt);
	void UpdateData();
	
	void Draw();
};

#endif // GAMEOBJECT_H


