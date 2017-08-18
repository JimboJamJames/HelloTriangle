#pragma once

struct Geometry;
struct Shader;
struct Framebuffer;
struct Texture;

void s0_draw(const Framebuffer &f,
			 const Shader &s,
			 const Geometry &g);

void clearFramebuffer(const Framebuffer &fb);

void setUniform(const Shader &shader, int location, float value);
void setUniform(const Shader &shader, int location, int value);

void setUniform(const Shader &shader, int location, const Texture &value, int slot);