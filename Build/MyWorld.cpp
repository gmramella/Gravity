#include "MyWorld.h"

MyWorld::MyWorld(Globals globals)
{
	movement = b2Vec2(0, 0);
	gravity = b2Vec2(0, 0);
	boost = false;
	xPos = 0;
	yPos = 0;
	this->globals = globals;
}

MyWorld::~MyWorld()
{
}

void MyWorld::CreateBodies()
{
	float32 earthMass = 5.972 * 1e24;
	float32 earthRadius = 6371 * 1e3;
	planetData *ed = new planetData(earthMass, earthRadius);
	b2Body *earth = CreateCircle(b2Vec2(0, 0), (earthRadius / 50000), ed->density, 1, 0, b2_staticBody);
	earth->SetUserData(ed);
	bodies.push_back(earth);

	float32 moonMass = 7.34767309 * 1e22;
	float32 moonRadius = 1737 * 1e3;
	planetData *md = new planetData(moonMass, moonRadius);
	b2Body *moon = CreateCircle(b2Vec2(768.8, 0), (moonRadius / 50000), md->density, 1, 0, b2_staticBody);
	moon->SetUserData(md);
	bodies.push_back(moon);

	float32 mul = 384400000 / 768.8;
	float32 distEM = sqrtf((moon->GetPosition().x - earth->GetPosition().x) * (moon->GetPosition().x - earth->GetPosition().x) + (moon->GetPosition().y * earth->GetPosition().y) * (moon->GetPosition().y * earth->GetPosition().y));
	float32 dm = (distEM * mul) / (sqrtf(earthMass / moonMass) + 1);
	float32 de = moon->GetPosition().x * mul - dm;
	printf("Eq %lf %lf\r\n", de / mul, dm / mul);

	//float32 bhask = -38380894.51880 / mul;
	//moon->GetPosition().x + bhask
	//printf("%f\r\n", bhask);
	//float32 bhask = 47957683.1723059971329063366381 / mul;
	//float32 bhask = bhaskara(((earthMass / moonMass) - 1), (2 * 384400000), (-384400000 * 384400000)) / mul;

	float32 shipMass = 2030 * 1000;
	float32 shipHeight = 56.1;
	float32 shipRadius = 4.35;
	float32 shipThrust = 30.5 * 1e6;
	shipData *sd = new shipData(shipMass, shipHeight, shipRadius, shipThrust);
	b2Body *ship = CreateCircle(b2Vec2(150, 0), shipRadius, sd->density, 1, 0, b2_dynamicBody);
	ship->SetUserData(sd);
	bodies.push_back(ship);

	world->SetGravity(gravity);
}

b2Body *MyWorld::CreateCircle(b2Vec2 center, float32 rad, float32 m, float32 f, float32 r, b2BodyType bt)
{
	b2Body *b;

	b2BodyDef bd;
	bd.position.Set(center.x, center.y);
	bd.type = bt;

	b2CircleShape cs;
	cs.m_p.Set(0, 0);
	cs.m_radius = rad;

	b2FixtureDef fd;
	fd.shape = &cs;
	fd.density = m / (4 * b2_pi * rad * rad * rad / 3);
	fd.friction = f;
	fd.restitution = r;

	b = world->CreateBody(&bd);
	b->CreateFixture(&fd);

	return b;
}

b2Body *MyWorld::CreateHouses(b2Vec2 center, float32 m, float32 f, float32 r, b2BodyType bt)
{
	b2Body *b;

	b2BodyDef bd;
	bd.position.Set(center.x, center.y);
	bd.type = bt;
	b = world->CreateBody(&bd);

	b2Vec2 vertices1[5];
	vertices1[0].Set(center.x - 20, center.y + 10);
	vertices1[1].Set(center.x - 20, center.y + 0);
	vertices1[2].Set(center.x + 0, center.y + 0);
	vertices1[3].Set(center.x + 0, center.y + 10);
	vertices1[4].Set(center.x - 10, center.y + 15);

	b2Vec2 vertices2[5];
	vertices2[0].Set(center.x + 0, center.y + 10);
	vertices2[1].Set(center.x + 0, center.y + 0);
	vertices2[2].Set(center.x + 20, center.y + 0);
	vertices2[3].Set(center.x + 20, center.y + 10);
	vertices2[4].Set(center.x + 10, center.y + 15);

	float32 area = Utils::PolygonArea(vertices1, (sizeof(vertices1) / sizeof(b2Vec2))) + Utils::PolygonArea(vertices2, (sizeof(vertices2) / sizeof(b2Vec2)));

	b2PolygonShape ps;
	b2FixtureDef fd;
	fd.density = m / (area * 1);
	fd.friction = f;
	fd.restitution = r;

	ps.Set(vertices1, (sizeof(vertices1) / sizeof(b2Vec2)));
	fd.shape = &ps;
	b->CreateFixture(&fd);

	ps.Set(vertices2, (sizeof(vertices2) / sizeof(b2Vec2)));
	fd.shape = &ps;
	b->CreateFixture(&fd);

	return b;
}

b2Body *MyWorld::CreateLine(b2Vec2 center, b2Vec2 left, b2Vec2 right, float32 m, float32 f, float32 r, b2BodyType bt)
{
	b2Body* b;

	b2BodyDef bd;

	bd.position.Set(center.x, center.y);
	bd.type = bt;

	b2EdgeShape es;
	es.Set(left, right);

	float32 w = right.x - left.x; if (w == 0) w = 1 / INFINITY;
	float32 h = right.y - left.y; if (h == 0) h = 1 / INFINITY;

	b2FixtureDef fd;
	fd.shape = &es;
	fd.density = m / (w * h * 1);
	fd.friction = f;
	fd.restitution = r;

	b = world->CreateBody(&bd);
	b->CreateFixture(&fd);

	return b;
}

b2Body *MyWorld::CreateRectangle(b2Vec2 center, float32 w, float32 h, float32 m, float32 f, float32 r, b2BodyType bt)
{
	b2Body *b;

	b2BodyDef bd;
	bd.position.Set(center.x, center.y);
	bd.type = bt;

	b2PolygonShape ps;
	ps.SetAsBox(w / 2, h / 2);

	b2FixtureDef fd;
	fd.shape = &ps;
	fd.density = m / (w * h * 1);
	fd.friction = f;
	fd.restitution = r;

	b = world->CreateBody(&bd);
	b->CreateFixture(&fd);

	return b;
}

void MyWorld::Delete()
{
	std::vector<b2Body*> toDelete;
	b2Body *temp;
	for (temp = world->GetBodyList(); temp; temp = temp->GetNext())
	{
		if (temp->GetFixtureList()->GetType() == b2Shape::e_polygon)
		{
			if (temp->GetPosition().y <= -50)
			{
				toDelete.push_back(temp);
			}
		}
	}
	for (std::vector<b2Body*>::iterator it = toDelete.begin(); it != toDelete.end(); ++it) {
		b2Body* dyingBox = *it;
		world->DestroyBody(dyingBox);
	}
	toDelete.clear();
}

void MyWorld::DeleteBodies()
{
	std::vector<b2Body*> toDelete;
	b2Body *temp;
	for (temp = world->GetBodyList(); temp; temp = temp->GetNext())
	{
		toDelete.push_back(temp);
	}
	for (std::vector<b2Body*>::iterator it = toDelete.begin(); it != toDelete.end(); ++it) {
		world->DestroyBody(*it);
	}
	toDelete.clear();
}

void MyWorld::InitBox2D()
{
	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);
	velocityIterations = 10;
	positionIterations = 8;
	timeStep = 1.0f / 60.0f;
	world->SetAllowSleeping(false);
}

void MyWorld::RunBox2D()
{
	planetData *ed = (planetData*)bodies[0]->GetUserData();
	planetData *md = (planetData*)(bodies[1])->GetUserData();
	shipData *sd = (shipData*)(bodies[2])->GetUserData();

	b2Vec2 earthPosition = 50000 * bodies[0]->GetPosition();
	float32 earthRadius = 50000 * bodies[0]->GetFixtureList()->GetShape()->m_radius;
	b2Vec2 moonPosition = 50000 * bodies[1]->GetPosition();
	float32 moonRadius = 50000 * bodies[1]->GetFixtureList()->GetShape()->m_radius;
	b2Vec2 shipPosition = 50000 * bodies[2]->GetPosition();
	float32 shipRadius = bodies[2]->GetFixtureList()->GetShape()->m_radius;
	b2Vec2 mousePosition = 50000 * b2Vec2(-globals.width / 2 + xPos, globals.height / 2 - yPos);

	float32 eM = ed->mass;
	float32 er = ed->radius;
	float32 distanceToEarth = sqrtf(((earthPosition.x - shipPosition.x) * (earthPosition.x - shipPosition.x)) + ((earthPosition.y - shipPosition.y) * (earthPosition.y - shipPosition.y)));
	float32 edist = distanceToEarth - earthRadius;
	float32 eh = distanceToEarth - earthRadius > 50000 * shipRadius ? edist : 0;
	float32 eg = G * eM / ((er + eh) * (er + eh));

	float32 mM = md->mass;
	float32 mr = md->radius;
	float32 distanceToMoon = sqrtf(((moonPosition.x - shipPosition.x) * (moonPosition.x - shipPosition.x)) + ((moonPosition.y - shipPosition.y) * (moonPosition.y - shipPosition.y)));
	float32 mdist = distanceToMoon - moonRadius;
	float32 mh = distanceToMoon - moonRadius > 50000 * shipRadius ? mdist : 0;
	float32 mg = G * mM / ((mr + mh) * (mr + mh));

	////Fuel (lost when used) http://www.braeunig.us/space/propuls.htm
	//float32 thrust = boost * (sd->rocket.volume > 0) * sd->rocket.density * sd->rocket.area * sd->rocket.velocity * sd->rocket.velocity;
	//float32 m = sd->mass + (sd->rocket.density * sd->rocket.volume);
	//sd->rocket.volume -= boost * sd->rocket.velocity;
	//globals.bodies[2]->SetUserData(sd);
	//No fuel
	float32 thrust = boost * 30.5 * 1e6;
	float32 sm = sd->mass;
	float32 sa = thrust / sm;

	float32 distanceToMouse = sqrtf(((mousePosition.x - shipPosition.x) * (mousePosition.x - shipPosition.x)) + ((mousePosition.y - shipPosition.y) * (mousePosition.y - shipPosition.y)));

	b2Vec2 directionToEarth = b2Vec2((earthPosition.x - shipPosition.x) / distanceToEarth, (earthPosition.y - shipPosition.y) / distanceToEarth);
	b2Vec2 directionToMoon = b2Vec2((moonPosition.x - shipPosition.x) / distanceToMoon, (moonPosition.y - shipPosition.y) / distanceToMoon);
	b2Vec2 directionToMouse = b2Vec2((mousePosition.x - shipPosition.x) / distanceToMouse, (mousePosition.y - shipPosition.y) / distanceToMouse);

	float32 egangle = atan2f(directionToEarth.y, directionToEarth.x);
	float32 mgangle = atan2f(directionToMoon.y, directionToMoon.x);
	float32 saangle = atan2f(directionToMouse.y, directionToMouse.x);
	if (movement.x != 0 || movement.y != 0)
	{
		sa = 30.5 * 1e6 / sm;
		saangle = atan2f(movement.y, movement.x);
	}

	b2Vec2 res = b2Vec2(eg * cosf(egangle) + mg * cosf(mgangle) + sa * cosf(saangle), eg * sinf(egangle) + mg * sinf(mgangle) + sa * sinf(saangle));
	float32 resg = sqrtf(res.x * res.x + res.y * res.y);
	if (resg == 0) resg = 1;
	b2Vec2 resdir = b2Vec2(res.x / resg, res.y / resg);
	//printf("move %f %f sang %f resg %f resang %f\r\n", movement.x, movement.y, saangle * 180 / b2_pi, resg, atan2f(res.y, res.x) * 180 / b2_pi);
	world->SetGravity(res);

	DebugDraw dd;
	b2Vec2 p1 = b2Vec2(bodies[2]->GetPosition().x + bodies[2]->GetFixtureList()->GetShape()->m_radius * resdir.x, bodies[2]->GetPosition().y + bodies[2]->GetFixtureList()->GetShape()->m_radius * resdir.y);
	b2Vec2 p2 = b2Vec2(p1.x + 5 * resdir.x, p1.y + 5 * resdir.y);
	dd.DrawSegment(p1, p2, b2Color(0, 0, 0));

	/*printf("acc e %f m %f s %f\r\n", eg, mg, sa);
	printf("g %f (%f %f)\r\n", resg, resdir.x, resdir.y);
	printf("ang e %f m %f s %f\r\n", egangle * RADTODEG, mgangle * RADTODEG, saangle * RADTODEG);
	printf("E pos (%.0f %.0f) rad %.0f dir (%f %f) dist %.0f\r\n", earthPosition.x, earthPosition.y, earthRadius, directionToEarth.x, directionToEarth.y, distanceToEarth);
	printf("E m %.0f r %.0f edist %.0f eh %.0f\r\n", eM, er, edist, eh);
	printf("M pos (%.0f %.0f) rad %.0f dir (%f %f) dist %.0f\r\n", moonPosition.x, moonPosition.y, moonRadius, directionToMoon.x, directionToMoon.y, distanceToMoon);
	printf("M m %.0f r %.0f mdist %.0f mh %.0f\r\n", mM, mr, mdist, mh);
	printf("S pos (%.0f %.0f) rad %.0f\r\n", shipPosition.x, shipPosition.y, shipRadius);
	printf("S m %.0f\r\n", sm);
	printf("C pos (%.0f %.0f) dir (%f %f)\r\n", mousePosition.x, mousePosition.y, directionToMouse.x, directionToMouse.y);
	printf("\r\n");*/

	world->Step(timeStep, velocityIterations, positionIterations);
	world->ClearForces();
}
