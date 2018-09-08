#include "Utils.h"

float32Pair Utils::Bhaskara(float32 a, float32 b, float32 c)
{
	float32Pair result;
	result.a = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
	result.b = (-b - sqrtf(b * b - 4 * a * c)) / (2 * a);
	return result;
}

float32 Utils::PolygonArea(b2Vec2* vertices, int size)
{
	float32 area = 0.0f;
	int i;
	for (i = 0; i < size - 1; i++)
	{
		area += (vertices[i].x * vertices[i + 1].y) - (vertices[i + 1].x * vertices[i].y);
	}
	return area / 2.0f;
}

float Utils::RandomInRange(float least, float most)
{
	return least + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (most - least)));
}