#include "peao_peca_jogada.h"

#include <cstdlib>
#include <iostream>

#include "../jogada_en_passant.h"
#include "../jogada_lista.h"
#include "../jogo.h"

void PeaoPecaJogada::calculaJogadasPossiveis( PecaJogadaParams* params ) {		
	Jogo* jogo = params->getJogo();
	JogadaLista* lista = params->getJogadas();
	int posX = params->getPosX();
	int posY = params->getPosY();
	bool isComp = params->getIsComp();
	Pecas* pecas = params->getPecas();
	
	Peca* peca = pecas->getPeca( posX, posY );	
	if ( isComp != peca->isDeComp() ) 
		return;

	int x = posX;
	int y = posY + ( isComp ? 1 : -1 );
		
	if ( jogo->isPosicaoValida( x, y ) ) {	
		peca = pecas->getPeca( x, y );				
		if ( peca == NULL )	{		
			lista->addJogada( x, y, NULL );						
		
			bool eh_primeira_jogada = ( isComp ? posY == 1 : posY == 6 );
			if ( eh_primeira_jogada ) {
				y += ( isComp ? 1 : -1 );
				
				if ( jogo->isPosicaoValida( x, y ) ) {			
					peca = pecas->getPeca( x, y );
					if ( peca == NULL )
						lista->addJogada( x, y, NULL );
				}
			}
		}
	}
	
	y = posY + ( isComp ? 1 : -1 );
	x = posX - 1;
				
	if ( jogo->isPosicaoValida( x, y ) ) {			
		if ( isComp ) {			
			peca = pecas->getJogadorPeca( x, y );		
			if ( peca != NULL )
				lista->addJogada( x, y, peca );
		} else {
			peca = pecas->getComputadorPeca( x, y );
			if ( peca != NULL)
				lista->addJogada( x, y, peca );
		}
	}
		
	x = posX + 1;
			
	if ( jogo->isPosicaoValida( x, y ) ) {			
		if ( isComp ) {			
			peca = pecas->getJogadorPeca( x, y );		
			if ( peca != NULL )
				lista->addJogada( x, y, peca );
		} else {
			peca = pecas->getComputadorPeca( x, y );
			if ( peca != NULL )
				lista->addJogada( x, y, peca );
		}
	}

	if ( isComp ) {
		if ( posY == 4 ) {
			if ( posX > 0 ) {
				Peca* jogPecaEsq = pecas->getJogadorPeca( posX-1, posY );
				if ( jogPecaEsq != NULL )
					if ( jogPecaEsq->getTipo() == Jogo::PEAO && jogPecaEsq->getMoveuContador() == 1 )
						if ( pecas->getPeca( posX-1, posY+1 ) == NULL )
							lista->addJogada( new JogadaEnPassant( posX-1, posY+1, jogPecaEsq ) );
			}
			if ( posX < 7 ) {
				Peca* jogPecaDir = pecas->getJogadorPeca( posX+1, posY );
				if ( jogPecaDir != NULL )
					if ( jogPecaDir->getTipo() == Jogo::PEAO && jogPecaDir->getMoveuContador() == 1 )
						if ( pecas->getPeca( posX+1, posY+1 ) == NULL )
							lista->addJogada( new JogadaEnPassant( posX+1, posY+1, jogPecaDir ) );
			}
		}
	} else {
		if ( posY == 3 ) {
			if ( posX > 0 ) {
				Peca* compPecaEsq = pecas->getComputadorPeca( posX-1, posY );
				if ( compPecaEsq != NULL )
					if ( compPecaEsq->getTipo() == Jogo::PEAO && compPecaEsq->getMoveuContador() == 1 )
						if ( pecas->getPeca( posX-1, posY - 1 ) == NULL )
							lista->addJogada( new JogadaEnPassant( posX-1, posY-1, compPecaEsq ) );
			}
			if ( posX < 7 ) {
				Peca* compPecaDir = pecas->getComputadorPeca( posX+1, posY );
				if ( compPecaDir != NULL )
					if ( compPecaDir->getTipo() == Jogo::PEAO && compPecaDir->getMoveuContador() == 1 )
						if ( pecas->getPeca( posX+1, posY-1 ) == NULL )
							lista->addJogada( new JogadaEnPassant( posX+1, posY-1, compPecaDir ) );
			}
		}
	}

}

