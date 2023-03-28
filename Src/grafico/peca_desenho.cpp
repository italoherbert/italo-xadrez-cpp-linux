#include "peca_desenho.h"

#include <SDL2/SDL_image.h>


void PecaDesenho::desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor, Peca* peca, int corTipo ) {
	SDL_Surface* imagem = this->getPecaIMG( peca->getTipo(), corTipo );			
				
	SDL_Rect ret;
 	ret.x = jogo->getTela()->getCelulaX( peca->getPosX() );
 	ret.y = jogo->getTela()->getCelulaY( peca->getPosY() );
 	ret.w = jogo->getTela()->getCelulaDIM();
 	ret.h = jogo->getTela()->getCelulaDIM();
	ret.x = ret.x + ( ( ret.w - imagem->w ) / 2 );
	ret.y = ret.y + ( ( ret.h - imagem->h ) / 2 );
	
	ret.x += peca->getAnimPosX();
	ret.y += peca->getAnimPosY();

	ret.w = imagem->w;
	ret.h = imagem->h;
						
	if ( imagem != NULL ) {			
		SDL_Texture* tx = SDL_CreateTextureFromSurface( pintor, imagem );
		SDL_RenderCopy( pintor, tx, NULL, &ret );
		SDL_DestroyTexture( tx );
	}
}

void PecaDesenho::carregaIMGs() {
	peaoPreto = IMG_Load( "img/peao-preto.png" );			
	peaoBranco = IMG_Load( "img/peao-branco.png" );			
	peaoVermelho = IMG_Load( "img/peao-vermelho.png" );
				
	torrePreta = IMG_Load( "img/torre-preta.png" );			
	torreBranca = IMG_Load( "img/torre-branca.png" );			
	torreVermelha = IMG_Load( "img/torre-vermelha.png" );			
	
	cavaloPreto = IMG_Load( "img/cavalo-preto.png" );			
	cavaloBranco = IMG_Load( "img/cavalo-branco.png" );			
	cavaloVermelho = IMG_Load( "img/cavalo-vermelho.png" );			
	
	bispoPreto = IMG_Load( "img/bispo-preto.png" );			
	bispoBranco = IMG_Load( "img/bispo-branco.png" );			
	bispoVermelho = IMG_Load( "img/bispo-vermelho.png" );
				
	rainhaPreta = IMG_Load( "img/rainha-preta.png" );			
	rainhaBranca = IMG_Load( "img/rainha-branca.png" );			
	rainhaVermelha = IMG_Load( "img/rainha-vermelha.png" );			
	
	reiPreto = IMG_Load( "img/rei-preto.png" );			
	reiBranco = IMG_Load( "img/rei-branco.png" );			
	reiVermelho = IMG_Load( "img/rei-vermelho.png" );
}

void PecaDesenho::liberaIMGs() {
	SDL_FreeSurface( peaoPreto );
	SDL_FreeSurface( peaoBranco );
	SDL_FreeSurface( peaoVermelho );
	
	SDL_FreeSurface( torrePreta );
	SDL_FreeSurface( torreBranca );
	SDL_FreeSurface( torreVermelha );
	
	SDL_FreeSurface( cavaloPreto );
	SDL_FreeSurface( cavaloBranco );
	SDL_FreeSurface( cavaloVermelho );
	
	SDL_FreeSurface( bispoPreto );
	SDL_FreeSurface( bispoBranco );
	SDL_FreeSurface( bispoVermelho );
	
	SDL_FreeSurface( rainhaPreta );
	SDL_FreeSurface( rainhaBranca );
	SDL_FreeSurface( rainhaVermelha );
	
	SDL_FreeSurface( reiPreto );
	SDL_FreeSurface( reiBranco );
	SDL_FreeSurface( reiVermelho );
}

SDL_Surface* PecaDesenho::getPecaIMG( int pecaTipo, int corTipo ) {	
	switch( pecaTipo ) {			
		case Jogo::PEAO:
			if ( corTipo == COR_PRETA ) {
				return peaoPreto;			 				 				 		 																		
			} else if ( corTipo == COR_BRANCA ) {
				return peaoBranco;
			} else if ( corTipo == COR_VERMELHA ) {
				return peaoVermelho;
			}			
			break;			
		case Jogo::CAVALO:
		 	if ( corTipo == COR_PRETA ) {
		 		return cavaloPreto;
			} else if ( corTipo == COR_BRANCA ) {
				return cavaloBranco;
			} else if ( corTipo == COR_VERMELHA ) {
				return cavaloVermelho;
			}			 				 				 	
		 	break;
		case Jogo::BISPO:
		 	if ( corTipo == COR_PRETA ) {
		 		return bispoPreto;
			} else if ( corTipo == COR_BRANCA ) {
				return bispoBranco;
			} else if ( corTipo == COR_VERMELHA ) {
				return bispoVermelho;
			}			 				 				 	
		 	break;
		case Jogo::RAINHA:
		 	if ( corTipo == COR_PRETA ) {
		 		return rainhaPreta;
			} else if ( corTipo == COR_BRANCA ) {
				return rainhaBranca;
			} else if ( corTipo == COR_VERMELHA ) {
				return rainhaVermelha;
			}			 				 				 	
		 	break;
		case Jogo::REI:
		 	if ( corTipo == COR_PRETA ) {
		 		return reiPreto;
			} else if ( corTipo == COR_BRANCA ) {
				return reiBranco;
			} else if ( corTipo == COR_VERMELHA ) {
				return reiVermelho;
			}
			break;			 				 				 	
		case Jogo::TORRE:
		 	if ( corTipo == COR_PRETA ) {
		 		return torrePreta;
			} else if ( corTipo == COR_BRANCA ) {
				return torreBranca;
			} else if ( corTipo == COR_VERMELHA ) {
				return torreVermelha;
			}			 				 				 	
			break;			
	}	
	return NULL;	
}

