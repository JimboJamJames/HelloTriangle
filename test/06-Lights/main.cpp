#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"
#include "graphics\Load.h"

#include "glm\ext.hpp"

//we gucci boyz

int main()
{
	Context context;
	context.init(800, 800);

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry floor_geo = makeGeometry(vquad, 4, quadidx, 6);
	glm::mat4 floor_model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0))
		* glm::scale(glm::vec3(5, 5, 1));

	// Buffers
	Framebuffer fb_shadow = makeFramebuffer(2048, 2048, 0, true, 0, 0);
	Framebuffer screen = { 0,1280, 720 };


	// Light
	glm::vec3 light_dir = glm::normalize(glm::vec3(.8, -1, -1));
	glm::mat4 light_proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view = glm::lookAt(-light_dir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


	// Shaders
	Shader shdr_shadow = loadShader("../../resources/shaders/shadow.vert",
		"../../resources/shaders/shadow.frag");
	Shader shdr_direct = loadShader("../../resources/shaders/direct.vert",
		"../../resources/shaders/direct.frag");

	// Shadow Pass
	setFlags(RenderFlag::DEPTH);
	clearFramebuffer(fb_shadow, false, true);

	// SoulSpear
	Geometry  ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model; // = glm::rotate(time, glm::vec3(0,1,0)) // on update.

						// Cube
	Geometry cube_geo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 cube_model = glm::translate(glm::vec3(2, 1, -1));
	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Shader lambert = loadShader("../../resources/shaders/lambert.vert",
		"../../resources/shaders/lambert.frag");

	Texture soil_diffuse = loadTexture("../../resources/textures/sand.jpg");


	int loc = 0, slot = 0;
	setUniforms(shdr_shadow, loc, slot, light_proj, light_view, floor_model);
	s0_draw(fb_shadow, shdr_shadow, floor_geo);

	glm::vec3 target_pos = glm::vec3(0, 0, 0);

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);


	glm::vec4 lightColor = glm::vec4(1, .5, 1, 1);
	glm::vec3 lightPos = glm::vec3(3, 2, 3);

	
	float lightIntensity = 8.0f;

	while (context.step())
	{

		float time = (float)context.getTime();

		glm::mat4 go_model = glm::rotate(time, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 modq = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0)) * 
						 glm::scale(glm::vec3(5, 5, 1));


	
	}

	context.term();

	return 0;
}