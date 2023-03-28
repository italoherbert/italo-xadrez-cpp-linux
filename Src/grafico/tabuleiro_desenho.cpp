
#include "tabuleiro_desenho.h"

void TabuleiroDesenho::desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor ) {
	int celula_dim = jogo->getTela()->getCelulaDIM();
	int tab_x = jogo->getTela()->getTabuleiroX();
	int tab_y = jogo->getTela()->getTabuleiroY();
	int tab_dim = jogo->getTela()->getTabuleiroDIM();
	
	int borda = TABULEIRO_BORDA;
	
	SDL_Rect ret_fundo;
	ret_fundo.x = tab_x - borda;
	ret_fundo.y = tab_y - borda;
	ret_fundo.w = ( 2 * borda ) + tab_dim;
	ret_fundo.h = ( 2 * borda ) + tab_dim;			
		
	SDL_SetRenderDrawColor( pintor, 100, 100, 50, SDL_ALPHA_OPAQUE );
	SDL_RenderFillRect( pintor, &ret_fundo );

	int cont = 0;
	for( int i = 0; i < 8; i++ ) {
		int x = tab_x + ( i * celula_dim );
		
		cont = i;
		for( int j = 0; j < 8; j++ ) {		
			int y = tab_y + ( j * celula_dim );
				
			SDL_Rect ret;
			ret.x = x;
			ret.y = y;
			ret.w = celula_dim;
			ret.h = celula_dim;	
				
			if ( cont % 2 == 0 ) {			
				SDL_SetRenderDrawColor( pintor, 220, 220, 175, SDL_ALPHA_OPAQUE );
				SDL_RenderFillRect( pintor, &ret );			
			} else {
				SDL_SetRenderDrawColor( pintor, 150, 150, 100, SDL_ALPHA_OPAQUE );
				SDL_RenderFillRect( pintor, &ret );		
			}					
			
			cont++;
		}		
	}		
}

