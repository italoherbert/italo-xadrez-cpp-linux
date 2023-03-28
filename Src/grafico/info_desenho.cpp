
#include "info_desenho.h"

#include <cstring>
#include <SDL2/SDL_ttf.h>

InfoDesenho::InfoDesenho() {
	reiPreto = IMG_Load( "img/rei-preto.png" );
	reiBranco = IMG_Load( "img/rei-branco.png" );
	reiVermelho = IMG_Load( "img/rei-vermelho.png" );
}

InfoDesenho::~InfoDesenho() {
	SDL_FreeSurface( reiPreto );
	SDL_FreeSurface( reiBranco );
	SDL_FreeSurface( reiVermelho );
}

int InfoDesenho::desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor ) {
	int brancasNivel = jogo->getNivel( false );
	int pretasNivel = jogo->getNivel( true );
	int vitorias = jogo->getVitoriasCont( false );
	int derrotas = jogo->getVitoriasCont( true );
	int empates = jogo->getEmpatesCont();

	std::string brancasNivelString = jogo->getNivelString( brancasNivel ).c_str();
	std::string pretasNivelString = jogo->getNivelString( pretasNivel ).c_str();

	std::string vitoriasString = std::to_string( vitorias );
	std::string derrotasString = std::to_string( derrotas );
	std::string empatesString = std::to_string( empates );

	const char* brancasNivelStr = brancasNivelString.c_str();
	const char* pretasNivelStr = pretasNivelString.c_str();

	const char* vitoriasStr = vitoriasString.c_str();
	const char* derrotasStr = derrotasString.c_str();
	const char* empatesStr = empatesString.c_str();

	int w = 0;
	w += this->calculaPainelLargura( gui, reiBranco, brancasNivelStr ) + infoEsp;
	w += this->calculaPainelLargura( gui, reiPreto, pretasNivelStr ) + infoEsp;
	w += this->calculaPainelLargura( gui, reiBranco, vitoriasStr ) + infoEsp;
	w += this->calculaPainelLargura( gui, reiPreto, derrotasStr ) + infoEsp;
	w += this->calculaPainelLargura( gui, reiVermelho, empatesStr ) + infoEsp;

	int x = ( gui->getTela()->w - w ) / 2;

	x = this->desenhaInfo( gui, pintor, reiBranco, brancasNivelStr, x );
	x = this->desenhaInfo( gui, pintor, reiPreto, pretasNivelStr, x );
	x = this->desenhaInfo( gui, pintor, reiBranco, vitoriasStr, x );
	x = this->desenhaInfo( gui, pintor, reiPreto, derrotasStr, x );
	x = this->desenhaInfo( gui, pintor, reiVermelho, empatesStr, x );

	TTF_Font* fonte = gui->getFonte();
	int msg_l, msg_a;

	TTF_SizeText( fonte, vitoriasStr, &msg_l, &msg_a );

	painelH = msg_a + ( 2 * borda );

	return painelH;
}

int InfoDesenho::calculaPainelLargura( GUI* gui, SDL_Surface* rei, const char* info ) {
	TTF_Font* fonte = gui->getInfoFonte();

	int msg_l, msg_a;
	TTF_SizeText( fonte, info, &msg_l, &msg_a );

	return reiPecaImgDim + imgInfoEsp + msg_l;
}

int InfoDesenho::desenhaInfo( GUI* gui, SDL_Renderer* pintor, SDL_Surface* rei, const char* info, int x ) {
	TTF_Font* fonte = gui->getInfoFonte();

	SDL_Color corInfo = { 0, 50, 200 };

	int msg_l, msg_a;

	SDL_Rect* imgRet = new SDL_Rect;
	imgRet->x = x;
	imgRet->y = borda - reiPecaImgDim/4;
	imgRet->w = reiPecaImgDim;
	imgRet->h = reiPecaImgDim;

	SDL_Texture* tx = SDL_CreateTextureFromSurface( pintor, rei );
	SDL_RenderCopy( pintor, tx, NULL, imgRet );
	SDL_DestroyTexture( tx );

	int x2 = x + reiPecaImgDim + imgInfoEsp;

	TTF_SizeText( fonte, info, &msg_l, &msg_a );

	SDL_Rect* brancasNivelInfoRet = new SDL_Rect;
	brancasNivelInfoRet->x = x2;
	brancasNivelInfoRet->y = borda;
	brancasNivelInfoRet->w = msg_l;
	brancasNivelInfoRet->h = msg_a;

	SDL_Surface* texto_sf = TTF_RenderText_Blended( fonte, info, corInfo );
	tx = SDL_CreateTextureFromSurface( pintor, texto_sf );
	SDL_RenderCopy( pintor, tx, NULL, brancasNivelInfoRet );
	SDL_FreeSurface( texto_sf );
	SDL_DestroyTexture( tx );

	delete imgRet;
	delete brancasNivelInfoRet;

	return x2 + msg_l + infoEsp;
}

int InfoDesenho::getPainelAltura() {
	return painelH;
}

