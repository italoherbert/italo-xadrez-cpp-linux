
#ifndef JOGO_GRAFICO_CONTROLADOR_H
#define JOGO_GRAFICO_CONTROLADOR_H

#include "../sistema.h"

class Sistema;

class JogoGraficoControlador : public JogoGraficoListener {
	
	private:
		const long NO_START = -1;

		const long NO_DELAY = -1;
		const long MENSAGEM_DELAY = 1500;
		const long FIM_JOGO_MENSAGEM_DELAY = 4000;

		Peca* pecaSelecionada = nullptr;
		long mensagemDelay = -1;
		
		Sistema* sistema;
		
		bool selecionaPeca( int posX, int posY, bool isComp );
		bool processaJogada( int posX, int posY );		

		void setMensagem( std::string mensagem, long delay );
		void removeMensagem();
		
		bool verificaSeXeque();
		int verificaEProcessaXequeMate();

	public:
		JogoGraficoControlador( Sistema* sistema );
		
		void executando();
		
		void mousePressionado( int x, int y );
		void teclaPressionada( int tecla );
};

#endif
