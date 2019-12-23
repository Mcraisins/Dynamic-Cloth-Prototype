#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Object.h"
#include "Spring.h"
#include "Mass.h"

class Cloth : public Object
{
public:
	Cloth();
	~Cloth() {};
	void build();
	void update(float);

public:
	glm::vec3 startpos;
	int width, height;
	float spacing, springcon, dampcon;
	std::vector<Mass> masses;
	std::vector<Spring> springs;
	float gravity;
	std::vector<int> fixed;
	bool verlet;
	float mass;

private:
	enum Dir { UR, UP, UL, CR, CL, DR, DW, DL };
	bool built = false;
	int To(int i, Dir d);
};
