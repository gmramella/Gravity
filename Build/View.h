#pragma once
#include "Render.h"
class View
{
public:
	//Objeto para a classe que faz o desenho das formas de colis�o dos corpos r�gidos
	DebugDraw renderer;
	/**
	Chama as rotinas de desenho para cada fixture de um corpo r�gido, de acordo com o tipo da forma de colis�o dela
	*/
	void DrawFixture(b2Fixture* fixture, b2Color color);
	/**
	Para chamar a rotina de desenho das fixtures de um corpo
	*/
	void DrawBody(b2Body *b, b2Color color);
	/**
	Rotina de render (n�o � mais callback)
	*/
	void Render(b2World *world);
	/**
	Imprime todos os objetos  
	*/
	void PrintBodies(b2World *world);
};
