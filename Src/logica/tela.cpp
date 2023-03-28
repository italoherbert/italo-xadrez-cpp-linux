#include "tela.h"

#include <cmath>

Tela::Tela( JogoDriver* driver ) {
	this->driver = driver;
}

int Tela::getTabuleiroX() {
	return ( driver->getTelaLargura() - this->getTabuleiroDIM() ) / 2;	
}

int Tela::getTabuleiroY() {
	int infoPAlt = driver->getInfoPainelAltura();
	return ( driver->getTelaAltura() - infoPAlt / 2 - this->getTabuleiroDIM() ) / 2 + infoPAlt / 2;
}

int Tela::getTabuleiroDIM() {
	return 8 * this->getCelulaDIM();
}

int Tela::getCelulaX( int i ) {
	return this->getTabuleiroX() + ( this->getCelulaDIM() * i );
}

int Tela::getCelulaY( int j ) {
	return this->getTabuleiroY() + ( this->getCelulaDIM() * j );
}

int Tela::getCelulaDIM() {
	int l = driver->getTelaLargura();
	int a = driver->getTelaAltura();
	int min = ( l < a ? l : a );
	
	return (int) round( driver->getFatorCelulaDIM() * min );
}

int Tela::getX( int posX ) {
	int tx = this->getTabuleiroX();
	int cd = this->getCelulaDIM();
	
	return tx + ( posX * cd ) + ( cd / 2 );
}

int Tela::getY( int posY ) {
	int ty = this->getTabuleiroY();
	int cd = this->getCelulaDIM();
	
	return ty + ( posY * cd ) + ( cd / 2 );
}
