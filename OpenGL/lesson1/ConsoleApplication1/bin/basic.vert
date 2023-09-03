#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in ivec4 boneIDs;
layout (location = 3) in vec4 weights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int gDisplayBoneIndex;

const int MAX_BONE_INFLUENCE = 4;

out vec2 TexCoord;
out vec4 colorOut;

void main()
{
    colorOut = vec4(0.1f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE; i++)
    {
        if(boneIDs[i] == 6)
        {
            colorOut = vec4(1.0f);
        }
    }

    gl_Position = projection * view * model * vec4(pos, 1.0f);
    TexCoord = texCoord;
};