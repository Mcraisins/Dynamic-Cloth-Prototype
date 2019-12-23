#include "Spring.h"
#include "iostream"
Spring::Spring(Mass* M1, Mass* M2, float ispringcon, float idampcon, float irestlen)
{
	m1 = M1; m2 = M2;
	springcon = ispringcon;
	restlen = irestlen;
	dampcon = idampcon;
}

Spring::~Spring()
{
}

void Spring::update()
{
	float len = glm::distance(m1->pos, m2->pos);
	float force = springcon * (len - restlen);
	force *= m1->mass;
	glm::vec3 norm = glm::normalize(m1->pos - m2->pos);
	m2->force += norm * force;
	m1->force += norm * -force;
	//m2->force += dampcon * (m1->vel - m2->vel);
	//m1->force += -dampcon * (m1->vel - m2->vel);
}