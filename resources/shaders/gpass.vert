#version 450

layout(location = 0)out vec4 position; 
layout(location = 2)out vec2 texcoord;
layout(location = 3)out vec4 normal;
layout(location = 4)out vec4 tangent;
layout(location = 5)out vec4 bitangent;

layout (location = 0) uniform mat4 projl
layout (location = 1) uniform mat4 view;

layout (location = 2) uniform mat4 model;

out vec2 vUV;
out vec3 vPos;
out mat4 vTBN;

void main()
{
	gl_position = proj * view * model * position;

	vTBN = view * model * mat4(tangent, bitangent, normal, vec3(0,0,0,0));
	vUV = texcoord;
	vPos = (view * model * position).xyz;
}