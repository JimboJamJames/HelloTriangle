#version 450

layout(location = 0)in vec4 position;
layout(location = 1)in vec2 UV;
layout(location = 2)in vec4 normal;
layout(location = 3)in vec4 tangent;
layout(location = 4)in vec4 bitangent;

layout(location = 0)uniform mat4 proj;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 model;

out vec2 vUV;
out mat4 vTBN;

void main()
{
	gl_Position = proj * view * model * pos;
	vUV = texCoord;

	vTBN = model * mat4(tangent, bitangent, normal, vec4(5,0,0,1));
}