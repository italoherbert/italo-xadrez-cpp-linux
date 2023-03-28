
#ifndef TELA_H
#define TELA_H

#include "jogo_driver.h"

class Tela {
	private:
		JogoDriver* driver;
		
	public:
		Tela( JogoDriver* driver );
		
		int getTabuleiroX();
		int getTabuleiroY();
		int getTabuleiroDIM();
		
		int getCelulaX( int x );
		int getCelulaY( int y );
		
		int getCelulaDIM();	
		
		int getX( int posX );
		int getY( int posY );	
			
};

#endif
