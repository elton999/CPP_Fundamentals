#include "GameObject.h"

GameObject::GameObject(ShaderProgram* shader, string mesh_path, string texture_path)
{
    m_shaderProgram = shader;
    m_mesh.loadOBJ(mesh_path);
    m_texture.loadTexture(texture_path);
}

void GameObject::Update(float dt)
{

}

void GameObject::UpdateData()
{
    glm::mat4 model;
    model = glm::translate(glm::mat4(), Position) * glm::scale(glm::mat4(), Scale);
    model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_shaderProgram->setUniform("model", model);
}

void GameObject::Draw()
{
    m_texture.bind(0);
    m_mesh.draw();
    m_texture.unbind(0);
}