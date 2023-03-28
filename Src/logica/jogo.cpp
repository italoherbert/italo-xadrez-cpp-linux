#include "jogo.h"

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "jogada_roque.h"
#include "jogo_pecas.h"

Jogo::Jogo( JogoDriver* drv ) {	
	this->drv = drv;

	tela = new Tela( drv );				
	jogadas = new JogadaLista();

	this->peaoPecaJogada = new PeaoPecaJogada();
	this->reiPecaJogada = new ReiPecaJogada();
	this->cavaloPecaJogada = new CavaloPecaJogada();
	this->torrePecaJogada = new TorrePecaJogada();
	this->bispoPecaJogada = new BispoPecaJogada();
	this->rainhaPecaJogada = new RainhaPecaJogada( torrePecaJogada, bispoPecaJogada );

	this->jogadorNivel = NIVEL_HUMANO;
	this->computadorNivel = NIVEL_NORMAL;
}

Jogo::~Jogo() {
	delete this->peaoPecaJogada;
	delete this->reiPecaJogada;
	delete this->bispoPecaJogada;
	delete this->torrePecaJogada;
	delete this->bispoPecaJogada;
	delete this->rainhaPecaJogada;
}


void Jogo::reinicia() {
	jogadorPecas[0] = new Peca( false, TORRE, 0, 7 );
	jogadorPecas[1] = new Peca( false, CAVALO, 1, 7 );
	jogadorPecas[2] = new Peca( false, BISPO, 2, 7 );
	jogadorPecas[3] = new Peca( false, RAINHA, 3, 7 );
	jogadorPecas[4] = new Peca( false, REI, 4, 7 );
	jogadorPecas[5] = new Peca( false, BISPO, 5, 7 );
	jogadorPecas[6] = new Peca( false, CAVALO, 6, 7 );
	jogadorPecas[7] = new Peca( false, TORRE, 7, 7 );
	jogadorPecas[8] = new Peca( false, PEAO, 0, 6 );
	jogadorPecas[9] = new Peca( false, PEAO, 1, 6 );
	jogadorPecas[10] = new Peca( false, PEAO, 2, 6 );
	jogadorPecas[11] = new Peca( false, PEAO, 3, 6 );
	jogadorPecas[12] = new Peca( false, PEAO, 4, 6 );
	jogadorPecas[13] = new Peca( false, PEAO, 5, 6 );
	jogadorPecas[14] = new Peca( false, PEAO, 6, 6 );
	jogadorPecas[15] = new Peca( false, PEAO, 7, 6 );
	
	computadorPecas[0] = new Peca( true, TORRE, 0, 0 );
	computadorPecas[1] = new Peca( true, CAVALO, 1, 0 );
	computadorPecas[2] = new Peca( true, BISPO, 2, 0 );
	computadorPecas[3] = new Peca( true, RAINHA, 3, 0 );
	computadorPecas[4] = new Peca( true, REI, 4, 0 );
	computadorPecas[5] = new Peca( true, BISPO, 5, 0 );
	computadorPecas[6] = new Peca( true, CAVALO, 6, 0 );
	computadorPecas[7] = new Peca( true, TORRE, 7, 0 );
	computadorPecas[8] = new Peca( true, PEAO, 0, 1 );
	computadorPecas[9] = new Peca( true, PEAO, 1, 1 );
	computadorPecas[10] = new Peca( true, PEAO, 2, 1 );
	computadorPecas[11] = new Peca( true, PEAO, 3, 1 );
	computadorPecas[12] = new Peca( true, PEAO, 4, 1 );
	computadorPecas[13] = new Peca( true, PEAO, 5, 1 );
	computadorPecas[14] = new Peca( true, PEAO, 6, 1 );
	computadorPecas[15] = new Peca( true, PEAO, 7, 1 );

	for( int i = 0; i < N_PECAS; i++ ) {
		jogadorPecas[i]->setRemovida( false );
		computadorPecas[i]->setRemovida( false );
		//jogadorPecas[i]->setRemovida( i != 4 ? true : false );
		//computadorPecas[i]->setRemovida( i > 7 ? true : false );
	}

	jogadas->deletaTodasAsJogadas();

	ultPecaMov = nullptr;
	ultCompPecaMov = nullptr;
	ultJogadorPecaMov = nullptr;

	movimento = nullptr;
	
	vezComputador = false;
	
	compRoque = false;
	jogRoque = false;

	audioLigado = true;
	pausa = false;
	fim = false;
			
	compJogadasCont = 0;

	status = NAO_FIM;	
}

bool Jogo::move( int posX, int posY, int novaPosX, int novaPosY ) {
	return this->move( jogadorPecas, computadorPecas, posX, posY, novaPosX, novaPosY );
}

bool Jogo::move( Peca** jogPecas, Peca** compPecas, int posX, int posY, int novaPosX, int novaPosY ) {
	Peca* novaPos = this->getPeca( jogPecas, compPecas, novaPosX, novaPosY );	
	
	if ( novaPos != NULL )
		novaPos->setRemovida( true );	
	
	Peca* peca = this->getPeca( jogPecas, compPecas, posX, posY );
								
	if ( peca != NULL ) {		
		peca->setPosX( novaPosX );
		peca->setPosY( novaPosY );
		return true;
	}
	
	return false;
}

void Jogo::move2( Peca* p, Jogada* jog ) {
	this->move2( jogadorPecas, computadorPecas, p, jog );
}

void Jogo::move2( Peca** jogPecas, Peca** compPecas, Peca* p, Jogada* jogada ) {
	p->setAnimPosX( 0 );
	p->setAnimPosY( 0 );

	if( jogada->getTipo() == Jogada::ROQUE ) {
		JogadaRoque* jr = (JogadaRoque*)jogada;

		Peca* rei = jr->getRei();
		Peca* torre = jr->getTorre();
		int reiPosX = jr->getReiPosX();
		int reiPosY = jr->getReiPosY();
		int torrePosX = jr->getTorrePosX();
		int torrePosY = jr->getTorrePosY();

		this->registraRoque( p->isDeComp() );

		Peca* pTorre = this->getPeca( jogPecas, compPecas, torre->getPosX(), torre->getPosY() );
		pTorre->setAnimPosX( 0 );
		pTorre->setAnimPosY( 0 );

		this->move( jogPecas, compPecas, rei->getPosX(), rei->getPosY(), reiPosX, reiPosY );
		this->move( jogPecas, compPecas, torre->getPosX(), torre->getPosY(), torrePosX, torrePosY );
	} else if ( jogada->getTipo() == Jogada::EN_PASSANT ){
		int capPosX = jogada->getCaptura()->getPosX();
		int capPosY = jogada->getCaptura()->getPosY();

		Peca* capturada = this->getPeca( jogPecas, compPecas, capPosX, capPosY );
		capturada->setRemovida( true );

		this->move( jogPecas, compPecas, p->getPosX(), p->getPosY(), jogada->getPosX(), jogada->getPosY() );
	} else {
		this->move( jogPecas, compPecas, p->getPosX(), p->getPosY(), jogada->getPosX(), jogada->getPosY() );
	}

	if( p->getTipo() == PEAO )
		if( jogada->getPosY() == 0 || jogada->getPosY() == 7 )
			p->setTipo( RAINHA );
}

bool Jogo::isPossivelEstaEmXequeMateOuEmpate( Peca** jogPecas, Peca** compPecas, bool isComp ) {
	Peca* jps[ N_PECAS ];
	Peca* cps[ N_PECAS ];

	Peca* reiP = this->getPecaRei( isComp ? compPecas : jogPecas );
	for( int i = -1; i <= 1; i++ ) {
		for( int j = -1; j <= 1; j++ ) {
			if ( i == 0 && j == 0 )
				continue;

			int x = reiP->getPosX() + i;
			int y = reiP->getPosY() + j;

			if ( !this->isPosicaoValida( x, y ) )
				continue;

			this->copia_pecas( jps, cps, jogPecas, compPecas );

			this->move( jps, cps, reiP->getPosX(), reiP->getPosY(), x, y );

			if ( !this->isOutroReiEmXeque( jps, cps, !isComp ) ) {
				this->deleta_pecas( jps );
				this->deleta_pecas( cps );
				return false;
			}

			this->deleta_pecas( jps );
			this->deleta_pecas( cps );
		}
	}

	return true;
}

int Jogo::isEstaEmXequeMateOuEmpate( bool isComp ) {
	return this->isEstaEmXequeMateOuEmpate( jogadorPecas, computadorPecas, isComp );
}

int Jogo::isEstaEmXequeMateOuEmpate( Peca** jogPecas, Peca** compPecas, bool isComp ) {
	bool fim = true;
	for( int i = 0; fim && i < N_PECAS; i++ ) {
		Peca* p = ( isComp ? compPecas[i] : jogPecas[i] );
		if ( p->isRemovida() )
			continue;

		JogadaLista* lista = new JogadaLista();
		JogoPecas* pecas = new JogoPecas( this );
		pecas->setPecas( jogPecas, compPecas );

		this->calculaJogadasPossiveis( lista, pecas, p->getPosX(), p->getPosY(), p->getTipo(), isComp, true );
		this->filtraJogadas( lista, jogPecas, compPecas, p->getPosX(), p->getPosY(), isComp );

		if ( lista->getTam() > 0 )
			fim = false;

		delete lista;
		delete pecas;
	}

	if ( fim ) {
		bool isXeque = this->isOutroReiEmXeque( jogPecas, compPecas, !isComp );
		if ( isXeque ) {
			if ( isComp )
				return JOGADOR_VENCEU;
			return COMPUTADOR_VENCEU;
		} else {
			if ( isComp == vezComputador )
				return EMPATE;
		}
	}
	return NAO_FIM;
}


bool Jogo::isOutroReiEmXeque( bool isComp ) {
	return this->isOutroReiEmXeque( jogadorPecas, computadorPecas, isComp );
}

bool Jogo::isOutroReiEmXeque( Peca** jogPecas, Peca** compPecas, bool isComp ) {
	for( int i = 0; i < N_PECAS; i++ ) {
		Peca* peca = ( isComp ? compPecas[ i ] : jogPecas[ i ] );
		if ( peca->isRemovida() )
			continue;

		JogadaLista* lista = new JogadaLista();

		JogoPecas* jogoPecas = new JogoPecas( this );
		jogoPecas->setPecas( jogPecas, compPecas );

		this->calculaJogadasPossiveis( lista, jogoPecas, peca->getPosX(), peca->getPosY(), peca->getTipo(), isComp, true );

		int tam = lista->getTam();
		for( int j = 0; j < tam; j++ ) {
			Jogada* jogada = lista->getJogada( j );
			if( jogada->getCaptura() != NULL ) {
				if ( jogada->getCaptura()->getTipo() == REI ) {
					delete lista;
					delete jogoPecas;

					return true;
				}
			}
		}

		delete lista;
		delete jogoPecas;
	}

	return false;
}

bool Jogo::isSomenteORei( Peca** pecas ) {
	for( int i = 0; i < N_PECAS; i++ ) {
		Peca* p = this->getPeca( pecas, i );
		if ( p == NULL )
			continue;

		if ( p->getTipo() != REI )
			return false;
	}
	return true;
}

bool Jogo::isCapturaOutraPeca( Peca** outras,
			Peca** jogPecas, Peca** compPecas,
			int posX, int posY, bool isComp ) {
			
	Peca* p = this->capturaOutraPeca( outras, jogPecas, compPecas, posX, posY, isComp, true );
	return ( p != NULL );					
}

Peca* Jogo::capturaOutraPeca( Peca** outras,
			Peca** jogPecas, Peca** compPecas,
			int posX, int posY, bool isComp ) {

	return this->capturaOutraPeca( outras, jogPecas, compPecas, posX, posY, isComp, true );
}

bool Jogo::isCapturaOutraPeca( Peca** outras,
			Peca** jogPecas, Peca** compPecas,
			int posX, int posY, bool isComp, bool incluirRei ) {
			
	Peca* p = this->capturaOutraPeca( outras, jogPecas, compPecas, posX, posY, isComp, incluirRei );
	return ( p != NULL );					
}

Peca* Jogo::capturaOutraPeca( Peca** outras,
			Peca** jogPecas, Peca** compPecas,
			int posX, int posY, bool isComp, bool incluirRei ) {

	for( int i = 0; i < N_PECAS; i++ ) {
		Peca* peca = outras[ i ];				
		if ( peca->isRemovida() )
			continue;
			
		if ( !incluirRei )	
			if ( peca->getTipo() == Jogo::REI )
				continue;
			
		if ( peca->getPosX() == posX && peca->getPosY() == posY )																										
			continue;
			
		if ( peca->getTipo() == Jogo::PEAO ) {
			int y = peca->getPosY() + ( isComp ? 1 : -1 );

			int x = peca->getPosX() - 1;
			if ( this->isPosicaoValida( x, y ) )			
				if ( x == posX && y == posY )
					return peca;
					
			x = peca->getPosX() + 1;
			if ( this->isPosicaoValida( x, y ) )
				if ( x == posX && y == posY )
					return peca;					
		} else {								
			JogadaLista* lista = new JogadaLista();	
			
			JogoPecas* jpecas = new JogoPecas( this );
			jpecas->setPecas( jogPecas, compPecas );
																	
			this->calculaJogadasPossiveis( lista, jpecas, peca->getPosX(), peca->getPosY(), peca->getTipo(), isComp, true );
			
			int tam = lista->getTam();
			for( int j = 0; j < tam; j++ ) {			
				Jogada* jogada = lista->getJogada( j );			
				
				if ( jogada->getPosX() == posX && jogada->getPosY() == posY ) {									
					delete lista;
					delete jpecas;
						
					return peca;
				}
			}			
			
			delete lista;
			delete jpecas;
		}	
	
	}
		
	return NULL;				
}

bool Jogo::verificaSeJogadaValida( Peca** jogPecas, Peca** compPecas, int posX1, int posY1, int posX2, int posY2 ) {
	Peca* peca = this->getPeca( jogPecas, compPecas, posX1, posY1 );
	if ( peca == NULL )
		return false;

	JogadaLista* lista = new JogadaLista();
	JogoPecas* jogoPecas = new JogoPecas( this );
	jogoPecas->setPecas( jogPecas, compPecas );

	this->calculaJogadasPossiveis( lista, jogoPecas, peca->getPosX(), peca->getPosY(), peca->getTipo(), peca->isDeComp(), false );
	this->filtraJogadas( lista, jogPecas, compPecas, peca->getPosX(), peca->getPosY(), peca->isDeComp() );

	int tam = lista->getTam();

	bool valida = false;
	for( int i = 0; !valida && i < tam; i++ ) {
		Jogada* jog = lista->getJogada( i );
		if ( jog->getPosX() == posX2 && jog->getPosY() == posY2 )
			valida = true;
	}

	delete lista;
	delete jogoPecas;

	return valida;
}

void Jogo::calculaJogadasPossiveis( JogadaLista* lista, Pecas* pecas, int posX, int posY, int tipo, bool isComp, bool inclurRoque ) {
	PecaJogadaParams* params = new PecaJogadaParams( this, lista, pecas, posX, posY, isComp, inclurRoque );
	switch( tipo ) {
		case Jogo::PEAO:
			peaoPecaJogada->calculaJogadasPossiveis( params );
			break;
		case Jogo::REI:
			reiPecaJogada->calculaJogadasPossiveis( params );
			break;
		case Jogo::CAVALO:
			cavaloPecaJogada->calculaJogadasPossiveis( params );
			break;
		case Jogo::TORRE:
			torrePecaJogada->calculaJogadasPossiveis( params );
			break;
		case Jogo::BISPO:
			bispoPecaJogada->calculaJogadasPossiveis( params );
			break;
		case Jogo::RAINHA:
			rainhaPecaJogada->calculaJogadasPossiveis( params );
			break;
	}

	delete params;
}

void Jogo::filtraJogadas(
			JogadaLista* lista,
			Peca** jogPecas,
			Peca** compPecas,
			int posX, int posY, bool isComp ) {

	Peca* jps[ N_PECAS ];
	Peca* cps[ N_PECAS ];

	JogadaLista* jogadas = new JogadaLista();

	int tam = lista->getTam();
	for( int i = 0; i < tam; i++ ) {
		Jogada* jogada = lista->getJogada( i );

		this->copia_pecas( jps, cps, jogPecas, compPecas );

		this->move( jps, cps, posX, posY, jogada->getPosX(), jogada->getPosY() );

		if ( !this->isOutroReiEmXeque( jps, cps, !isComp ) )
			jogadas->addJogada( jogada->nova() );

		this->deleta_pecas( jps );
		this->deleta_pecas( cps );
	}

	jogadas->copiaPara( lista );

	delete jogadas;
}

bool Jogo::addJogada( JogadaLista* lista, Pecas* pecas, int posX, int posY, bool isComp ) {					
	Peca* peca = pecas->getPeca( posX, posY );	
	if ( peca == NULL ) {
		lista->addJogada( posX, posY, NULL );
	} else {
		if ( isComp ) {
			if ( !peca->isDeComp() )				
				lista->addJogada( posX, posY, peca );
		} else {
			if ( peca->isDeComp() )
				lista->addJogada( posX, posY, peca );
		}
		return true;	
	}	
	return false;
}

Peca* Jogo::getPeca( Peca** jogPecas, Peca** compPecas, int posX, int posY ) {
	Peca* p = this->getPeca( jogPecas, posX, posY );
	if ( p == NULL )
		p = this->getPeca( compPecas, posX, posY );		
	return p;
}
		
Peca* Jogo::getPeca( Peca** pecas, int posX, int posY ) {
	for( int i = 0; i < N_PECAS; i++ ) {
		Peca* p = pecas[ i ];
		if ( p->isRemovida() )
			continue;
			
		if ( p->getPosX() == posX && p->getPosY() == posY )
			return p;
	}
	return NULL;
}
		
Peca* Jogo::getPeca( Peca** vetor, int indice ) {
	Peca* p = vetor[ indice ];
	if ( p->isRemovida() )
		return NULL;
	return p;
}

Peca** Jogo::getJogadorPecas() {
	return jogadorPecas;
}

Peca** Jogo::getComputadorPecas() {
	return computadorPecas;
}

int Jogo::isPosicaoValida( int posX, int posY ) {
	return ( posX >= 0 && posX < 8 && posY >= 0 && posY < 8 );
}
		
Peca* Jogo::getJogadorPeca( int posX, int posY ) {
	for( int i = 0; i < N_PECAS; i++ )	
		if ( !jogadorPecas[ i ]->isRemovida() )
			if ( jogadorPecas[ i ]->getPosX() == posX && jogadorPecas[ i ]->getPosY() == posY )
				return jogadorPecas[ i ];	
	return NULL;
}

Peca* Jogo::getComputadorPeca( int posX, int posY ) {
	for( int i = 0; i < N_PECAS; i++ )
		if ( !computadorPecas[ i ]->isRemovida() )
			if ( computadorPecas[ i ]->getPosX() == posX && computadorPecas[ i ]->getPosY() == posY )
				return computadorPecas[ i ];
			
	return NULL;
}

Peca* Jogo::getPeca( int posX, int posY ) {
	Peca* peca = this->getJogadorPeca( posX, posY );
	if ( peca == NULL )
		return this->getComputadorPeca( posX, posY );
	return peca;
}

Jogada* Jogo::getJogada( int posX, int posY ) {
	JogadaLista* lista = this->getJogadasPossiveis();
	int tam = lista->getTam();
	for( int i = 0; i < tam; i++ ) {	
		Jogada* jogada = lista->getJogada( i );
		if ( jogada->getPosX() == posX && jogada->getPosY() == posY )
			return jogada;
	}
	return NULL;
}

void Jogo::registraRoque( bool isComp ) {
	if ( isComp )
		compRoque = true;
	else jogRoque = true;
}

Peca* Jogo::getPecaPeaoMeioEsq( Peca** vetor ) {
	Peca* p = vetor[ PECA_PEAO_MEIO_ESQ_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaPeaoMeioDir( Peca** vetor ) {
	Peca* p = vetor[ PECA_PEAO_MEIO_DIR_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaCavaloEsq( Peca** vetor ) {
	Peca* p = vetor[ PECA_CAVALO_ESQ_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaCavaloDir( Peca** vetor ) {
	Peca* p = vetor[ PECA_CAVALO_DIR_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaBispoEsq( Peca** vetor ) {
	Peca* p = vetor[ PECA_BISPO_ESQ_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaBispoDir( Peca** vetor ) {
	Peca* p = vetor[ PECA_BISPO_DIR_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaTorreEsq( Peca** vetor ) {
	Peca* p = vetor[ PECA_TORRE_ESQ_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaTorreDir( Peca** vetor ) {
	Peca* p = vetor[ PECA_TORRE_DIR_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaRei( bool isComp ) {
	if( isComp )
		return computadorPecas[ PECA_REI_INDICE ];
	return jogadorPecas[ PECA_REI_INDICE ];
}

Peca* Jogo::getPecaRei( Peca** vetor )  {
	return vetor[ PECA_REI_INDICE ];
}

Peca* Jogo::getJogadorPeca( int indice ) {
	return jogadorPecas[ indice ];
}

Peca* Jogo::getComputadorPeca( int indice ) {
	return computadorPecas[ indice ];
}

JogadaLista* Jogo::getJogadasPossiveis() {
	return jogadas;
}

int* Jogo::getJogadaDominioCentro( int i, bool isComp ) {
	if ( isComp )
		return jogadasCompDominioCentro[ i ];
	return jogadasJogadorDominioCentro[ i ];
}

bool Jogo::isCompRoqueFeito() {
	return compRoque;
}

bool Jogo::isJogRoqueFeito() {
	return jogRoque;
}

Tela* Jogo::getTela() {
	return tela;
}

bool Jogo::isVezComputador() {
	return vezComputador;
}	
	
void Jogo::setVezComputador( bool b ) {
	this->vezComputador = b;
}
		
Peca* Jogo::getJogadorJogadaPeca() {
	return jogadaPeca;
}

void Jogo::setJogadorJogadaPeca( Peca* peca ) {
	this->jogadaPeca = peca;
}

void Jogo::copia_pecas( Peca** novoJPs, Peca** novoCPs ) {
	this->copia_pecas( novoJPs, novoCPs, jogadorPecas, computadorPecas );
}

void Jogo::copia_pecas( Pecas* pecas, Peca** novoJPs, Peca** novoCPs ) {
	for( int i = 0; i < N_PECAS; i++ ) {
		Peca* jogador = pecas->getJogadorPeca( i );
		Peca* computador = pecas->getComputadorPeca( i );
		novoJPs[ i ] = jogador->nova();
		novoCPs[ i ] = computador->nova();
	}
}

void Jogo::copia_pecas( Peca** novoJPs, Peca** novoCPs, Peca** jps, Peca** cps ) {
	for( int i = 0; i < N_PECAS; i++ ) {
		novoJPs[ i ] = jps[ i ]->nova();
		novoCPs[ i ] = cps[ i ]->nova();
	}
}

void Jogo::deleta_pecas() {
	this->deleta_pecas( jogadorPecas );
	this->deleta_pecas( computadorPecas );
}

void Jogo::deleta_pecas( Peca** vetor ) {
	this->deleta_pecas( vetor, N_PECAS );
}

void Jogo::deleta_pecas( Peca** vetor, int tam ) {
	for( int i = 0; i < tam; i++ )
		delete vetor[i];
}

PecaMov* Jogo::getUltimoMov( bool isComp ) {
	if ( isComp )
		return ultCompPecaMov;
	return ultJogadorPecaMov;
}

PecaMov* Jogo::getUltimoMov() {
	return ultPecaMov;
}

void Jogo::setUltimoMov( PecaMov* pecaMov ) {
	if ( pecaMov->isDeComp() ) {
		ultCompPecaMov = pecaMov;
	} else {
		ultJogadorPecaMov = pecaMov;
	}
	ultPecaMov = pecaMov;
}

void Jogo::incJogadasCont( bool isComp ) {
	if ( isComp )
		compJogadasCont++;
	else jogadorJogadasCont++;
}

int Jogo::getJogadasCont( bool isComp ) {
	if ( isComp )
		return compJogadasCont;
	return jogadorJogadasCont;
}

int Jogo::getJogadaRepetidaCont( bool isComp ) {
	if ( isComp )
		return compJogadaRepetidaCont;
	return jogadorJogadaRepetidaCont;
}

void Jogo::incJogadaRepetidaCont( bool isComp ) {
	if ( isComp )
		compJogadaRepetidaCont++;
	else jogadorJogadaRepetidaCont++;
}

void Jogo::zeraJogadaRepetidaCont( bool isComp ) {
	if ( isComp )
		compJogadaRepetidaCont = 0;
	else jogadorJogadaRepetidaCont = 0;
}

int Jogo::getStatus() {
	return status;
}

void Jogo::setStatus( int status ) {
	this->status = status;
}

bool Jogo::isAudioLigado() {
	return audioLigado;
}

void Jogo::setAudioLigado( bool ligado ) {
	this->audioLigado = ligado;
}

Movimento* Jogo::getMovimento() {
	return movimento;
}

void Jogo::setMovimento( Movimento* movimento ) {
	this->movimento = movimento;
}			

int Jogo::getNivel( bool isComp ) {
	return isComp ? computadorNivel : jogadorNivel;
}

void Jogo::incNivel( bool isComp ) {
	if ( isComp ) {
		if ( computadorNivel < NIVEL_DIFICIL )
			computadorNivel++;
		else computadorNivel = NIVEL_FACIL;
	} else {
		if ( jogadorNivel < NIVEL_DIFICIL )
			jogadorNivel++;
		else jogadorNivel = NIVEL_HUMANO;
	}
}

void Jogo::setNivel( bool isComp,int nivel ) {
	if ( isComp )
		this->computadorNivel = nivel;
	else this->jogadorNivel = nivel;
}

int Jogo::getVitoriasCont( bool isComp ) {
	if ( isComp )
		return pretasVitoriasCont;
	return brancasVitoriasCont;
}

void Jogo::incVitoriasCont( bool isComp ) {
	if ( isComp )
		pretasVitoriasCont++;
	else brancasVitoriasCont++;
}

int Jogo::getEmpatesCont() {
	return empatesCont;
}

void Jogo::incEmpatesCont() {
	empatesCont++;
}

bool Jogo::isJogadorHumano() {
	return jogadorNivel == NIVEL_HUMANO;
}

bool Jogo::isPausa() {
	return pausa;
}

void Jogo::setPausa( bool pausar ) {
	this->pausa = pausar;
}

bool Jogo::isFim() {
	return fim;
}

void Jogo::setFim( bool fim ) {
	this->fim = fim;
}

JogoDriver* Jogo::getJogoDriver() {
	return drv;
}

std::string Jogo::getNivelString( int nivel ) {
	switch( nivel ) {
		case Jogo::NIVEL_HUMANO:  return "Humano";
		case Jogo::NIVEL_FACIL:   return "Fácil";
		case Jogo::NIVEL_NORMAL:  return "Normal";
		case Jogo::NIVEL_DIFICIL: return "Difícil";
	}
	return "";
}

std::string Jogo::getPecaTipoString( int tipo ) {
	switch( tipo ) {
		case Jogo::REI: return "REI";
		case Jogo::RAINHA: return "RAINHA";
		case Jogo::TORRE: return "TORRE";
		case Jogo::BISPO: return "BISPO";
		case Jogo::CAVALO: return "CAVALO";
		case Jogo::PEAO: return "PEAO";
	}
	return "DESCONHECIDO";
}

