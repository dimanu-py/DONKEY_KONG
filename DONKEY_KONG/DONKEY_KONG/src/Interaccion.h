#pragma once

#include "Jugador.h"
#include "Plataforma.h"
#include "Pared.h"
#include "Escalera.h"

class Interaccion{
public:
	Interaccion();
	virtual ~Interaccion();
	static void reboteExterior(Jugador& jugador, Pared pared);
	static bool sobrePlataforma(Jugador& jugador, Plataforma plataforma);
	static bool detectaEscalera(Jugador& jugador, Escalera escalera);
	static bool arribaEscalera(Jugador& jugador, Escalera escalera);

	//static bool comprobarAltura(Jugador& jugador, Plataforma plataforma);
};
