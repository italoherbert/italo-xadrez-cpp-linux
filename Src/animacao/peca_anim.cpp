#include "peca_anim.h"

#include <cmath>

#include <iostream>
using namespace std;

PecaAnim::PecaAnim( Jogo* jogo ) {
	this->jogo = jogo;
}

int PecaAnim::move( MovimentoSimples* movSimples, int raioInc ) {
	int posX = movSimples->getPeca()->getPosX();
	int posY = movSimples->getPeca()->getPosY();
	Peca* peca = jogo->getPeca( posX, posY );							

	int x1 = jogo->getTela()->getX( movSimples->getPosX1() );
	int y1 = jogo->getTela()->getY( movSimples->getPosY1() );
	int x2 = jogo->getTela()->getX( movSimples->getPosX2() );
	int y2 = jogo->getTela()->getY( movSimples->getPosY2() );	
	double raio = movSimples->getRaio();
				
	double a = atan2( y2-y1, x2-x1 ); 
	
	int x = x1 + ( raio * cos( a ) );
	int y = y1 + ( raio * sin( a ) );										
							
	int animX = x1 - jogo->getTela()->getX( peca->getPosX() );
	int animY = y1 - jogo->getTela()->getY( peca->getPosY() );						
					
	peca->setAnimPosX( animX + ( raio * cos( a ) ) );
	peca->setAnimPosY( animY + ( raio * sin( a ) ) );	
								
	movSimples->setRaio( raio + raioInc );
	
	double d = sqrt( pow( x2-x, 2 ) + pow( y2-y, 2 ) );				
	if ( d <= raioInc ) {
		peca->setAnimPosX( x2-x1 );
		peca->setAnimPosY( y2-y1 );
	}
	return d;
}

void PecaAnim::carregaMovsCavalo( Movimento* mov, Peca* cavalo ) {
	int posX1 = cavalo->getPosX();
	int posY1 = cavalo->getPosY();
	int posX2 = mov->getJogada()->getPosX();
	int posY2 = mov->getJogada()->getPosY();
		
	if( abs( posX2 - posX1 ) == 1 ) {
		if ( posX2 > posX1 ) {
			mov->setMovimento1( new MovimentoSimples( cavalo, posX1, posY1, posX2, posY1 ) );
			mov->setMovimento2( new MovimentoSimples( cavalo, posX2, posY1, posX2, posY2 ) );
		} else {
			mov->setMovimento1( new MovimentoSimples( cavalo, posX1, posY1, posX2, posY1 ) );
			mov->setMovimento2( new MovimentoSimples( cavalo, posX2, posY1, posX2, posY2 ) );
		}
	} else {
		if ( posX2 > posX1 ) {
			mov->setMovimento1( new MovimentoSimples( cavalo, posX1, posY1, posX2, posY1 ) );
			mov->setMovimento2( new MovimentoSimples( cavalo, posX2, posY1, posX2, posY2 ) );					
		} else {
			mov->setMovimento1( new MovimentoSimples( cavalo, posX1, posY1, posX2, posY1 ) );
			mov->setMovimento2( new MovimentoSimples( cavalo, posX2, posY1, posX2, posY2 ) );
		}
	}			
}

void PecaAnim::carregaMovsRoque( Movimento* mov, JogadaRoque* jogR ) {
	int reiPosX1 = jogR->getRei()->getPosX();
	int reiPosY1 = jogR->getRei()->getPosY();
	int reiPosX2 = jogR->getReiPosX();
	int reiPosY2 = jogR->getReiPosY();
	Peca* rei = jogR->getRei();
	
	int torrePosX1 = jogR->getTorre()->getPosX();
	int torrePosY1 = jogR->getTorre()->getPosY();
	int torrePosX2 = jogR->getTorrePosX();
	int torrePosY2 = jogR->getTorrePosY();
	Peca* torre = jogR->getTorre();
		
	mov->setMovimento1( new MovimentoSimples( rei, reiPosX1, reiPosY1, reiPosX2, reiPosY2 ) );		
	mov->setMovimento2( new MovimentoSimples( torre, torrePosX1, torrePosY1, torrePosX2, torrePosY2 ) );		
}

void PecaAnim::carregaMovsPeca( Movimento* mov, Peca* peca ) {
	int posX1 = peca->getPosX();
	int posY1 = peca->getPosY();
	int posX2 = mov->getJogada()->getPosX();
	int posY2 = mov->getJogada()->getPosY();
		
	mov->setMovimento1( new MovimentoSimples( peca, posX1, posY1, posX2, posY2 ) );
	mov->setMovimento2( NULL );
}
