#include "rei_peca_jogada.h"

#include <cstdlib>
#include <iostream>

#include "../jogada_roque.h"

void ReiPecaJogada::calculaJogadasPossiveis( PecaJogadaParams* params ) {		
	Jogo* jogo = params->getJogo();
	JogadaLista* lista = params->getJogadas();
	int posX = params->getPosX();
	int posY = params->getPosY();
	bool isComp = params->getIsComp();
	bool incluirRoque = params->getIsIncluirRoque();
	Pecas* pecas = params->getPecas();
	
	Peca* peca = pecas->getPeca( posX, posY );
				
	for( int i = -1; i <= 1; i++ ) {
		for( int j = -1; j <= 1; j++ ) {
			if ( i == 0 && j == 0 )
				continue;
				
			int x = posX + i;
			int y = posY + j;				
			if ( jogo->isPosicaoValida( x, y ) )
				jogo->addJogada( lista, pecas, x, y, isComp );							
		}
	}			
		
	if ( peca->getMoveuContador() == 0 && !incluirRoque ) {
		Peca* jogPecas[ JogoConstantes::N_PECAS ];
		Peca* compPecas[ JogoConstantes::N_PECAS ];
			
		jogo->copia_pecas( pecas, jogPecas, compPecas );
				
		bool xeque = jogo->isCapturaOutraPeca( ( isComp ? jogPecas : compPecas ), jogPecas, compPecas, posX, posY, !isComp );
		if ( !xeque ) {						
			if ( isComp ) {			
				Peca* torreEsq = pecas->getComputadorPeca( 0, 0 );
				if ( torreEsq != NULL ) {							
					if ( torreEsq->getMoveuContador() == 0 ) {
						Peca* cavalo = pecas->getPeca( 1, 0 );
						Peca* bispo = pecas->getPeca( 2, 0 );
						Peca* rainha = pecas->getPeca( 3, 0 );
						if ( cavalo == NULL && bispo == NULL && rainha == NULL ) {																											
							bool isCap = jogo->isCapturaOutraPeca( jogPecas, jogPecas, compPecas, 1, 0, false );
							if ( isCap == false ) {						
								isCap = jogo->isCapturaOutraPeca( jogPecas, jogPecas, compPecas, 2, 0, false );
								if( isCap == false ) {
									isCap = jogo->isCapturaOutraPeca( jogPecas, jogPecas, compPecas, 3, 0, false );
									if ( isCap == false )								
										lista->addJogada( new JogadaRoque( 2, 0, 3, 0, NULL, peca, torreEsq ) );																																							
								}
							}							
						}
					}
				}
				
				Peca* torreDir = pecas->getComputadorPeca( 7, 0 );
				if ( torreDir != NULL ) {			
					if ( torreDir->getMoveuContador() == 0 ) {				
						Peca* bispo = pecas->getPeca( 5, 0 );
						Peca* cavalo = pecas->getPeca( 6, 0 );
						if ( cavalo == NULL && bispo == NULL ) {
							bool isCap = jogo->isCapturaOutraPeca( jogPecas, jogPecas, compPecas, 5, 0, false );
							if ( isCap == false ) {
								isCap = jogo->isCapturaOutraPeca( jogPecas, jogPecas, compPecas, 6, 0, false );
								if ( isCap == false ) {																	
									lista->addJogada( new JogadaRoque( 6, 0, 5, 0, NULL, peca, torreDir ) );
								}
							}
						}
					}			
				}		
			} else {												
				Peca* torreEsq = pecas->getJogadorPeca( 0, 7 );
				if ( torreEsq != NULL ) {			
					if ( torreEsq->getMoveuContador() == 0 ) {
						Peca* cavalo = pecas->getPeca( 1, 7 );
						Peca* bispo = pecas->getPeca( 2, 7 );
						Peca* rainha = pecas->getPeca( 3, 7 );
						if ( cavalo == NULL && bispo == NULL && rainha == NULL ) {												
							bool isCap = jogo->isCapturaOutraPeca( compPecas, jogPecas, compPecas, 1, 7, true );
							if ( isCap == false ) {												
								isCap = jogo->isCapturaOutraPeca( compPecas, jogPecas, compPecas, 2, 7, true );
								if( isCap == false ) {
									isCap = jogo->isCapturaOutraPeca( compPecas, jogPecas, compPecas, 3, 7, true );
									if ( isCap == false )
										lista->addJogada( new JogadaRoque( 2, 7, 3, 7, NULL, peca, torreEsq ) );
								}													
							}												
						}
					}
				}
				Peca* torreDir = pecas->getJogadorPeca( 7, 7 );
				if ( torreDir != NULL ) {			
					if ( torreDir->getMoveuContador() == 0 ) {
						Peca* bispo = pecas->getPeca( 5, 7 );
						Peca* cavalo = pecas->getPeca( 6, 7 );
						if ( cavalo == NULL && bispo == NULL ) {
							bool isCap = jogo->isCapturaOutraPeca( compPecas, jogPecas, compPecas, 5, 7, true );
							if( isCap == false ) {
								isCap = jogo->isCapturaOutraPeca( compPecas, jogPecas, compPecas, 6, 7, true );
								if ( isCap == false )
									lista->addJogada( new JogadaRoque( 6, 7, 5, 7, NULL, peca, torreDir ) );
							}
						}					
					}
				}
			}
		}
		jogo->deleta_pecas( jogPecas );
		jogo->deleta_pecas( compPecas );
	}	
}

