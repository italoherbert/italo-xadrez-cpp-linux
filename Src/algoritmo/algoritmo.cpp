
#include "algoritmo.h"

#include <cstdlib>
#include <cmath>
#include <ctime>

#include "../logica/jogo_pecas.h"

using namespace std;

Algoritmo::Algoritmo( Jogo* jogo ) {
	this->jogo = jogo;
}

bool Algoritmo::calculaMelhorJogada( int* posX, int* posY, Jogada** jogada, bool isComp ) {
	MiniMaxNo* raiz = new MiniMaxNo;
	raiz->peso = 0;
	raiz->pai = NULL;
	raiz->filhos = NULL;
	raiz->jogada = NULL;
	raiz->terminal = false;
	raiz->venceu = false;

	int nivel = jogo->getNivel( isComp );

	srand( time( NULL ) );
	MiniMaxNo* no = this->minimax( raiz, true, nivel, nivel, INT32_MIN, INT32_MAX, isComp );

	while( no->pai->pai != NULL  )
		no = no->pai;

	*posX = no->posX;
	*posY = no->posY;
	*jogada = no->jogada->nova();

	this->limpaMiniMaxArvore( &raiz );

	Peca* escolhida = jogo->getPeca( *posX, *posY );

	PecaMov* ultMov = jogo->getUltimoMov( isComp );
	if ( ultMov != nullptr ) {
		if ( ultMov->getX2() == escolhida->getPosX() && ultMov->getY2() == escolhida->getPosY() ) {
			if ( ( jogo->getJogadaRepetidaCont( isComp )+1 ) % 5 == 0 ) {
				jogo->copia_pecas( jogPecas, compPecas );

				this->sorteiaJogada( posX, posY, jogada, jogPecas, compPecas, isComp, ultMov );
				jogo->zeraJogadaRepetidaCont( isComp );

				jogo->deleta_pecas( jogPecas );
				jogo->deleta_pecas( compPecas );
			} else {
				jogo->incJogadaRepetidaCont( isComp );
			}
		} else {
			jogo->zeraJogadaRepetidaCont( isComp );
		}
	}

	escolhida->incJogadaCont();

	jogo->incJogadasCont( isComp );

	return true;
}

MiniMaxNo* Algoritmo::minimax( MiniMaxNo* no, bool isMaximizador, int iniNivel, int nivel, float alpha, float beta, bool isComp ) {
	if ( nivel <= 0 || no->terminal )
		return no;

	MiniMaxNo* minimaxNo = new MiniMaxNo;
	minimaxNo->peso = isMaximizador ? INT32_MIN : INT32_MAX;
	minimaxNo->pai = no;
	minimaxNo->jogada = NULL;
	minimaxNo->terminal = false;
	minimaxNo->venceu = false;

	MiniMaxNo* paux = minimaxNo;

	bool fim = false;
	for( int i = 0; !fim && !jogo->isFim() && i < Jogo::N_PECAS; i++ ) {
		jogo->copia_pecas( jogPecas, compPecas );
		this->efetuaJogadas( no, jogPecas, compPecas );

		Peca* p = jogo->getPeca( isComp ? compPecas : jogPecas, i );
		if ( p == NULL ) {
			jogo->deleta_pecas( jogPecas );
			jogo->deleta_pecas( compPecas );
			continue;
		}

		p = p->nova();

		JogadaLista* lista = new JogadaLista();
		JogoPecas* jogoPecas = new JogoPecas( jogo );
		jogoPecas->setPecas( jogPecas, compPecas );

		jogo->calculaJogadasPossiveis( lista, jogoPecas, p->getPosX(), p->getPosY(), p->getTipo(), isComp, true );
		jogo->filtraJogadas( lista, jogPecas, compPecas, p->getPosX(), p->getPosY(), isComp );

		jogo->deleta_pecas( jogPecas );
		jogo->deleta_pecas( compPecas );
		delete jogoPecas;

		int tam = lista->getTam();
		for( int j = 0; !fim && !jogo->isFim() && j < tam; j++ ) {
			Jogada* jog = lista->getJogada( j )->nova();

			jogo->copia_pecas( jogPecas, compPecas );
			this->efetuaJogadas( no, jogPecas, compPecas );

			bool terminal = false;
			bool venceu = false;

			float peso = 0;

			float pecaPeso = 0;
			if ( nivel == iniNivel ) {
				bool isCap = jogo->isCapturaOutraPeca(
						( isComp ? jogPecas : compPecas ),
						jogPecas, compPecas,
						p->getPosX(), p->getPosY(), !isComp );

				if ( isCap )
					pecaPeso = this->calculaPeso( p );
			}

			jogo->move2( jogPecas, compPecas, p, jog );

			int status = Jogo::NAO_FIM;

			bool isXeque = jogo->isOutroReiEmXeque( jogPecas, compPecas, isComp );
			if ( isXeque )
				status = jogo->isEstaEmXequeMateOuEmpate( jogPecas, compPecas, !isComp );

			if ( status != Jogo::NAO_FIM ) {
				terminal = true;
				if ( isComp ) {
					if ( status == Jogo::COMPUTADOR_VENCEU ) {
						venceu = true;
						peso += ( Jogo::NIVEL_DIFICIL - nivel ) * 1000;
					}
				} else {
					if ( status == Jogo::JOGADOR_VENCEU ) {
						venceu = true;
						peso += ( Jogo::NIVEL_DIFICIL - nivel ) * 1000;
					}
				}
				if ( status == Jogo::EMPATE )
					peso -= 500;
			}

			Peca* capturada = jog->getCaptura();
			if ( capturada != NULL )
				if ( capturada->getTipo() != Jogo::REI )
					peso += this->calculaPeso( capturada );

			if ( nivel == iniNivel ) {
				bool verificar = true;
				if ( pecaPeso > 0 ) {
					bool isAposMovCap = jogo->isCapturaOutraPeca(
							( isComp ? jogPecas : compPecas ),
							jogPecas, compPecas,
							jog->getPosX(), jog->getPosY(), !isComp );

					if ( !isAposMovCap ) {
						peso += pecaPeso;
						verificar = false;
					}
				}

				if ( verificar && isXeque ) {
					peso += 0.002 + p->getJogadaCont() * 0.0001;
					verificar = false;
				}

				if ( verificar && p->getTipo() == Jogo::PEAO )
					peso += ( rand() % 100 ) / 1000.0;
			}

			jogo->deleta_pecas( jogPecas );
			jogo->deleta_pecas( compPecas );

			MiniMaxNo* filho = new MiniMaxNo;
			filho->jogada = jog;
			filho->posX = p->getPosX();
			filho->posY = p->getPosY();
			filho->peso = no->peso + ( isMaximizador ? peso : -peso );
			filho->nivel = nivel;
			filho->terminal = terminal;
			filho->venceu = venceu;
			filho->pai = no;
			filho->filhos = NULL;

			MiniMaxNoLista* novo = new MiniMaxNoLista;
			novo->no = filho;
			novo->prox = NULL;
			if ( no->filhos == NULL ) {
				no->filhos = novo;
			} else {
				novo->prox = no->filhos;
				no->filhos = novo;
			}

			if ( venceu ) {
				minimaxNo = filho;
				fim = true;
				continue;
			}

			MiniMaxNo* no2 = this->minimax( filho, !isMaximizador, iniNivel, nivel-1, alpha, beta, !isComp );
			if ( isMaximizador ) {
				if ( no2->peso > minimaxNo->peso )
					minimaxNo = no2;

				if ( minimaxNo->peso > alpha )
					alpha = minimaxNo->peso;
				if ( beta <= alpha )
					fim = true;
			} else {
				if ( no2->peso < minimaxNo->peso )
					minimaxNo = no2;

				if ( minimaxNo->peso < beta )
					beta = minimaxNo->peso;
				if ( beta <= alpha )
					fim = true;
			}
		}

		delete lista;
		delete p;
	}

	if ( minimaxNo == paux ) {
		minimaxNo->peso = 0;
	} else {
		delete paux;
	}

	return minimaxNo;
}

float Algoritmo::estadoAtualSomaPesos( Peca** jps, Peca** cps, bool isComp ) {
	float somaJog = 0;
	float somaOutroJog = 0;
	for( int i = 0; i < Jogo::N_PECAS; i++ ) {
		Peca* p = jogo->getPeca( isComp ? cps : jps, i );
		if ( p == NULL )
			continue;

		somaJog += this->calculaPeso( p );
	}

	for( int i = 0; i < Jogo::N_PECAS; i++ ) {
		Peca* p = jogo->getPeca( isComp ? jps : cps, i );
		if ( p == NULL )
			continue;

		somaOutroJog += this->calculaPeso( p );
	}

	return somaJog - somaOutroJog;
}

void Algoritmo::limpaMiniMaxArvore( MiniMaxNo** no ) {
	if ( *no == NULL )
		return;

	MiniMaxNoLista* perc = (*no)->filhos;
	while( perc != NULL ) {
		MiniMaxNoLista* aux = perc;
		perc = perc->prox;
		this->limpaMiniMaxArvore( &aux->no );
		delete aux;
	}

	if ( (*no)->jogada != NULL )
		delete (*no)->jogada;
	delete *no;
}

void Algoritmo::efetuaJogadas( MiniMaxNo* no, Peca** jps, Peca** cps) {
	MiniMaxNo* perc = no;
	MiniMaxNoLista* raiz = NULL;

	while( perc != NULL ) {
		MiniMaxNoLista* novo = new MiniMaxNoLista;
		novo->no = perc;
		novo->prox = NULL;

		if ( raiz == NULL ) {
			raiz = novo;
		} else {
			novo->prox = raiz;
			raiz = novo;
		}

		perc = perc->pai;
	}

	while( raiz != NULL ) {
		if ( raiz->no->pai != NULL ) {
			int posX = raiz->no->posX;
			int posY = raiz->no->posY;
			Peca* p = jogo->getPeca( jogPecas,  compPecas, posX, posY );
			jogo->move2( jps, cps, p, raiz->no->jogada );
		}

		MiniMaxNoLista* aux = raiz;
		raiz = raiz->prox;
		delete aux;
	}

}

float Algoritmo::calculaPeso( Peca* peca ) {
	return this->calculaPeso( peca->getTipo() );
}

float Algoritmo::calculaPeso( int tipo ) {
	float peso = 0;
	switch( tipo ) {
		case Jogo::REI:     peso = 20;  break;
		case Jogo::RAINHA:  peso = 10;   break;
		case Jogo::TORRE:   peso = 6;   break;
		case Jogo::BISPO:   peso = 4;   break;
		case Jogo::CAVALO:  peso = 3;   break;
		case Jogo::PEAO:    peso = 2;  break;
	}
	return peso;
}

bool Algoritmo::sorteiaJogada(
		int* posX, int* posY, Jogada** jogada,
		Peca** jps,
		Peca** cps,
		bool isComp,
		PecaMov* ultMov ) {

	Peca* pecasParaSortear[ Jogo::N_PECAS ];

	int pecasParaSortearCont = 0;
	for( int i = 0; i < Jogo::N_PECAS; i++ ) {
		Peca* p = jogo->getPeca( isComp ? cps : jps, i );
		if ( p == NULL )
			continue;

		if ( ultMov != NULL )
			if ( p->getPosX() == ultMov->getX2() && p->getPosY() == ultMov->getY2() )
				continue;

		bool isCap = jogo->isCapturaOutraPeca( ( isComp ? jps : cps ), jps, cps, p->getPosX(), p->getPosY(), !isComp );
		if ( isCap )
			continue;

		JogadaLista* lista = new JogadaLista();

		JogoPecas* pecas = new JogoPecas( jogo );
		pecas->setPecas( jps, cps );

		jogo->calculaJogadasPossiveis( lista, pecas, p->getPosX(), p->getPosY(), p->getTipo(), isComp, false );
		jogo->filtraJogadas( lista, jps, cps, p->getPosX(), p->getPosY(), isComp );

		if ( lista->getTam() > 0 ) {
			Jogada* jog = this->sorteiaPecaJogada( p, jps, cps, isComp );
			if ( jog != NULL ) {
				pecasParaSortear[ pecasParaSortearCont++ ] = p;
				delete jog;
			}
		}

		delete pecas;
		delete lista;
	}

	bool sorteou = false;

	if ( pecasParaSortearCont > 0 ) {
		srand( time( NULL ) );
		int indice = (int)round( rand() % pecasParaSortearCont );

		Peca* p = pecasParaSortear[ indice ];
		*jogada = this->sorteiaPecaJogada( p, jps, cps, isComp );
		*posX = p->getPosX();
		*posY = p->getPosY();
		sorteou = true;
	}

	jogo->deleta_pecas( pecasParaSortear, pecasParaSortearCont );

	return sorteou;
}

Peca* Algoritmo::sorteiaPeca( Peca** jps, Peca** cps, bool isComp ) {
	Peca* vet[ Jogo::N_PECAS ];
	int vet_tam = 0;
	for( int i = 0; i < Jogo::N_PECAS; i++ )  {
		Peca* p = jogo->getPeca( isComp ? cps : jps, i );
		if ( p == NULL )
			continue;

		JogadaLista* lista = new JogadaLista();

		JogoPecas* pecas = new JogoPecas( jogo );
		pecas->setPecas( jps, cps );

		jogo->calculaJogadasPossiveis( lista, pecas, p->getPosX(), p->getPosY(), p->getTipo(), isComp, false );
		jogo->filtraJogadas( lista, jps, cps, p->getPosX(), p->getPosY(), isComp );

		if ( lista->getTam() > 0 ) {
			Jogada* jog = this->sorteiaPecaJogada( p, jps, cps, isComp );
			if ( jog != NULL ) {
				vet[ vet_tam++ ] = p;
				delete jog;
			}
		}

		delete pecas;
		delete lista;
	}

	Peca* sorteada = NULL;

	srand( time( NULL ) );
	if ( vet_tam > 0 )
		sorteada = vet[ (int)round( rand() % vet_tam ) ]->nova();

	jogo->deleta_pecas( vet, vet_tam );

	return sorteada;
}

Jogada* Algoritmo::sorteiaPecaJogada( Peca* peca, Peca* jps[ Jogo::N_PECAS ], Peca* cps[ Jogo::N_PECAS ], bool isComp ) {
	JogadaLista* lista = new JogadaLista();

	JogoPecas* pecas = new JogoPecas( jogo );
	pecas->setPecas( jps, cps );

	jogo->calculaJogadasPossiveis( lista, pecas, peca->getPosX(), peca->getPosY(), peca->getTipo(), isComp, false );
	jogo->filtraJogadas( lista, jps, cps, peca->getPosX(), peca->getPosY(), isComp );

	JogadaLista* lista2 = new JogadaLista();

	for( int i = 0; i < lista->getTam(); i++ ) {
		Jogada* jog = lista->getJogada( i );
		bool isCap = jogo->isCapturaOutraPeca( ( isComp ? jps : cps ), jogPecas, compPecas, jog->getPosX(), jog->getPosY(), !isComp );
		if ( !isCap )
			lista2->addJogada( jog->nova() );
	}

	srand( time( NULL ) );

	Jogada* jog = NULL;
	if ( lista2->getTam() > 0 ) {
		jog = lista2->getJogada( (int)round( rand() % lista2->getTam() ) )->nova();
	} else if ( lista->getTam() > 0 ){
		jog = lista->getJogada( (int)round( rand() % lista->getTam() ) )->nova();
	}

	delete pecas;
	delete lista;
	delete lista2;

	return jog;
}

bool Algoritmo::tentaDominioDoCentro( int* posX, int* posY, Jogada** jogada, Peca** jps, Peca** cps, bool isComp ) {
	bool jogou = false;
	for( int i = 0; !jogou && i < Jogo::N_JOGADAS_DOMINIO_CENTRO; i++ ) {
		int* jog = jogo->getJogadaDominioCentro( i, isComp );
		int px1 = jog[ 0 ];
		int py1 = jog[ 1 ];
		int px2 = jog[ 2 ];
		int py2 = jog[ 3 ];
		int verifCap = jog[ 4 ];
		Peca* p = jogo->getPeca( isComp ? cps : jps, px1, py1 );
		if ( p != NULL ) {
			if ( p->getMoveuContador() == 0 ) {
				bool isJogadaValida = jogo->verificaSeJogadaValida( jps, cps, px1, py1, px2, py2 );
				if ( !isJogadaValida )
					continue;

				if ( verifCap ) {
					bool isCap = jogo->isCapturaOutraPeca( isComp ? jps : cps, jps, cps, px2, py2, !isComp );
					if ( isCap )
						continue;
				}

				*posX = px1;
				*posY = py1;

				if ( p->getTipo() == Jogo::REI && abs( px2 - p->getPosX() ) > 1 ) {
					Peca* rei = jogo->getPecaRei( isComp ? compPecas : jogPecas );
					if ( px2 > p->getPosX() ) {
						Peca* torre = jogo->getPecaTorreDir( isComp ? compPecas : jogPecas );
						*jogada = new JogadaRoque( 6, rei->getPosY(), 5, torre->getPosY(), NULL, rei, torre );
					} else {
						Peca* torre = jogo->getPecaTorreEsq( isComp ? compPecas : jogPecas );
						*jogada = new JogadaRoque( 2, rei->getPosY(), 3, torre->getPosY(), NULL, rei, torre );
					}
				} else {
					Peca* p2 = jogo->getPeca( jps, px2, py2 );
					*jogada = new Jogada( px2, py2, p2, Jogada::NORMAL );
				}

				jogou = true;
			}
		}
	}
	return jogou;
}
