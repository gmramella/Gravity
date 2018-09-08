#pragma once
#include "Math.h"

#define G (6.67408 * 1e-11)

#define massMercury (330.2 * 1e24)
#define radiusMercury (2439.7 * 1e3)
#define distanceMercury (57.9 * 1e9)

#define massVenus (4868.5 * 1e24)
#define radiusVenus (6051.8 * 1e3)
#define distanceVenus (108.2 * 1e9)

#define massEarth (5973.6 * 1e24)
#define radiusEarth (6371 * 1e3)
#define distanceEarth (149.6 * 1e9)

#define massMars (641.85 * 1e24)
#define radiusMars (3389.5 * 1e3)
#define distanceMars (227.9 * 1e9)

#define massJupiter (1898600 * 1e24)
#define radiusJupiter (69911 * 1e3)
#define distanceJupiter (778.3 * 1e9)

#define massSaturn (568460 * 1e24)
#define radiusSaturn (58232 * 1e3)
#define distanceSaturn (1427 * 1e9)

#define massUranus (86832 * 1e24)
#define radiusUranus (25362 * 1e3)
#define distanceUranus (2871 * 1e9)

#define massNeptune (102430 * 1e24)
#define radiusNeptune (24622 * 1e3)
#define distanceNeptune (4497.1 * 1e9)

#define massPluto (13.105 * 1e24)
#define radiusPluto (1186 * 1e3)
#define distancePluto (5913 * 1e9)

class Physics
{
public:
	/**
	Retorna velocidade orbital de planeta
	*/
	float OrbitalSpeed(float M, float r);
};

