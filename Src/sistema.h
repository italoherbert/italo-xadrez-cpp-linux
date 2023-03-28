
#ifndef SISTEMA_H
#define SISTEMA_H

#include "logica/jogo.h"

#include "gui/GUI.h"

#include "grafico/abertura_grafico.h"
#include "grafico/jogo_grafico.h"

#include "audio/jogo_audio.h"
#include "animacao/animacao.h"

#include "algoritmo/algoritmo_gerenciador.h"

#include "controlador/GUI_Controlador.h"
#include "controlador/abertura_grafico_controlador.h"
#include "controlador/jogo_grafico_controlador.h"
#include "driver_adapter.h"

class GUI_Controlador;
class AberturaGraficoControlador;
class JogoGraficoControlador;

class Sistema {

	private:
		Jogo* jogo;
		DriverAdapter* drv;
		GUI* gui;

		JogoAudio* audio;

		AberturaGrafico* aberturaGrafico;
		JogoGrafico* jogoGrafico;

		AlgoritmoGerenciador* algoritmoGerenciador;
		Animacao* animacao;

		GUI_Controlador* guiControlador;
		AberturaGraficoControlador* aberturaGraficoControlador;
		JogoGraficoControlador* jogoGraficoControlador;

	public:
		Sistema();
		~Sistema();

		void inicia();
		void finaliza();

		void reinicia();

		void execGUI();
		void execJogo( void* id );

		long tempo();

		Jogo* getJogo();
		DriverAdapter* getJogoDriver();

		GUI* getGUI();
		AberturaGrafico* getAberturaGrafico();
		JogoGrafico* getJogoGrafico();

		JogoAudio* getJogoAudio();
		Animacao* getAnimacao();

		AlgoritmoGerenciador* getAlgoritmoGerenciador();

};

#endif




