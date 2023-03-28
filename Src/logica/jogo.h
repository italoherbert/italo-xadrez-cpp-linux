
#ifndef JOGO_H
#define JOGO_H


#include "jogada/bispo_peca_jogada.h"
#include "jogada/cavalo_peca_jogada.h"
#include "jogada/peao_peca_jogada.h"
#include "jogada/rainha_peca_jogada.h"
#include "jogada/rei_peca_jogada.h"
#include "jogada/torre_peca_jogada.h"

#include "jogo_constantes.h"
#include "jogada_lista.h"
#include "movimento.h"
#include "peca.h"
#include "pecas.h"
#include "peca_mov.h"
#include "tela.h"
#include "peca_jogada_params.h"
#include "jogo_driver.h"

#include <string>

class BispoPecaJogada;
class CavaloPecaJogada;
class PeaoPecaJogada;
class ReiPecaJogada;
class RainhaPecaJogada;
class TorrePecaJogada;

class Jogo : public Pecas, public JogoConstantes {

	private:
		Tela* tela;
		
		Peca* jogadorPecas[ N_PECAS ];
		Peca* computadorPecas[ N_PECAS ];

		int jogadasCompDominioCentro[ N_JOGADAS_DOMINIO_CENTRO ][ 5 ] = {
			{ 3, 1, 3, 3, JOGADA_CENTRO_NORMAL },
			{ 6, 0, 5, 2, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 4, 1, 4, 2, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 1, 0, 2, 2, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 5, 0, 1, 4, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 4, 0, 6, 0, JOGADA_CENTRO_SE_NAO_CAPTURADA }
		};

		int jogadasJogadorDominioCentro[ N_JOGADAS_DOMINIO_CENTRO ][ 5 ] = {
			{ 3, 6, 3, 4, JOGADA_CENTRO_NORMAL },
			{ 6, 7, 5, 5, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 4, 6, 4, 5, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 1, 7, 2, 5, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 5, 7, 1, 3, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 4, 7, 6, 7, JOGADA_CENTRO_SE_NAO_CAPTURADA }
		};
				
		int pretasVitoriasCont = 0;
		int brancasVitoriasCont = 0;
		int empatesCont = 0;

		JogadaLista* jogadas;
		Peca* jogadaPeca = nullptr;
		
		PecaMov* ultPecaMov = nullptr;
		PecaMov* ultCompPecaMov = nullptr;
		PecaMov* ultJogadorPecaMov = nullptr;

		int compJogadasCont = 0;
		int compJogadaRepetidaCont = 0;

		int jogadorJogadasCont = 0;
		int jogadorJogadaRepetidaCont = 0;
				
		bool vezComputador = false;

		bool compRoque = false;
		bool jogRoque = false;

		bool audioLigado = true;
		bool pausa = false;
		bool fim = false;
		
		int jogadorNivel = NIVEL_HUMANO;
		int computadorNivel = NIVEL_NORMAL;
		int status = 0;
		
		Movimento* movimento = nullptr;

		PeaoPecaJogada* peaoPecaJogada;
		ReiPecaJogada* reiPecaJogada;
		CavaloPecaJogada* cavaloPecaJogada;
		TorrePecaJogada* torrePecaJogada;
		BispoPecaJogada* bispoPecaJogada;
		RainhaPecaJogada* rainhaPecaJogada;

		JogoDriver* drv;

		bool move( int posX, int posY, int novaPosX, int novaPosY );
		bool move( Peca** jogPecas, Peca** compPecas, int posX, int posY, int novaPosX, int novaPosY );

	public:
		Jogo( JogoDriver* drv );
		~Jogo();
		
		void reinicia();

		void filtraJogadas(
					JogadaLista* lista,
					Peca** jogPecas,
					Peca** compPecas,
					int posX, int posY, bool isComp );

		void calculaJogadasPossiveis(
				JogadaLista* lista,
				Pecas* pecas,
				int posX, int posY, int tipo, bool isComp, bool isCaptura );

		void move2( Peca* p, Jogada* jog );
		void move2( Peca** jogPecas, Peca** compPecas, Peca* p, Jogada* jogada );

		bool isCapturaOutraPeca( Peca** outras,
					Peca** jogPecas, Peca** compPecas, int posX, int posY, bool isComp );
		
		Peca* capturaOutraPeca( Peca** outras,
					Peca** jogPecas, Peca** compPecas, int posX, int posY, bool isComp );
					
		bool isCapturaOutraPeca( Peca** outras,
					Peca** jogPecas, Peca** compPecas, int posX, int posY, bool isComp, bool incluirRei );
	
		Peca* capturaOutraPeca( Peca** outras,
					Peca** jogPecas, Peca** compPecas, int posX, int posY, bool isComp, bool incluirRei );
	
		bool isOutroReiEmXeque( bool isComp );
		bool isOutroReiEmXeque( Peca** jogPecas, Peca** compPecas, bool isComp );

		int isEstaEmXequeMateOuEmpate( bool isComp );
		int isEstaEmXequeMateOuEmpate( Peca** jogPecas, Peca** compPecas, bool isComp );
		bool isPossivelEstaEmXequeMateOuEmpate( Peca** jogPecas, Peca** compPecas, bool isComp );

		bool verificaSeJogadaValida( Peca** jps, Peca** cps, int posX1, int posY1, int posX2, int posY2 );
		int isPosicaoValida( int posX, int posY );			

		bool isSomenteORei( Peca** pecas );

		bool addJogada( JogadaLista* lista, Pecas* pecas, int posX, int posY, bool isComp );					
				
		Tela* getTela();
		
		Peca* getPecaRei( bool isComp );
		
		Peca* getPecaRei( Peca** vetor );
		Peca* getPecaPeaoMeioEsq( Peca** vetor );
		Peca* getPecaPeaoMeioDir( Peca** vetor );
		Peca* getPecaCavaloEsq( Peca** vetor );
		Peca* getPecaCavaloDir( Peca** vetor );
		Peca* getPecaBispoEsq( Peca** vetor );
		Peca* getPecaBispoDir( Peca** vetor );
		Peca* getPecaTorreEsq( Peca** vetor );
		Peca* getPecaTorreDir( Peca** vetor );

		Peca* getJogadorPeca( int indice );
		Peca* getComputadorPeca( int indice );
		
		Peca* getJogadorPeca( int posX, int posY );
		Peca* getComputadorPeca( int posX, int posY );

		Peca* getPeca( int posX, int posY );
	
		Peca* getPeca( Peca** jogPecas, Peca** compPecas, int posX, int posY );
		Peca* getPeca( Peca** vetor, int posX, int posY );
		Peca* getPeca( Peca** vetor, int indice );
		
		Peca** getJogadorPecas();
		Peca** getComputadorPecas();
										
		Jogada* getJogada( int posX, int posY );
		
		JogadaLista* getJogadasPossiveis();									
		
		void registraRoque( bool isComp );
		
		void copia_pecas( Peca** novoJPs, Peca** novoCPs );
		void copia_pecas( Pecas* pecas, Peca** novoJPs, Peca** novoCPs );
		void copia_pecas( Peca** novoJPs, Peca** novoCPs, Peca** jps, Peca** cps );
		
		void deleta_pecas();
		void deleta_pecas( Pecas* pecas );
		
		void deleta_pecas( Peca** vetor );
		void deleta_pecas( Peca** vetor, int tam );

		void deleta_jogadas( JogadaLista* lista );

		bool isVezComputador();		
		void setVezComputador( bool b );

		bool isPausa();
		void setPausa( bool pausar );

		PecaMov* getUltimoMov();
		PecaMov* getUltimoMov( bool isComp );
		void setUltimoMov( PecaMov* pecaMov );

		int getJogadaRepetidaCont( bool isComp );
		void incJogadaRepetidaCont( bool isComp );
		void zeraJogadaRepetidaCont( bool isComp );

		void incJogadasCont( bool isComp );
		int getJogadasCont( bool isComp );

		Peca* getJogadorJogadaPeca();
		void setJogadorJogadaPeca( Peca* peca );

		bool isCompRoqueFeito();
		bool isJogRoqueFeito();

		int* getJogadaDominioCentro( int i, bool isComp );
						
		int getStatus();
		void setStatus( int status );

		bool isFim();
		void setFim( bool fim );
								
		Movimento* getMovimento();
		void setMovimento( Movimento* movimento );
		
		bool isAudioLigado();
		void setAudioLigado( bool b );
				
		int getNivel( bool isComp );
		void setNivel( bool isComp, int nivel );
		void incNivel( bool isComp );

		bool isJogadorHumano();

		int getVitoriasCont( bool isComp );
		void incVitoriasCont( bool isComp );

		int getEmpatesCont();
		void incEmpatesCont();
				
		JogoDriver* getJogoDriver();

		std::string getNivelString( int nivel );
		std::string getPecaTipoString( int tipo );
};

#endif
