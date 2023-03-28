
#include "GUI_Controlador.h"

#include <SDL2/SDL_image.h>
#include <cmath>

#include <iostream>
using namespace std;

GUI_Controlador::GUI_Controlador( Sistema* sistema ) {
	this->sistema = sistema;
}

void GUI_Controlador::inicializou() {			
	sistema->inicia();
}

void GUI_Controlador::finalizando() {
	sistema->finaliza();
}
		
void GUI_Controlador::janelaFechada() {
	
}



