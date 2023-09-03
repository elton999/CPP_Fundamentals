#version 330 core

in vec2 TexCoord;
in vec4 colorOut;
out vec4 frag_color;

uniform sampler2D myTexture1;
uniform sampler2D myTexture2;

void main()
{
    frag_color = mix(texture(myTexture1, TexCoord), texture(myTexture2, TexCoord), 0.2) * colorOut;
};