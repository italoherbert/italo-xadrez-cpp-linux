
#include "GUI.h"

GUI::GUI( GUI_Driver* drv ) {
	this->drv = drv;
	this->graficoTipo = ABERTURA_GRAFICO;
}

void GUI::reinicia() {
	this->setGraficoTipo( ABERTURA_GRAFICO );
	this->repinta();
}

void GUI::execGUI( std::string titulo, int largura, int altura ) {
	SDL_Init( SDL_INIT_EVERYTHING );
	IMG_Init( IMG_INIT_PNG );
	Mix_Init( MIX_INIT_MID );
	TTF_Init();

	Mix_OpenAudio( 22050, AUDIO_S16SYS, 2, 1024 );

	fonte = TTF_OpenFont( "arial.ttf", 24 );
	infoFonte = TTF_OpenFont( "arial.ttf", 18 );
	
	janela = SDL_CreateWindow( titulo.c_str(), 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		largura, altura, 
		SDL_WINDOW_SHOWN
	);	
	
	pintor = SDL_CreateRenderer( janela, -1, SDL_RENDERER_SOFTWARE );
	tela = SDL_GetWindowSurface( janela );

	cursorSeta = SDL_CreateSystemCursor( SDL_SYSTEM_CURSOR_ARROW );	
	cursorMaozinha = SDL_CreateSystemCursor( SDL_SYSTEM_CURSOR_HAND );

	SDL_Event evento;
	
	if ( listener != NULL )
		listener->inicializou();		
	
	fim = false;
	repintar = true;

	while( !fim ) {
		if ( repintar ) {
			switch ( graficoTipo ) {
				case ABERTURA_GRAFICO:
					aberturaGrafico->desenha( pintor );
					break;
				case JOGO_GRAFICO:
					jogoGrafico->desenha( pintor );
					break;
			}
			repintar = false;
		}

		if ( listener != NULL ) {		
			while( SDL_PollEvent( &evento ) != 0 ) {
				switch( evento.type ) {
					case SDL_QUIT:					
						listener->janelaFechada();
						fim = true;
						break;
					case SDL_MOUSEBUTTONDOWN:
						if ( graficoTipo == ABERTURA_GRAFICO ) {
							if ( aberturaGraficoListener != NULL )
								aberturaGraficoListener->mousePressionado( evento.motion.x, evento.motion.y );
						} else if ( graficoTipo == JOGO_GRAFICO ) {
							if ( jogoGraficoListener != NULL )
								jogoGraficoListener->mousePressionado( evento.motion.x, evento.motion.y );
						}
						break;
					case SDL_MOUSEMOTION:
						if ( graficoTipo == ABERTURA_GRAFICO ) {
							if ( aberturaGraficoListener != NULL)		
								aberturaGraficoListener->mouseSobre( evento.motion.x, evento.motion.y );
						}
						break;
					case SDL_KEYDOWN:
						if ( graficoTipo == ABERTURA_GRAFICO ) {												
							if ( aberturaGraficoListener != NULL )
								if ( evento.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
									aberturaGraficoListener->teclaPressionada( JogoGraficoListener::TECLA_ESQ );						
						} else if ( graficoTipo == JOGO_GRAFICO ) {
							if ( jogoGraficoListener != NULL ) {
								if ( evento.key.keysym.scancode == SDL_SCANCODE_ESCAPE ) {
									jogoGraficoListener->teclaPressionada( JogoGraficoListener::TECLA_ESQ );
								} else if ( evento.key.keysym.scancode == SDL_SCANCODE_RETURN ) {
									jogoGraficoListener->teclaPressionada( JogoGraficoListener::TECLA_ENTER );
								}
							}
						}
						break;						
				}
			}
		}

		SDL_Delay( DELAY );
	}
	
	if ( listener != NULL )
		listener->finalizando();
	
	IMG_Quit();

	TTF_CloseFont( infoFonte );
	TTF_CloseFont( fonte );
	TTF_Quit();
	
	Mix_CloseAudio();	
	Mix_Quit();
	
	SDL_DestroyRenderer( pintor );
	SDL_DestroyWindow( janela );
	SDL_Quit();	
}

void GUI::execJogo( void* id ) {
	while( !fim ) {
		if ( graficoTipo == JOGO_GRAFICO )
			if ( jogoGraficoListener != NULL )
				jogoGraficoListener->executando();

		SDL_Delay( DELAY );
	}
}

void GUI::repinta() {
	this->repintar = true;
}

void GUI::setCursorTipo( int tipo ) {
	switch( tipo ) {
		case CURSOR_SETA:
			SDL_SetCursor( cursorSeta );
			break;
		case CURSOR_MAOZINHA:
			SDL_SetCursor( cursorMaozinha );
			break;
	}
}

void GUI::setGraficoTipo( int tipo ) {		
	this->graficoTipo = tipo;
}

void GUI::carregaTelaDIM( int* largura, int* altura ) {
	SDL_GetWindowSize( janela, largura, altura );
}

void GUI::setAberturaGrafico( Grafico* grafico ) {
	this->aberturaGrafico = grafico;
}

void GUI::setJogoGrafico( Grafico* grafico ) {
	this->jogoGrafico = grafico;
}

void GUI::setGUIListener( GUI_Listener* listener ) {
	this->listener = listener;
}

void GUI::setAberturaGraficoListener( AberturaGraficoListener* listener ) {
	this->aberturaGraficoListener = listener;
}

void GUI::setJogoGraficoListener( JogoGraficoListener* listener ) {
	this->jogoGraficoListener = listener;
}

SDL_Surface* GUI::getTela() {
	return tela;
}

TTF_Font* GUI::getFonte() {
	return fonte;
}

TTF_Font* GUI::getInfoFonte() {
	return infoFonte;
}
