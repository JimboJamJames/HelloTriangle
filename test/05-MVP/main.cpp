#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"
#include "glm\ext.hpp"
#include "graphics\load.h"

int main()
{
	Context context;
	context.init(800, 900);

	Vertex vquad[] = {
		{ { -.1,-.1,0,1 },{},{ 0,0 } },
		{ { .1,-.1,0,1 },{},{ 1,0 } },
		{ { .1, .1,0,1 },{},{ 1,1 } },
		{ { -.1,.1,0,1 },{},{ 0,1 } } };

	unsigned quadidx[] = { 0,1,3, 1,2,3 };

	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	//Geometry cube = loadGeometry("../../resources/models/cube.obj");

	//Texture tex = loadTexture("../../resources/textures/Capture2.png");


	//Shader scube = loadShader("../../resources/shaders/shaders/cube.vert",
	//	"../../recources/shaders/shaders/cube.frag");
	

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Shader mvplite = loadShader("../../resources/shaders/shaders/mvplite.vert",
								"../../resources/shaders/shaders/mvplite.frag");

	Framebuffer screen = { 0, 800, 900 };

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
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 900.f, .01f, 100.f);
	glm::mat4 go_model;

	setFlags(RenderFlag::DEPTH);
	while (context.step())
	{

		int loc = 0, tslot = 0;
		float time = (float)context.getTime();

		//setUniforms(s, loc, tslot, tex, (int)(time*3) % 4 + frame*4, 4,4,x,y);

	
		clearFramebuffer(screen);
		setUniforms(mvplite, loc, tslot, cam_proj, cam_view, go_model, ss_diffuse);
		s0_draw(screen, mvplite, ss_geo);

	}
	freeGeometry(ss_geo);
	freeShader(mvplite);
	freeTexture(ss_diffuse);
	context.term();
	return 0;
}