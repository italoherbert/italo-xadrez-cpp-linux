
#ifndef ABERTURA_GRAFICO_CONTROLADOR_H
#define ABERTURA_GRAFICO_CONTROLADOR_H

#include "../sistema.h"

class Sistema;

class AberturaGraficoControlador : public AberturaGraficoListener {
	
	private:
		Sistema* sistema;

	public:		
		AberturaGraficoControlador( Sistema* sistema );
		virtual ~AberturaGraficoControlador() {}

		void mouseSobre( int x, int y );
		void mousePressionado( int x, int y );
		void teclaPressionada( int tecla );

};

#endif
