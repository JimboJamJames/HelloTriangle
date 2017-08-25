#pragma once

#include "..\include\glm\glm.hpp"

struct Vertex
{
	glm::vec4 position; // 
	glm::vec4 color;
	glm::vec2 UV;
	glm::vec4 normal;
	glm::vec2 texCoord;
};