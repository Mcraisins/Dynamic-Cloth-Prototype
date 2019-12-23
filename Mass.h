#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	

class Mass
{
public:
	Mass(float, float, float, float, float, bool);
	~Mass();
	void update(float delta, bool);

public:
	float mass, dampcon;
	glm::vec3 pos, prevpos;
	glm::vec3 vel;
	glm::vec3 force;
	bool fixed;
};

