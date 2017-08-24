#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"
#include "glm\ext.hpp"
#include "graphics\load.h"

int main()
{
	Context context;
	context.init(807, 768);

	Texture tex = loadTexture("../../resources/textures/Capture2.png");

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } },
		{ { -1, 1,0,1 },{},{ 0,1 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };

	Geometry g = makeGeometry(vquad, 4, quadidx, 6);

	Framebuffer f = { 0, 800, 800 };

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 2) in vec2 texCoord;\n"
		"out vec2 vUV;\n"
		"void main ()\n"
		"{ gl_Position = position; vUV = texCoord; }\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec2 vUV;\n"
		"layout(location = 0) uniform sampler2D map;\n"
		"void main () { outColor = texture(map, vUV.xy); }\n";

	Shader s = makeShader(vsource, fsource);

	// RGB texture (3 channels), 2x1

	
	while (context.step())
	{
		clearFramebuffer(f);
		int loc = 0, tslot = 0;
		setUniforms(s, loc, tslot, tex);
		s0_draw(f, s, g);
	}
	freeGeometry(g);
	freeShader(s);
	freeTexture(tex);
	context.term();
	return 0;
}