#include "Mundo.h"
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

	//Inicializamos jugador
	player.setPos(-10,0);
	//Inicializamos plataforma
	plataforma1.setSize(10, 0.25);
	plataforma1.setPos(9,-2);

}

void Mundo::Dibuja() {
	//Punto de vista
	gluLookAt(x_ojo, y_ojo, z_ojo,//posición del ojo
		0.0, y_ojo, 0.0, //Miramos al centro de la escena
		0.0, 1.0, 0.0); //orientación del mundo hacia arriba

	player.Dibuja();
	plataforma1.Dibuja();
}

void Mundo::Mueve() {
	player.Mueve(0.025f);
}

void Mundo::TeclaEspecial(unsigned char key) {

	switch (key) {
		case GLUT_KEY_RIGHT:
			player.setVel(5.0f, 0.0f);
			break;
		case GLUT_KEY_LEFT:
			player.setVel(-5.0f, 0.0f);
			break;
	}
}