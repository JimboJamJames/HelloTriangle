#version 450

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;

out vec2 vUV;

void main()
{
	gl_Position = position;
	vUV = texcoord;
}