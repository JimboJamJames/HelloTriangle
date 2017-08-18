#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"

int main()
{
	Context context;
	context.init(800, 600);
	Vertex verts[4] = { { { .5,  .5,  0, 1 },{ 1,1,0,1 } },   //0
	{ { -.5,  .5,  0, 1 },{ 0,1,1,1 } },   //1
	{ { -.5, -.5,  0, 1 },{ 1,0,1,1 } },   //2
	{ { .5, -.5,  0, 1 },{ 1,0,0,1 } } }; //3

	unsigned idxs[6] = { 1,2,3,
		0,3,1 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);
	
	//Geometry g = makeNGon(7, 6, 0);

	const char* vsource = // once per vertex
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 0) uniform float time;\n"
		"flat out vec4 vColor;"
		"void main ()\n"
		"{\n"
		"gl_Position = position;\n"
		"vColor = color;"
		"}\n";

	const char* fsource = // once per pixel
		"#version 450\n"
		"out vec4 outColor;\n"
		"flat in vec4 vColor;"
		"void main ()\n"
		"{\n"
		"outColor = vColor;\n"
		"}\n";

	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 800, 600 };

	while (context.step())
	{
		clearFramebuffer(f);
		setUniform(s, 0, context.getTime());
		s0_draw(f, s, g);
	}

	freeGeometry(g);
	freeShader(s);

	context.term();
	return 0;
}