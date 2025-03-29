#version 330 core

layout (location=0) in vec3 vertexPos;
out vec2 fragmentTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projetion;

void main()
{
    gl_Position = projection*view*model*vec4(vertexPos, 1.0);
    fragmentTexCoord=vec2(0.5f,-0.5f)*(vertexPos.xy+vec2(1.0f));
}