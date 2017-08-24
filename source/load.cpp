#include "graphics/load.h"
#include "graphics/RenderObjects.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb\stb_image.h"

#include<istream>
#include<fstream>
#include<iostream>

Texture loadTexture(const char *path)
{
	Texture retval = { 0 };

	stbi_set_flip_vertically_on_load(true);
	int w, h, c;
	unsigned char *pixels;
	pixels = stbi_load(path, &w, &h, &c, STBI_default);
	retval = makeTexture(w, h, c, pixels);
	stbi_image_free(pixels);

	return retval;
}

std::string fileToString(const char *path)
{
	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)),
					 std::istreambuf_iterator<char>());
	return str;
}

Shader loadShader(const char *vert_path, const char *frag_path)
{
	Shader retval = { 0 };
	
	unsigned char *v_source = fileToString(vert_path).c_str();
	unsigned char *f_source = fileToString(frag_path).c_str();
		
	return retval;
}

