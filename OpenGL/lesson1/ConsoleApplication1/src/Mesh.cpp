#include "Mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>

Mesh::Mesh()
	: mLoaded(0)
{}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
}

bool Mesh::loadFBX(const std::string& filename)
{
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(filename,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if (scene)
    {
        const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            const aiMesh* paiMesh = scene->mMeshes[i];
            std::vector<glm::vec3> tempVertices;
            std::vector<glm::vec2> tempUVs;

            for (unsigned int j = 0; j < paiMesh->mNumVertices; j++)
            {
                const aiVector3D* pPos = &paiMesh->mVertices[j];
                const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][j]) : &Zero3D;

                glm::vec3 vertex = glm::vec3(pPos->x, pPos->y, pPos->z);
                glm::vec2 uv = glm::vec2(pTexCoord->x, pTexCoord->y);

                tempVertices.push_back(vertex);
                tempUVs.push_back(uv);
            }

            for (unsigned int j = 0; j < paiMesh->mNumFaces; j++)
            {
                for (unsigned int k = 0; k < 3; k++)
                {
                    Vertex meshVertex;
                    meshVertex.position = tempVertices[paiMesh->mFaces[j].mIndices[k]];
                    meshVertex.texCoords = tempUVs[paiMesh->mFaces[j].mIndices[k]];
                    mVertices.push_back(meshVertex);
                }
            }
        }
    }
    else
    {
        std::cerr << "Error Import: " << importer.GetErrorString() << std::endl;
        return false;
    }

    std::cout << "Import of scene " << filename << " succeeded." << std::endl;

    initBuffers();
    return (mLoaded = true);
}

bool Mesh::loadOBJ(const std::string& filename)
{
    std::vector<unsigned int> vertexIndices, uvIndices;
    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempUVs;

    if (filename.find(".obj") != std::string::npos)
    {
        std::ifstream fin(filename, std::ios::in);
        if (!fin)
        {
            std::cerr << "Cannot open " << filename << std::endl;
            return false;
        }

        std::cout << "Loading OBJ file " << filename << " ..." << std::endl;

        std::string lineBuffer;
        while (std::getline(fin, lineBuffer))
        {
            if (lineBuffer.substr(0, 2) == "v ")
            {
                std::istringstream v(lineBuffer.substr(2));
                glm::vec3 vertex;
                v >> vertex.x; v >> vertex.y; v >> vertex.z;
                tempVertices.push_back(vertex);
            }
            else if (lineBuffer.substr(0, 2) == "vt")
            {
                std::istringstream vt(lineBuffer.substr(3));
                glm::vec2 uv;
                vt >> uv.s; vt >> uv.t;
                tempUVs.push_back(uv);
            }
            else if (lineBuffer.substr(0, 2) == "f ")
            {
                int p1, p2, p3;
                int t1, t2, t3;
                int n1, n2, n3;
                const char* face = lineBuffer.c_str();
                int match = sscanf_s(face, "f  %i/%i/%i %i/%i/%i %i/%i/%i",
                    &p1, &t1, &n1,
                    &p2, &t2, &n2,
                    &p3, &t3, &n3);
                if (match != 9)
                    std::cout << "Failed to parse OBJ file using our very simple OBJ loader" << std::endl;

                // We are ignoring normal (for now)
                
                vertexIndices.push_back(p1);
                vertexIndices.push_back(p2);
                vertexIndices.push_back(p3);

                uvIndices.push_back(t1);
                uvIndices.push_back(t2);
                uvIndices.push_back(t3);
            }
        }

        fin.close();

        for (unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            glm::vec3 vertex = tempVertices[vertexIndices[i] - 1];
            glm::vec2 uv = tempUVs[uvIndices[i] - 1];

            Vertex meshVertex;
            meshVertex.position = vertex;
            meshVertex.texCoords = uv;

            mVertices.push_back(meshVertex);
        }
            initBuffers();
            return (mLoaded = true);

    }
        return false;
}

void Mesh::draw()
{
    if (!mLoaded) return;

    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

    glBindVertexArray(0);
}

void Mesh::initBuffers()
{
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);

    // tex coord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLfloat*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}