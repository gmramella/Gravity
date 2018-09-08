#include "Physics.h"

float Physics::OrbitalSpeed(float M, float r)
{
	return sqrt(G * M / r);
}