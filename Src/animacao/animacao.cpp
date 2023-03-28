#include "animacao.h"

#include <cstdlib>

#include "../logica/jogo.h"

Animacao::Animacao( Jogo* jogo ) {
	this->jogo = jogo;
	this->pecaAnim = new PecaAnim( jogo );
}

Animacao::~Animacao() {
	delete this->pecaAnim;
}

bool Animacao::move( Movimento* movimento, int raioInc ) {
	if ( movimento->getMovimento1() != NULL ) {		
		if ( !movimento->getMovimento1()->isMoveu() ) {			
			int d2 = pecaAnim->move( movimento->getMovimento1(), raioInc );
			if ( d2 <= raioInc )			
				movimento->getMovimento1()->setMoveu( true );												
		} else {						
			if ( movimento->getMovimento2() != NULL ) {
				int d2 = pecaAnim->move( movimento->getMovimento2(), raioInc );
				if ( d2 <= raioInc )
					movimento->getMovimento2()->setMoveu( true );																									
			}			
		}
	}
	return movimento->isMoveu();
}

Movimento* Animacao::criaMovimentos( Jogada* jogada, Peca* peca ) {
	Movimento* mov = new Movimento( jogada );
	
	if ( peca->getTipo() == Jogo::CAVALO ) {
		pecaAnim->carregaMovsCavalo( mov, peca );
	} else if ( jogada->getTipo() == Jogada::ROQUE ) {
		pecaAnim->carregaMovsRoque( mov, (JogadaRoque*)jogada );
	} else {
		pecaAnim->carregaMovsPeca( mov, peca );
	}
	
	return mov;
}

