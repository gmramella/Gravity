#pragma once
#include "Build/Globals.h"
#include "Build/Physics.h"
#include "Build/Utils.h"
#include <vector>

struct planetData {
	float32 mass;
	float32 radius;
	float32 volume;
	float32 density;
	planetData(float32 mass, float32 radius)
	{
		this->mass = mass;
		this->radius = radius;
		this->volume = (4.0f / 3.0f) * b2_pi * radius * radius * radius;
		this->density = mass / volume;
	}
};

struct rocketData {
	float32 volume;
	float32 density;
	float32 area;
	float32 velocity;
	rocketData(float32 volume, float32 density, float32 radius, float32 velocity)
	{
		this->volume = volume;
		this->density = density;
		this->area = b2_pi * radius * radius;
		this->velocity = velocity;
	}
};

struct shipData {
	float32 mass;
	float32 radius;
	float32 volume;
	float32 density;
	rocketData rocket = rocketData(1e6, 70850, 100, 20);
	shipData(float32 mass, float32 height, float32 radius, float32 thrust)
	{
		this->mass = mass;
		this->radius = radius;
		this->volume = height * b2_pi * radius * radius;
		this->density = mass / volume;
	}
};

class MyWorld
{
public:
	b2Vec2 movement;
	b2Vec2 gravity;
	bool boost;
	float xPos, yPos;
	float32 timeStep;
	int32 velocityIterations;
	int32 positionIterations;

	Globals globals;
	b2World *world;
	std::vector<b2Body*> bodies;

	MyWorld(Globals globals);
	~MyWorld();

	/**
	Cria corpos iniciais do cenário
	*/
	void CreateBodies();
	/**
	Cria circulo
	*/
	b2Body *CreateCircle(b2Vec2 center = b2Vec2(0, 0), float32 rad = 1, float32 m = 1, float32 f = 0.5, float32 r = 0.5, b2BodyType bt = b2_dynamicBody);
	/**
	Cria casa (exemplo de corpo com 2 fixtures)
	*/
	b2Body *CreateHouses(b2Vec2 center = b2Vec2(0, 0), float32 m = 1000, float32 f = 1, float32 r = 1, b2BodyType bt = b2_staticBody);
	/**
	Cria linha
	*/
	b2Body *CreateLine(b2Vec2 center = b2Vec2(0, -39.5), b2Vec2 left = b2Vec2(-39.5, 0), b2Vec2 right = b2Vec2(39.5, 0), float32 m = 2, float32 f = 0.5, float32 r = 0.5, b2BodyType bt = b2_staticBody);
	/**
	Cria retangulo
	*/
	b2Body *CreateRectangle(b2Vec2 center = b2Vec2(0, 0), float32 w = 1, float32 h = 1, float32 m = 1, float32 f = 0.5, float32 r = 0.5, b2BodyType bt = b2_dynamicBody);
	/**
	Remove caixas que saem de cena
	*/
	void Delete();
	/**
	Remove todos corpos do cenário
	*/
	void DeleteBodies();
	/**
	Função de inicialização da Box2D
	*/
	void InitBox2D();
	/**
	Função de Execução da Simulação
	*/
	void RunBox2D();
};