#version 330 core

layout (location=0) in vec3 vertexPos;
layout (location=1) in int colorIndex;

out vec3 fragmentColor;
out vec2 fragmentTexCoord;
const vec3 colors[3]=vec3[](
    vec3(1.0f,0.0f,0.0f),
    vec3(0.0f,1.0f,0.0f),
    vec3(0.0f,0.0f,1.0f)
);
void main()
{
    gl_Position = vec4(vertexPos, 1.0);
    fragmentColor = colors[gl_VertexID];
    fragmentTexCoord=vec2(0.5f,-0.5f)*(vertexPos.xy+vec2(1.0f));
}