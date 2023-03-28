
#include "audio_ligado_desenho.h"

void AudioLigadoDesenho::inicializa( GUI* gui ) {
	audioLigado = IMG_Load( "img/audio-ligado.png" );
	audioDesligado = IMG_Load( "img/audio-desligado.png");
	
	int l, a;
	gui->carregaTelaDIM( &l, &a );
		
	x = ( l - audioLigado->w ) - 25;
	y = 10;
	largura = audioLigado->w;
	altura = audioLigado->h;	
}

void AudioLigadoDesenho::finaliza() {
	SDL_FreeSurface( audioLigado );
	SDL_FreeSurface( audioDesligado );
}

void AudioLigadoDesenho::desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor ) {
	SDL_Surface* imagem;
	if ( jogo->isAudioLigado() ) {	
		imagem = audioLigado;
	} else {
		imagem = audioDesligado;		
	}
	
	SDL_Rect ret;
	ret.x = x;
	ret.y = y;
	ret.w = largura;
	ret.h = altura;
				
	SDL_Texture* tx = SDL_CreateTextureFromSurface( pintor, imagem );
	SDL_RenderCopy( pintor, tx, NULL, &ret );
	SDL_DestroyTexture( tx );
}

bool AudioLigadoDesenho::isMouseEmAudioBT( int mouseX, int mouseY ) {
	int x2 = x + largura;
	int y2 = y + altura;
	return ( mouseX >= x && mouseX <= x2 && mouseY >= y && mouseY <= y2 );	
}

