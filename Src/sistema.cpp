
#include "sistema.h"

#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

Sistema::Sistema() {
	this->drv = new DriverAdapter();

	this->gui = new GUI( drv );
	this->jogo = new Jogo( drv );

	this->aberturaGrafico = new AberturaGrafico( gui, jogo );
	this->jogoGrafico = new JogoGrafico( jogo, gui );

	this->drv->setJogoEGUI( gui, jogo, jogoGrafico );

	this->audio = new JogoAudio();

	this->algoritmoGerenciador = new AlgoritmoGerenciador( jogo );
	this->animacao = new Animacao( jogo );

	this->guiControlador = new GUI_Controlador( this );
	this->aberturaGraficoControlador = new AberturaGraficoControlador( this );
	this->jogoGraficoControlador = new JogoGraficoControlador( this );

	gui->setGUIListener( guiControlador );
	gui->setAberturaGraficoListener( aberturaGraficoControlador );
	gui->setJogoGraficoListener( jogoGraficoControlador );

	gui->setAberturaGrafico( aberturaGrafico );
	gui->setJogoGrafico( jogoGrafico );
}

Sistema::~Sistema() {
	delete jogo;
	delete drv;
	delete aberturaGrafico;
	delete jogoGrafico;
	delete audio;
	delete algoritmoGerenciador;
	delete animacao;

	delete guiControlador;
	delete aberturaGraficoControlador;
	delete jogoGraficoControlador;
}

void Sistema::inicia() {
	aberturaGrafico->inicializa();
	jogoGrafico->inicializa();
	audio->inicializa();

	jogo->reinicia();
	audio->reinicia();
	gui->reinicia();
}

void Sistema::finaliza() {
	aberturaGrafico->finaliza();
	jogoGrafico->finaliza();
	audio->finaliza();
}

void Sistema::reinicia() {
	jogoGrafico->getMensagemDesenho()->removeMensagem();

	gui->reinicia();
	jogo->reinicia();
	audio->reinicia();
}

void Sistema::execGUI() {
	gui->execGUI( "Jogo de Xadrez", Consts::JANELA_LARGURA, Consts::JANELA_ALTURA );
}

void Sistema::execJogo( void* id ) {
	gui->execJogo( id );
}

long Sistema::tempo() {
	return time( NULL );
}

Jogo* Sistema::getJogo() {
	return jogo;
}

DriverAdapter* Sistema::getJogoDriver() {
	return drv;
}

GUI* Sistema::getGUI() {
	return gui;
}

AberturaGrafico* Sistema::getAberturaGrafico() {
	return aberturaGrafico;
}

JogoGrafico* Sistema::getJogoGrafico() {
	return jogoGrafico;
}

Animacao* Sistema::getAnimacao() {
	return animacao;
}

JogoAudio* Sistema::getJogoAudio() {
	return audio;
}

AlgoritmoGerenciador* Sistema::getAlgoritmoGerenciador() {
	return algoritmoGerenciador;
}


