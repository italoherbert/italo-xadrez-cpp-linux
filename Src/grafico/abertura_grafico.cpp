
#include "abertura_grafico.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>

AberturaGrafico::AberturaGrafico( GUI* gui, Jogo* jogo ) {
	this->gui = gui;
	this->jogo = jogo;
	this->aberturaIMG = NULL;
	
	textoCor->r = 255;
	textoCor->g = 255;
	textoCor->b = 255;

	opcaoTextoCor->r = 50;
	opcaoTextoCor->g = 100;
	opcaoTextoCor->b = 225;

	opcaoTextoSobreCor->r = 0;
	opcaoTextoSobreCor->g = 255;
	opcaoTextoSobreCor->b = 0;

	opcaoFundoCor->r = 0;
	opcaoFundoCor->g = 0;
	opcaoFundoCor->b = 0;

	opcaoFundoSobreCor->r = 50;
	opcaoFundoSobreCor->g = 120;
	opcaoFundoSobreCor->b = 180;

	opcaoBordaCor->r = 0;
	opcaoBordaCor->g = 0;
	opcaoBordaCor->b = 0;

	btnTextoCor->r = 255;
	btnTextoCor->g = 255;
	btnTextoCor->b = 255;

	btnFundoCor->r = 0;
	btnFundoCor->g = 0;
	btnFundoCor->b = 200;

	btnTextoSobreCor->r = 200;
	btnTextoSobreCor->g = 200;
	btnTextoSobreCor->b = 200;
	
	btnFundoSobreCor->r = 50;
	btnFundoSobreCor->g = 120;
	btnFundoSobreCor->b = 180;

	btnBordaCor->r = 255;
	btnBordaCor->g = 255;
	btnBordaCor->b = 255;

	jogadorTextoOpcaoCor = opcaoTextoCor;
	computadorTextoOpcaoCor = opcaoTextoCor;
	jogarBTTextoOpcaoCor = btnTextoCor;

	jogadorFundoOpcaoCor = opcaoFundoCor;
	computadorFundoOpcaoCor = opcaoFundoCor;
	jogarBTFundoOpcaoCor = btnFundoCor;
}

void AberturaGrafico::inicializa() {	
	aberturaIMG = IMG_Load( "img/abertura.png" );
}

void AberturaGrafico::finaliza() {
	SDL_FreeSurface( aberturaIMG );
}

void AberturaGrafico::sobreOpcao( int opcao ) {
	jogadorTextoOpcaoCor = opcaoTextoCor;
	computadorTextoOpcaoCor = opcaoTextoCor;
	jogarBTTextoOpcaoCor = btnTextoCor;

	jogadorFundoOpcaoCor = opcaoFundoCor;
	computadorFundoOpcaoCor = opcaoFundoCor;
	jogarBTFundoOpcaoCor = btnFundoCor;

	switch( opcao ) {
		case OPCAO_SET_TIPO_JOGADOR:
			jogadorTextoOpcaoCor = opcaoTextoSobreCor;
			jogadorFundoOpcaoCor = opcaoFundoSobreCor;
			break;
		case OPCAO_SET_TIPO_COMPUTADOR:
			computadorTextoOpcaoCor = opcaoTextoSobreCor;
			computadorFundoOpcaoCor = opcaoFundoSobreCor;
			break;
		case OPCAO_JOGAR:
			jogarBTTextoOpcaoCor = btnTextoSobreCor;
			jogarBTFundoOpcaoCor = btnFundoSobreCor;
			break;
	}
}

void AberturaGrafico::desenha( SDL_Renderer* pintor ) {
	SDL_SetRenderDrawColor( pintor, 0, 0, 0, SDL_ALPHA_OPAQUE );
	SDL_RenderClear( pintor );

	if ( aberturaIMG != NULL ) {
		int l, a;
		gui->carregaTelaDIM( &l, &a );

		SDL_Rect* ret = new SDL_Rect;

	 	ret->x = ( l - aberturaIMG->w ) / 2;
	 	ret->y = ( a - aberturaIMG->h ) / 2;
	 	ret->w = aberturaIMG->w;
	 	ret->h = aberturaIMG->h;

		SDL_Texture* tx = SDL_CreateTextureFromSurface( pintor, aberturaIMG );
		SDL_RenderCopy( pintor, tx, NULL, ret );
		SDL_DestroyTexture( tx );
	}

	this->desenhaMenu( pintor );

	SDL_RenderPresent( pintor );
}

void AberturaGrafico::desenhaMenu( SDL_Renderer* pintor ) {
	std::string jogadorOpcaoTextoStr = jogo->getNivelString( jogo->getNivel( false ) );
	std::string computadorOpcaoTextoStr = jogo->getNivelString( jogo->getNivel( true ) );

	const char* jogadorOpcaoTexto = jogadorOpcaoTextoStr.c_str();
	const char* computadorOpcaoTexto = computadorOpcaoTextoStr.c_str();

	int espacamento = MENU_ABERTURA_ESP;

	int espBT_H = MENU_ABERTURA_ESP_BT_H;
	int espBT_V = MENU_ABERTURA_ESP_BT_V;
	
	int espOp_H = MENU_ABERTURA_ESP_OP_H;
	int espOpRotulo_H = MENU_ABERTURA_ESP_OP_ROTULO_W;

	int larguraFundoTexto = MENU_ABERTURA_LARGURA_FUNDO_TEXTO;
	
	int x = espacamento;
	int y = espacamento;

	TTF_Font* fonte = gui->getFonte();

	int jog_str_l,jog_str_a;
	TTF_SizeText( fonte, jogadorStr.c_str(), &jog_str_l, &jog_str_a );

	int comp_str_l, comp_str_a;
	TTF_SizeText( fonte, computadorStr.c_str(), &comp_str_l, &comp_str_a );

	int msg_l, msg_a;
	TTF_SizeText( fonte, opcoesStr.c_str(), &msg_l, &msg_a );

	menuRet = new SDL_Rect;
	menuRet->w = ( 2 * espacamento ) + larguraFundoTexto;

	opcoesTituloRet = new SDL_Rect;
	opcoesTituloRet->x = x + ( ( larguraFundoTexto - msg_l ) / 2 );
	opcoesTituloRet->y = y + espBT_V;
	opcoesTituloRet->w = msg_l;
	opcoesTituloRet->h = msg_a;
	
	y += opcoesTituloRet->h + espacamento + ( 2 * espBT_V );
		
	TTF_SizeText( fonte, jogadorOpcaoTexto, &msg_l, &msg_a );

	jogador1TextoRet = new SDL_Rect;
	jogador1TextoRet->x = x + espOp_H;
	jogador1TextoRet->y = y + espBT_V;
	jogador1TextoRet->w = jog_str_l;
	jogador1TextoRet->h = jog_str_a;

	jogadorTextoOpcaoRet = new SDL_Rect;
	jogadorTextoOpcaoRet->x = x + espOp_H + espOpRotulo_H + comp_str_l;
	jogadorTextoOpcaoRet->y = y + espBT_V;
	jogadorTextoOpcaoRet->w = msg_l;
	jogadorTextoOpcaoRet->h  = msg_a;

	jogadorOpcaoRet = new SDL_Rect;
	jogadorOpcaoRet->x = x;
	jogadorOpcaoRet->y = y;
	jogadorOpcaoRet->w = larguraFundoTexto;
	jogadorOpcaoRet->h = ( 2 * espBT_V ) + msg_a;

	y += jogadorOpcaoRet->h + espacamento;

	TTF_SizeText( fonte, computadorOpcaoTexto, &msg_l, &msg_a );

	jogador2TextoRet = new SDL_Rect;
	jogador2TextoRet->x = x + espOp_H;
	jogador2TextoRet->y = y + espBT_V;
	jogador2TextoRet->w = comp_str_l;
	jogador2TextoRet->h = comp_str_a;

	computadorTextoOpcaoRet = new SDL_Rect;
	computadorTextoOpcaoRet->x = x + espOp_H + espOpRotulo_H + comp_str_l;
	computadorTextoOpcaoRet->y = y + espBT_V;
	computadorTextoOpcaoRet->w = msg_l;
	computadorTextoOpcaoRet->h  = msg_a;

	computadorOpcaoRet = new SDL_Rect;
	computadorOpcaoRet->x = x;
	computadorOpcaoRet->y = y;
	computadorOpcaoRet->w = larguraFundoTexto;
	computadorOpcaoRet->h = ( 2 * espBT_V ) + msg_a;
		
	y += computadorOpcaoRet->h + ( espacamento );
	
	TTF_SizeText( fonte, jogarStr.c_str(), &msg_l, &msg_a );

	int jogarBT_X =  ( menuRet->w -( msg_l + ( 2 * espBT_H ) ) ) / 2;

	jogarBTTextoOpcaoRet = new SDL_Rect;
	jogarBTTextoOpcaoRet->x = jogarBT_X + espBT_H;
	jogarBTTextoOpcaoRet->y = y + espBT_V + 2;
	jogarBTTextoOpcaoRet->w = msg_l;
	jogarBTTextoOpcaoRet->h  = msg_a;

	jogarBTOpcaoRet = new SDL_Rect;
	jogarBTOpcaoRet->w = msg_l + ( 2 * espBT_H );
	jogarBTOpcaoRet->h = msg_a + espBT_V;
	jogarBTOpcaoRet->x = jogarBT_X;
	jogarBTOpcaoRet->y = y + espBT_V;

	y += jogarBTOpcaoRet->h + espacamento;

	menuRet->h = y + espacamento;
			
	int tela_l, tela_a;	
	gui->carregaTelaDIM( &tela_l, &tela_a );	
	
	menuRet->x = ( tela_l - menuRet->w ) / 2;
	menuRet->y = 235;

	SDL_SetRenderDrawColor( pintor, 0, 0, 0, 0 );
	SDL_RenderFillRect( pintor, menuRet );

	SDL_SetRenderDrawColor( pintor, 255, 255, 255, 100 );
	SDL_RenderDrawRect( pintor, menuRet );

	this->desenhaBTFundo( pintor, jogadorOpcaoRet, jogadorFundoOpcaoCor, opcaoBordaCor );
	this->desenhaBTFundo( pintor, computadorOpcaoRet, computadorFundoOpcaoCor, opcaoBordaCor );
	this->desenhaBTFundo( pintor, jogarBTOpcaoRet, jogarBTFundoOpcaoCor, btnBordaCor );

	this->desenhaTexto( pintor, opcoesTituloRet, opcoesStr.c_str(), textoCor );

	this->desenhaTexto( pintor, jogador1TextoRet, jogadorStr.c_str(), textoCor );
	this->desenhaTexto( pintor, jogadorTextoOpcaoRet, jogadorOpcaoTexto, jogadorTextoOpcaoCor );

	this->desenhaTexto( pintor, jogador2TextoRet, computadorStr.c_str(), textoCor );
	this->desenhaTexto( pintor, computadorTextoOpcaoRet, computadorOpcaoTexto, computadorTextoOpcaoCor );

	this->desenhaTexto( pintor, jogarBTTextoOpcaoRet, jogarStr.c_str(), jogarBTTextoOpcaoCor );
}

void AberturaGrafico::desenhaTexto( SDL_Renderer* pintor, SDL_Rect* rect, const char* texto, SDL_Color* cor ) {
	TTF_Font* fonte = gui->getFonte();

	SDL_Rect* texto_ret = new SDL_Rect;
	texto_ret->x = menuRet->x + rect->x;
	texto_ret->y = menuRet->y + rect->y;
	texto_ret->w = rect->w;
	texto_ret->h = rect->h;

	SDL_Color cor2 = { cor->r, cor->g, cor->b };

	SDL_Surface* texto_sf = TTF_RenderText_Blended( fonte, texto, cor2 );
	SDL_Texture* tx = SDL_CreateTextureFromSurface( pintor, texto_sf );
	SDL_RenderCopy( pintor, tx, NULL, texto_ret );
	SDL_FreeSurface( texto_sf );
	SDL_DestroyTexture( tx );
}

void AberturaGrafico::desenhaBTFundo( SDL_Renderer* pintor, SDL_Rect* rect, SDL_Color* cor, SDL_Color* bordaCor ) {
	SDL_Rect* fundo_ret = new SDL_Rect;
	fundo_ret->x = menuRet->x + rect->x;
	fundo_ret->y = menuRet->y + rect->y;
	fundo_ret->w = rect->w;
	fundo_ret->h = rect->h;

	SDL_SetRenderDrawColor( pintor, cor->r, cor->g, cor->b, SDL_ALPHA_OPAQUE );
	SDL_RenderFillRect( pintor, fundo_ret );

	SDL_SetRenderDrawColor( pintor, bordaCor->r, bordaCor->g, bordaCor->b, SDL_ALPHA_OPAQUE );
	SDL_RenderDrawRect( pintor, fundo_ret );
}

bool AberturaGrafico::isMouseJogadorUmOpBT( int mouseX, int mouseY ) {
	return this->isMouseEmBT( jogadorOpcaoRet, mouseX, mouseY );
}

bool AberturaGrafico::isMouseJogadorDoisOpBT( int mouseX, int mouseY ) {
	return this->isMouseEmBT( computadorOpcaoRet, mouseX, mouseY );
}

bool AberturaGrafico::isMouseJogarBT( int mouseX, int mouseY ) {
	return this->isMouseEmBT( jogarBTOpcaoRet, mouseX, mouseY );
}

bool AberturaGrafico::isMouseEmBT( SDL_Rect* rect, int mouseX, int mouseY )	{
	int x1 = menuRet->x + rect->x;
	int y1 = menuRet->y + rect->y;
	int x2 = menuRet->x + rect->x + rect->w;
	int y2 = menuRet->y + rect->y + rect->h;
	
	return ( mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2 );	
}

