#pragma once

#include "Mass.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	

class Spring
{
public:
	Spring(Mass*, Mass*, float, float, float);
	~Spring();
	void update();
public:
	Mass *m1, *m2;
	float springcon;
	float dampcon;
	float restlen;
};

