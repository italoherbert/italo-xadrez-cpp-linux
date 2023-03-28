
#ifndef TELA_DRIVER_ADAPTER_H
#define TELA_DRIVER_ADAPTER_H

#include "gui/GUI.h"
#include "gui/GUI_driver.h"

#include "grafico/jogo_grafico.h"

#include "logica/jogo.h"
#include "logica/jogo_driver.h"

class DriverAdapter : public JogoDriver, public GUI_Driver {
	
	private:
		GUI* gui;
		Jogo* jogo;
		JogoGrafico* jogoGrafico;
		
	public:
		void setJogoEGUI( GUI* gui, Jogo* jogo, JogoGrafico* jogoGrafico );
		
		int getTelaLargura();
		int getTelaAltura();
		
		int getInfoPainelAltura();
		double getFatorCelulaDIM();

		bool isPausa();
};

#endif
