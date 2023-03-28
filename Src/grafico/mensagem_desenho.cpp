
#include "mensagem_desenho.h"

#include <cstring>

MensagemDesenho::MensagemDesenho() {
	this->mensagem = "";
	this->mensagem.clear();
}

void MensagemDesenho::desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor ) {
	if ( this->mensagem.empty() )
		return;

	int msg_l, msg_a;
	int tela_l, tela_a;
		
	gui->carregaTelaDIM( &tela_l, &tela_a );
	
	TTF_Font* fonte = gui->getFonte();
	TTF_SizeText( fonte, mensagem.c_str(), &msg_l, &msg_a );
		
	int tx = jogo->getTela()->getTabuleiroX();
	int ty = jogo->getTela()->getTabuleiroY();
	int td = jogo->getTela()->getTabuleiroDIM();
	
	SDL_Rect texto_ret;	
	texto_ret.x = tx + ( ( td - msg_l ) / 2 );
	texto_ret.y = ty + ( ( td - msg_a ) / 2 );
	texto_ret.w = msg_l;
	texto_ret.h = msg_a;
	
	SDL_Rect texto2_ret;
	texto2_ret.x = texto_ret.x + 2;
	texto2_ret.y = texto_ret.y + 2;
	texto2_ret.w = texto_ret.w;
	texto2_ret.h = texto_ret.h;
	
	SDL_Rect fundo_ret;
	fundo_ret.x = texto_ret.x - MENSAGEM_BORDA;
	fundo_ret.y = texto_ret.y - MENSAGEM_BORDA;
	fundo_ret.w = texto_ret.w + ( 2 * MENSAGEM_BORDA );
	fundo_ret.h = texto_ret.h + ( 2 * MENSAGEM_BORDA );
	
	SDL_SetRenderDrawColor( pintor, 0, 0, 200, SDL_ALPHA_OPAQUE );
	SDL_RenderFillRect( pintor, &fundo_ret );
	
	SDL_SetRenderDrawColor( pintor, 255, 255, 255, SDL_ALPHA_OPAQUE );
	SDL_RenderDrawRect( pintor, &fundo_ret );
	
	SDL_Color texto2_cor = { 0, 0, 0 };
	SDL_Color texto_cor = { 255, 255, 255 };

	SDL_Surface* texto2_sf = TTF_RenderText_Blended( fonte, mensagem.c_str(), texto2_cor );
	SDL_Texture* txt2 = SDL_CreateTextureFromSurface( pintor, texto2_sf );
	SDL_RenderCopy( pintor, txt2, NULL, &texto2_ret );
	SDL_FreeSurface( texto2_sf );
	SDL_DestroyTexture( txt2 );
	
	SDL_Surface* texto_sf = TTF_RenderText_Blended( fonte, mensagem.c_str(), texto_cor );
	SDL_Texture* txt = SDL_CreateTextureFromSurface( pintor, texto_sf );
	SDL_RenderCopy( pintor, txt, NULL, &texto_ret );
	SDL_FreeSurface( texto_sf );
	SDL_DestroyTexture( txt );
}

void MensagemDesenho::setMensagem( std::string msg ) {
	this->mensagem = msg;
}

void MensagemDesenho::removeMensagem() {
	this->mensagem.clear();
}

bool MensagemDesenho::isMensagemVazia() {
	return this->mensagem.empty();
}
