#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"
#include "glm\ext.hpp"
#include "graphics\load.h"

int main()
{
	Context context;
	context.init(900, 900);

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 } },
		{ {  1,-1,0,1 },{},{ 1,0 } },
		{ {  1, 1,0,1 },{},{ 1,1 } },
		{ { -1, 1,0,1 },{},{ 0,1 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };

	Geometry g = makeGeometry(vquad, 4, quadidx, 6);

	Geometry cube = loadGeometry("../../resources/models/cube.obj");
	
	Texture tex = loadTexture("../../resources/textures/Capture3.png");

	
	Shader scube = loadShader("../../resources/shaders/shaders/cube.vert",
							  "../../recources/shaders/shaders/cube.frag");

	Framebuffer screen = { 0, 900, 900 };

	//const char* vsource =
	//	"#version 450\n"
	//	"layout(location = 0) in vec4 position;\n"
	//	"layout(location = 2) in vec2 texCoord;\n"
	//	"out vec2 vUV;\n"
	//	"void main ()\n"
	//	"{ gl_Position = position; vUV = texCoord; }\n";

	//const char* fsource =
	//	"#version 450\n"
	//	"out vec4 outColor;\n"
	//	"in vec2 vUV;\n"
	//	"layout(location = 0) uniform sampler2D map;\n"
	//	"void main () { outColor = texture(map, vUV.xy); }\n";

	//Shader s = makeShader(vsource, fsource);

	// RGB texture (3 channels), 2x1

	
	while (context.step())
	{
		clearFramebuffer(screen);
		int loc = 0, tslot = 0;
		float time = context.getTime();

		//setUniforms(s, loc, tslot, tex, (int)(time*3) % 4 + frame*4, 4,4,x,y);

		glm::mat4 mod_cube = glm::rotate(time, glm::vec3(1, 1, 1));
		loc = 0; tslot = 0;
		setUniforms(scube, loc, tslot, mod_cube);
		s0_draw(screen,scube,cube);
	}
	freeGeometry(g);
	//freeShader(s);
	freeTexture(tex);
	context.term();
	return 0;
}