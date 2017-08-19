#pragma once

struct Geometry;
struct Shader;
struct Framebuffer;

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g);


void clearFrameBuffer(const Framebuffer &f);

void setUniform(const Shader &shader, int location, float value);
void setUniform(const Shader &shader, int location, int value);
void setUniform(const Shader &shader, int location, double value);

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);