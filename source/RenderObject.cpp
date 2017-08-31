//this explains all the weird functions:
//http://docs.gl/
#define GLM_FORCE_SWIZZLE

#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "glincl.h"

#ifdef _DEBUG
#include <iostream>
#endif

//sets up things
Geometry makeGeometry(const Vertex * verts, size_t vsize, const unsigned * idxs, size_t isize)
{
	//Initializer List (constructor)
	Geometry retval = { 0,0,0,isize };


	//Declare openGL objects and acquire handles
	glGenBuffers(1, &retval.vbo);
	glGenBuffers(1, &retval.ibo);
	glGenVertexArrays(1, &retval.handle);

	//Scope variables
	glBindVertexArray(retval.handle); //ALL buffers bound after this will attach to this array
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo);				//array of vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo);		//array of indices

	//Initialize the buffers with our own data
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize * sizeof(unsigned), idxs, GL_STATIC_DRAW);


	//Describe memory layout
	//This one's for position
	glEnableVertexAttribArray(0); //Tells video card which attribute to use
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//This one's for color
	glEnableVertexAttribArray(1); //Tells video card which attribute to use
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);

	//This one's for texCoord
	glEnableVertexAttribArray(2); //Tells video card which attribute to use
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	// This one's for normals 4c2 so it jumps by 8 not 16
		glEnableVertexAttribArray(3); //Tells video card which attribute to use
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)40);

	// This one's for tangent
	glEnableVertexAttribArray(4); //Tells video card which attribute to use
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)56);

	// This one's for bitangent
	glEnableVertexAttribArray(5); //Tells video card which attribute to use
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)72);

	//unbind variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return retval;
}

//Basically a delete function
void freeGeometry(Geometry & g)
{
	glDeleteBuffers(1, &g.vbo);
	glDeleteBuffers(1, &g.ibo);
	glDeleteVertexArrays(1, &g.handle);
	g = { 0,0,0,0 };	//zero out geometry
}


//helper function \o/
glm::vec4 calcTangent(const Vertex &v0, const Vertex &v1, const Vertex &v2)
{
	//direction between vertices
	glm::vec4 p1 = v1.position - v0.position;
	glm::vec4 p2 = v2.position - v0.position;

	//direction for uvs
	glm::vec2 t1 = v1.UV - v0.UV;
	glm::vec2 t2 = v2.UV - v0.UV;


	//get average of some stuff??
	//it's math magic
	return glm::normalize((p1*t2.y - p2*t1.y) / (t1.x*t2.y - t1.y*t2.x));
	//uv.x will follow tangents
	//uv.y will follow bitengents
}

//#define GLM_FORCE_SWIZZLE
void solveTangents(Vertex * v, size_t vsize, const unsigned * idxs, size_t isize)
{
	//for every 3 vertices (every triangle)
	for (int i = 0; i < isize; i += 3)
	{
		//get the tanget of the three things
		glm::vec4 T = calcTangent(v[idxs[i]], v[idxs[i+1]], v[idxs[i+2]]);

		for (int j = 0; j < 3; j++)
			//get the middle angle (the NORMAL) of two other angles
			v[idxs[i + j]].tangent = glm::normalize(T + v[idxs[i + j]].tangent);
	}

	//CROSS PRODUCT WILL GIVE YOU THE Z AXIS IF YOU PUT IN THE X/Y AXIS.
	//this only works for vec3
	//we're getting the bitangent here
	for (int i = 0; i < vsize; i++)
		v[i].bitangent = glm::vec4(glm::cross(v[i].normal.xyz(), v[i].tangent.xyz()), 0);
}



Shader makeShader(const char * vertSource, const char * fragSource)
{
	Shader retval = {0};

	//create shader program and attach that to the shader variable
	retval.handle = glCreateProgram();
	//create local shader variables for linking.
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	//attach shaders to shader program
	glShaderSource(vs, 1, &vertSource, 0);
	glShaderSource(fs, 1, &fragSource, 0);

	//compile shaders
	glCompileShader(vs);

#ifdef _DEBUG
	GLint success = GL_FALSE;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(vs, length, 0, log);
		std::cerr << log << std::endl;
		assert(false && "Vertex failed to compile!");
		delete[] log;
		
	}
#endif // _DEBUG

	glCompileShader(fs);

#ifdef _DEBUG
	GLint success2 = GL_FALSE;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success2);
	if (success2 == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(fs, length, 0, log);
		std::cerr << log << std::endl;
		assert(false && "Fragment failed to compile!");
		delete[] log;
	}
#endif // _DEBUG

	//attach and link shaders to shader program
	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);

	glLinkProgram(retval.handle);

#ifdef _DEBUG
	GLint success3 = GL_FALSE;
	glGetProgramiv(retval.handle, GL_LINK_STATUS, &success3);
	if (success3 == GL_FALSE)
	{
		int length = 0;
		glGetProgramiv(retval.handle, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetProgramInfoLog(retval.handle, length, 0, log);
		std::cerr << log << std::endl;
		assert(false && "Program failed to compile!");
		delete[] log;
	}
#endif // _DEBUG


	//Once shaders have been linked they are no longer needed and are deleted.
	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}

//delete shader
void freeShader(Shader & s)
{
	glDeleteProgram(s.handle);
	s = { 0 };
}


Texture makeTexture(unsigned w, unsigned h, unsigned c, const unsigned char * pixels)
{
	Texture retval = { 0 };

	GLenum f = 0;
	switch (c)
	{
	case 1: f = GL_RED; break;
	case 2: f = GL_RG; break;
	case 3: f = GL_RGB; break;
	case 4: f = GL_RGBA; break;
	}

	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//nearest neighbor 

	//make texture
	glTexImage2D(GL_TEXTURE_2D, 0, f, w, h, 0, f, GL_UNSIGNED_BYTE, pixels);

	//unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;
}

void freeTexture(Texture & t)
{
	glDeleteTextures(1, &t.handle);
	t = { 0 };
}
