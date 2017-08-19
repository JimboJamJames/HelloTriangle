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
		"layout(location = 2) uniform float xpos;\n"
		"layout(location = 3) uniform float ypos;\n"
		"out vec4 vColor;\n"
		"out vec2 vUV;\n"
		"void main ()\n"
		"{\n"
		"gl_Position = position;\n"
		"gl_Position.y *= sin(time*2-position.y)/1.5;\n"
		"vColor = color;\n"
		"vUV = position.xy;\n"
		"}\n";

	const char* fsource = // once per pixel
		"#version 450\n"
		"out vec4 outColor;\n"
		"layout(location = 4) uniform sampler2D map;\n"
		"in vec4 vColor;\n"
		"in vec2  vUV;\n"
		"void main ()\n"
		"{\n"
		"outColor = texture(map, vUV);\n"
		"}\n";

	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 800, 800 };

	unsigned char pixels[] = { 255,0,255, 
							   255,255,0,
							   0,255,0,255,
							   255,0255,0};

	Texture t_magyel = makeTexture(4, 4, 3, pixels);

	glm::vec2 pos = { 0,0 };
	float prevTime = 0;
	float speed = 1.2f;

	while (context.step())
	{
		float ct = context.getTime();
		float dt = ct - prevTime;
		prevTime = ct;

		glm::vec2 vel = { 0,0 };
		vel.y += context.getKey('w');
		vel.x -= context.getKey('a');
		vel.y -= context.getKey('s');
		vel.x += context.getKey('d');

		if (glm::length(vel) > 0)
			pos += glm::normalize(vel) * dt * speed;

		clearFramebuffer(f);

		setUniform(s, 0, (float)context.getTime());
		//setUniform(s, 1, context.getKey(' '));
		setUniform(s, 2, pos.x);
		setUniform(s, 3, pos.y);

		setUniform(s, 4, t_magyel, 0);

		s0_draw(f, s, g);
	}

	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);

	context.term();
	return 0;
}