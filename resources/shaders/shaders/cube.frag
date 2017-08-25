#version 450

in vec4 vCol;

out vec4 outColor;

void main()
{
    outColor = dot(-normalize(vec4(1,1,1,0)), vNormal) * outColor;
	outColor.a = 1;
}