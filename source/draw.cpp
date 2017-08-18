#include "graphics\draw.h"
#include "graphics\RenderObjects.h"
#include "glinc.h"

void s0_draw(const Framebuffer &f,
			 const Shader &s,
			 const Geometry &g)
{
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);

	glViewport(0, 0, f.width, f.height);

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	glBindVertexArray(0);
}