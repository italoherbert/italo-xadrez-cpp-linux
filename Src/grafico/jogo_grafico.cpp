#include "jogo_grafico.h"

#include <cstdlib>

#include "../consts.h"

JogoGrafico::JogoGrafico( Jogo* jogo, GUI* gui ) {
	this->jogo = jogo;
	this->gui = gui;
	
	this->infoDesenho = new InfoDesenho();
	this->tabuleiroDesenho = new TabuleiroDesenho();
	this->pecaDesenho = new PecaDesenho();
	this->mensagemDesenho = new MensagemDesenho();
	this->audioLigadoDesenho = new AudioLigadoDesenho();

	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
}

JogoGrafico::~JogoGrafico() {
	delete infoDesenho;
	delete tabuleiroDesenho;
	delete pecaDesenho;
	delete mensagemDesenho;
	delete audioLigadoDesenho;
}

void JogoGrafico::inicializa() {
	pecaDesenho->carregaIMGs();
	audioLigadoDesenho->inicializa( gui );
}

void JogoGrafico::finaliza() {
	pecaDesenho->liberaIMGs();
	audioLigadoDesenho->finaliza();
}
		
void JogoGrafico::desenha( SDL_Renderer* pintor ) {
	SDL_SetRenderDrawColor( pintor, 225, 225, 225, SDL_ALPHA_OPAQUE );
	SDL_RenderClear( pintor );
		
	infoDesenho->desenha( jogo, gui, pintor );
	tabuleiroDesenho->desenha( jogo, gui, pintor );
	
	JogadaLista* cLista = new JogadaLista;
	jogo->getJogadasPossiveis()->copiaPara( cLista );

	Peca* jps[ Jogo::N_PECAS ];
	Peca* cps[ Jogo::N_PECAS ];

	jogo->copia_pecas( jps, cps );

	int tam = cLista->getTam();
	
	for( int i = 0; i < tam; i++ ) {
		Jogada* jogada = cLista->getJogada( i );						
		desenhaMarc( jogo, jogada->getPosX(), jogada->getPosY(), pintor );
	}		
	
	Peca* jogadorJPeca = jogo->getJogadorJogadaPeca();
	int jogsPossTam = jogo->getJogadasPossiveis()->getTam();
	if ( jogadorJPeca != NULL && jogsPossTam > 0 )
		desenhaMarc( jogo, jogadorJPeca->getPosX(), jogadorJPeca->getPosY(), pintor );
	


	for( int i = 0; i < Jogo::N_PECAS; i++ ) {
		Peca* jogadorPeca = jps[ i ];
		Peca* computadorPeca = cps[ i ];
							
		if ( !jogadorPeca->isRemovida() )
			pecaDesenho->desenha( jogo, gui, pintor, jogadorPeca, PecaDesenho::COR_BRANCA );
		if ( !computadorPeca->isRemovida() )
			pecaDesenho->desenha( jogo, gui, pintor, computadorPeca, PecaDesenho::COR_PRETA );
	}				
	
	for( int i = 0; i < tam; i++ ) {
		Jogada* jogada = cLista->getJogada( i );
		if( jogada->getCaptura() != NULL )					
			if ( jogada->getCaptura()->getTipo() != Jogo::REI )
				pecaDesenho->desenha( jogo, gui, pintor, jogada->getCaptura(), PecaDesenho::COR_VERMELHA );
	}
	
	mensagemDesenho->desenha( jogo, gui, pintor );
	
	audioLigadoDesenho->desenha( jogo, gui, pintor );
	
	SDL_RenderPresent( pintor );

	jogo->deleta_pecas( jps );
	jogo->deleta_pecas( cps );
	delete cLista;
}

void JogoGrafico::desenhaMarc( Jogo* jogo, int posX, int posY, SDL_Renderer* pintor ) {
	int x = jogo->getTela()->getCelulaX( posX );
	int y = jogo->getTela()->getCelulaY( posY );
	int cdim = jogo->getTela()->getCelulaDIM();
	
	SDL_Rect cRet = { x, y, cdim, cdim };				
	
	SDL_SetRenderDrawColor( pintor, 200, 200, 255, SDL_ALPHA_OPAQUE );
	SDL_RenderFillRect( pintor, &cRet );
	
	SDL_SetRenderDrawColor( pintor, 150, 150, 100, SDL_ALPHA_OPAQUE );
	SDL_RenderDrawRect( pintor, &cRet );	
}

MensagemDesenho* JogoGrafico::getMensagemDesenho() {
	return this->mensagemDesenho;
}

AudioLigadoDesenho* JogoGrafico::getAudioLigadoDesenho() {
	return this->audioLigadoDesenho;
}

InfoDesenho* JogoGrafico::getInfoDesenho() {
	return this->infoDesenho;
}
