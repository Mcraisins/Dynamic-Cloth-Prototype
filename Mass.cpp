#include "Mass.h"

Mass::Mass(float x, float y, float z, float imass, float idampcon, bool ifixed)
{
	mass = imass;
	pos = glm::vec3(x,y,z);
	fixed = ifixed;
	
	prevpos = pos;
}

Mass::~Mass()
{
}

void Mass::update(float delta, bool verlet)
{
	if(fixed) return;

	glm::vec3 accel = force / mass;
	if(verlet)
	{
		glm::vec3 temp = pos;
		vel = (pos - prevpos) * delta;
		pos += (pos - prevpos) * dampcon + accel * delta * delta;
		prevpos = temp;
	} else {
		vel = vel * dampcon + accel * delta;
		pos += vel * delta;
	}
	force = glm::vec3();
}