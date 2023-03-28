
#ifndef GUI_CONTROLADOR_H
#define GUI_CONTROLADOR_H

#include "../sistema.h"
#include "../gui/GUI_listener.h"

class Sistema;

class GUI_Controlador : public GUI_Listener {
	
	private:
		Sistema* sistema;
								
	public:
		GUI_Controlador( Sistema* sistema );

		void inicializou();
		void finalizando();
		
		void janelaFechada();
};

#endif
