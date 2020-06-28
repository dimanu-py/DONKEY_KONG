#include "Mundo.h"
#include "ETSIDI.h"
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
	//Jugador
	player.setPos(-8,-1.85);
	//Plataformas
	plataforma1.Inicializa(0, -2, 18, 0.3);
	plataforma2.Inicializa(4.75, 2, 8.5, 0.3);
	plataforma3.Inicializa(-4.75, 2, 8.5, 0.3);
	plataforma4.Inicializa(0, 6, 18, 0.3);
	plataforma5.Inicializa(3.5, 10, 11, 0.3);
	plataforma6.Inicializa(-4.75, 10, 7, 0.3);
	plataforma7.Inicializa(0, 14, 18, 0.3);
	//Escaleras
	escalera1.Inicializa(6.0, 0, 0.5, 4);
	escalera2.Inicializa(3, 4, 0.5, 4);
	escalera3.Inicializa(-8, 4, 0.5, 4);
	escalera4.Inicializa(-5, 8, 0.5, 4);
	escalera5.Inicializa(1, 12, 0.5, 4);
	escalera6.Inicializa(-3, 16, 0.5, 4);
}

void Mundo::Dibuja() {
	//Punto de vista
	gluLookAt(x_ojo, y_ojo, z_ojo,//posición del ojo
		0.0, y_ojo, 0.0, //Miramos al centro de la escena
		0.0, 1.0, 0.0); //orientación del mundo hacia arriba
	//Pared
	suelo.Dibuja();
	//Jugador
	player.Dibuja();
	//Plataformas
	plataforma1.Dibuja();
	plataforma2.Dibuja();
	plataforma3.Dibuja();
	plataforma4.Dibuja();
	plataforma5.Dibuja();
	plataforma6.Dibuja();
	plataforma7.Dibuja();
	//Escaleras
	escalera1.Dibuja();
	escalera2.Dibuja();
	escalera3.Dibuja();
	escalera4.Dibuja();
	escalera5.Dibuja();
	escalera6.Dibuja();
}

void Mundo::Mueve() {
	player.Desplaza(0.025f);

	//Jugador con pared
	player.limitePared(suelo);
	//Salto
	if (player.getSalto()) {
		if (player.sobrePlataforma(plataforma1)) {
			player.setAcel(0.0f, 0.0f);
			player.setVel(player.getVel().x, 0);
		}
	}
	//Jugador con escaleras
	/*if (player.limiteEscalera(escalera1))
		player.setPos(player.getPos().x, plataforma2.getLimite2().y);

	if (player.limiteEscalera(escalera2))
		player.setPos(player.getPos().x, plataforma4.getLimite2().y);*/

	
	if (player.detectaEscalera(escalera1)|| player.detectaEscalera(escalera2)) {
		ETSIDI::play("sonidos/contactoPared.wav");
	}
}

void Mundo::TeclaEspecial(unsigned char key) {

	switch (key) {
	case GLUT_KEY_RIGHT:
		player.setVel(5.0f, 0.0f);
		break;

	case GLUT_KEY_LEFT:
		player.setVel(-5.0f, 0.0f);
		break;

	case GLUT_KEY_UP:
		/*if (player.detectaEscalera(escalera1) || player.detectaEscalera(escalera2)) 
			player.setVel(0.0f, 5.0f);*/
		break;

	case GLUT_KEY_DOWN:
		/*if (player.detectaEscalera(escalera1) || player.detectaEscalera(escalera2))
			player.setVel(0.0f, -5.0f);*/
		break;
	}
}

void Mundo::Tecla(unsigned char key) {

	switch (key) {
	case ' ':
		if (player.sobrePlataforma(plataforma1)) {
			player.setVel(player.getVel().x, 4.0f);
			player.setAcel(0, -15);
			player.setSalto(true);
		}
		break;
	}
}