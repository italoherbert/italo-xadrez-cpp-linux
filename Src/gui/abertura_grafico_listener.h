
#ifndef ABERTURA_GRAFICO_LISTENER_H
#define ABERTURA_GRAFICO_LISTENER_H

class AberturaGraficoListener {
	
	public:		
		virtual ~AberturaGraficoListener() {}

		virtual void mouseSobre( int x, int y ) = 0;
		virtual void mousePressionado( int x, int y ) = 0;
		virtual void teclaPressionada( int tecla ) = 0;
		
};

#endif
