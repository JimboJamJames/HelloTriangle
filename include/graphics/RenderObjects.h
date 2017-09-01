#pragma once

#include "glm\glm.hpp"

struct Vertex;

struct Geometry
{
	/*vertex array object,
	*vertex buffer object,
	*index buffer object,
	*# of indices that make up the model
	*/

	unsigned handle, vbo, ibo, size;
};

Geometry makeGeometry(const Vertex *verts, size_t vsize, const unsigned *idxs, size_t isize);
void freeGeometry(Geometry &g);


void solveTangents(Vertex *v, size_t vsize, const unsigned *idxs, size_t isize);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vertSource, const char *fragSource);
void freeShader(Shader &s);


struct Framebuffer
{
	unsigned handle, width, height;
};


struct Texture
{
	unsigned handle;
};


//RGBA = 4 channels
/*
*w = width
*h = height
*c = channels
*/
Texture makeTexture(unsigned w, unsigned h, unsigned c, const unsigned char *pixels);
void freeTexture(Texture &t);