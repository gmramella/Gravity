#pragma once
#include "Build\Render.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class float32Pair
{
public:
	float32 a;
	float32 b;
};

class Utils
{
public:
	/**
	Retorna (-b +- sqrt(delta))/2a
	*/
	static float32Pair Bhaskara(float32 a, float32 b, float32 c);
	/**
	Calcula área de um polígono CONVEXO
	*/
	static float32 PolygonArea(b2Vec2* vertices, int size);
	/**
	Retorna um float pseudoaleatório no intervalo [least, most]
	*/
	static float RandomInRange(float least, float most);
};