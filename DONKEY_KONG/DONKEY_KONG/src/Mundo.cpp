#include "Mundo.h"
#include "ETSIDI.h"
#include "Globales.h"
#include "Interaccion.h"
#include "glut.h"

///////////////////////////////////DESTRUCTOR////////////////////////////
Mundo::~Mundo() {

}

////////////////////////////////////METODOS////////////////////////////
void Mundo::Inicializa() {
	//Posición del ojo
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;

	//Pared
	suelo.setLimites(-9, -4, 9, -3);
	hueco1.setLimites(-0.9, 1.85, 0.9, 2.15);
	hueco2.setLimites(-2, 9.75, 0, 10.15);
	//Jugador
	player.setPos(-8, -1.85);
	//Plataformas
	plataformas.Agregar(new Plataforma(0, -2, 18, 0.3, plataforma_18));
	plataformas.Agregar(new Plataforma(5, 2, 8, 0.3, plataforma_8_5));
	plataformas.Agregar(new Plataforma(-5, 2, 8, 0.3, plataforma_8_5));
	plataformas.Agregar(new Plataforma(0, 6, 18, 0.3, plataforma_18));
	plataformas.Agregar(new Plataforma(4.5, 10, 9, 0.3, plataforma_8_5));
	plataformas.Agregar(new Plataforma(-5.5, 10, 7, 0.3, plataforma_7));
	plataformas.Agregar(new Plataforma(0, 14, 18, 0.3, plataforma_18));
	//Escaleras
	escaleras.Agregar(new Escalera(6, 0, 0.5, 4));
	escaleras.Agregar(new Escalera(3, 4, 0.5, 4));
	escaleras.Agregar(new Escalera(-8, 4, 0.5, 4));
	escaleras.Agregar(new Escalera(-5, 8, 0.5, 4));
	escaleras.Agregar(new Escalera(1, 12, 0.5, 4));
	escaleras.Agregar(new Escalera(-3, 16, 0.5, 4));
}

void Mundo::Dibuja() {
	//Punto de vista
	gluLookAt(x_ojo, y_ojo, z_ojo,//posición del ojo
		0.0, y_ojo, 0.0, //Miramos al centro de la escena
		0.0, 1.0, 0.0); //orientación del mundo hacia arriba
	//Pared
	suelo.Dibuja();
	hueco1.Dibuja();
	//hueco2.Dibuja();
	//Jugador
	player.Dibuja();
	//Plataformas
	plataformas.Dibuja();
	//Escaleras
	escaleras.Dibuja();
}

void Mundo::Mueve() {
	
	player.Mueve(0.025f);
	//Jugador con pared
	Interaccion::reboteExterior(player, suelo);
	if (Interaccion::caidaHueco(player, hueco1) || Interaccion::caidaHueco(player, hueco2)) {
		player.setAcel(0.0, -20.0f);
		player.setFalling(true);
	}
	//Salto
	if (player.getSalto() || player.getFalling()) {
		if (plataformas.sobrePlataformas(player)!=0) {
			player.setAcel(0.0f, 0.0f);
			player.setVel(player.getVel().x, 0);
			player.setSalto(false);
			player.setFalling(false);
		}
	}
	
	//Jugador con escaleras
	if (escaleras.jugadorArriba(player)!=0) {
		player.setVel(0.0f, 0.0f);
		player.setUp(false);
	}
	
	if (escaleras.jugadorAbajo(player) != 0) {
		player.setVel(0.0f, 0.0f);
		player.setDown(false);
	}

	if (escaleras.detectaEscalerasSubir(player)!=0) {
		ETSIDI::play("sonidos/contactoPared.wav");
	}

	if (escaleras.detectaEscalerasBajar(player) != 0) {
		ETSIDI::play("sonidos/coin.wav");
	}
}

void Mundo::TeclaEspecial(unsigned char key) {

	switch (key) {
	case GLUT_KEY_RIGHT:
		player.setVel(5.0f, 0.0f);
		if (player.getUp() || player.getDown()) {
			player.setAcel(0.0f, -20.0f);
			player.setFalling(true);
		}
		break;

	case GLUT_KEY_LEFT:
		player.setVel(-5.0f, 0.0f);
		if (player.getUp() || player.getDown()) {
			player.setAcel(0.0f, -20.0f);
			player.setFalling(true);
		}
		break;

	case GLUT_KEY_UP:
		if(escaleras.detectaEscalerasSubir(player)!=0 && plataformas.sobrePlataformas(player)!=0){
			player.setVel(0.0f, 5.0f);
			player.setUp(true);
		}
		break;

	case GLUT_KEY_DOWN:
		if (escaleras.detectaEscalerasBajar(player) != 0 && plataformas.sobrePlataformas(player) != 0) {
			player.setVel(0.0f, -5.0f);
			player.setDown(true);
		}
		break;
	}
}

void Mundo::Tecla(unsigned char key) {

	switch (key) {
	case ' ':
		if (plataformas.sobrePlataformas(player)!=0) {
			player.setAcel(0, -15);
			player.setVel(player.getVel().x, 4.0f);
			player.setSalto(true);
		}
		break;
	}
}