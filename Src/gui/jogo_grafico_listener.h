
#ifndef JOGO_GRAFICO_LISTENER_H
#define JOGO_GRAFICO_LISTENER_H

class JogoGraficoListener {
	
	public:									 
		const static int TECLA_ESQ = 1;		
		const static int TECLA_ENTER = 2;
	
		virtual ~JogoGraficoListener() {}

		virtual void executando() = 0;
		
		virtual void mousePressionado( int x, int y ) = 0;
		virtual void teclaPressionada( int tecla ) = 0;					 		
	
};

#endif
