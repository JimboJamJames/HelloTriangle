#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "glm\glm.hpp"

#include "genShape.h"

Geometry makeNGon(size_t N, float r)
{
	unsigned vsize = N+1;
	unsigned isize = N*3;
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	// circle = 360
	// angle of each tirangle = 360/N
	float a = (2*3.14159265359) / N;

	verts[0] = { {0,0,0,1},{1,1,1,1} };

	for (int i = 0; i < N; ++i)
	{
		float x = sin(i*a)*r; //angle to vector
		float y = cos(i*a)*r; 

		verts[i+1] = { {x,y,0,1},{x,y,0,1} };

		idxs[i * 3 + 0] = N;
		idxs[i * 3 + 1] = i;
		idxs[i * 3 + 2] = (i+1)%N;
	}

	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;

	return ret;
}

Geometry makeCheckerboard(int dim, int size)
{
	unsigned vdim = dim + 1;
	unsigned vsize = (dim+1)*(dim+1);
	unsigned isize = 3 * 2 * dim * dim;
	Vertex   *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	float step = size / dim;
	float offset = size / 2;
	int l = 0;
	for (int i = 0; i < vsize; ++i)
	{
		float x = (i & vdim)*step - offset; //collumn
		float y = (i / vdim)*step - offset; //rows


		verts[i].position = { x,y,0,1 };
		verts[i].color    = { rand() / (float)RAND_MAX, 
							  rand() / (float)RAND_MAX,	
							  rand() / (float)RAND_MAX, 1
							};

		if (i == 1 && dim > 1 ||	  //special case
			i % vdim != 1 &&	  //right case
			i / vdim != vdim - 1&&
			l < isize) // bottom case
		{
			idxs[l++] = i;
			idxs[l++] = i + 1;
			idxs[l++] = i + vdim;

			idxs[l++] = i + 1;
			idxs[l++] = i + vdim;
			idxs[l++] = i + vdim + 1;
		}
			
	}

	for (int i = 0; i < dim+1; ++i)
	{
		float y = i * step;

		for (int j = 0; j < dim+1; ++j)
		{
			float x = j * step;
		}
	}

	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;

	return ret;
}