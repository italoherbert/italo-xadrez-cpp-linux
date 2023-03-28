
#include "jogo_grafico_controlador.h"

#include <cmath>
#include <chrono>

using namespace std::chrono;

#include "../grafico/audio_ligado_desenho.h"
#include "../logica/jogada_roque.h"

JogoGraficoControlador::JogoGraficoControlador( Sistema* sistema ) {
	this->sistema = sistema;
	this->pecaSelecionada = NULL;
	this->mensagemDelay = -1;
}

void JogoGraficoControlador::mousePressionado( int x, int y ) {
	Jogo* jogo = sistema->getJogo();
	GUI* gui = sistema->getGUI();
	JogoAudio* audio = sistema->getJogoAudio();
	JogoGrafico* jogoGrafico = sistema->getJogoGrafico();
	Animacao* animacao = sistema->getAnimacao();

	AudioLigadoDesenho* ald = jogoGrafico->getAudioLigadoDesenho();
	if ( ald->isMouseEmAudioBT( x, y ) ) {
		jogo->setAudioLigado( !jogo->isAudioLigado() );
		if ( jogo->isAudioLigado() ) {
			audio->resumeMusica();
		} else {
			audio->pauseMusica();
		}		 
	}

	if ( jogo->getStatus() != Jogo::NAO_FIM ) {
		jogo->setFim( true );
		return;
	}

	if ( !jogo->isJogadorHumano() )
		return;
	if ( jogo->getMovimento() != NULL )
		return;

	if ( !jogo->isPausa() ) {
		int tx = jogo->getTela()->getTabuleiroX();
		int ty = jogo->getTela()->getTabuleiroY();
		int td = jogo->getTela()->getTabuleiroDIM();
		int cd = jogo->getTela()->getCelulaDIM();			
	
		if( x >= tx && x < tx+td && y >= ty && y < ty+td ) {
			int posX = ( x - tx ) / cd;
			int posY = ( y - ty ) / cd;			
			
			if ( pecaSelecionada != NULL ) {			
				Peca* p = jogo->getPeca( posX, posY );
				if ( p != NULL ) {
					if ( !p->isIgual( pecaSelecionada ) && p->isDeComp() == jogo->isVezComputador() ) {
						jogo->getJogadasPossiveis()->deletaTodasAsJogadas();
						jogo->setJogadorJogadaPeca( NULL );
						pecaSelecionada = NULL;
					}
				}
			}

			if ( !jogo->isVezComputador() ) {
				if ( pecaSelecionada == NULL ) {
					Peca* peca = jogo->getJogadorPeca( posX, posY );
					if ( peca != NULL ) {
						bool selecionada = this->selecionaPeca( posX, posY, false );				
						if ( selecionada ) {
							jogo->setJogadorJogadaPeca( peca );
							pecaSelecionada = peca;
						}
					}
				} else {							
					Jogada* jogada = jogo->getJogada( posX, posY );
					if ( jogada != NULL ) {				
						jogo->setMovimento( animacao->criaMovimentos( jogada, pecaSelecionada ) );	
					} else {
						jogo->getJogadasPossiveis()->deletaTodasAsJogadas();
						jogo->setJogadorJogadaPeca( NULL );
						pecaSelecionada = NULL;	
					}
				}
			}
		}
	}
	gui->repinta();
}

void JogoGraficoControlador::teclaPressionada( int tecla ) {
	Jogo* jogo = sistema->getJogo();
	GUI* gui = sistema->getGUI();

	if ( jogo->getStatus() == Jogo::NAO_FIM ) {
		if ( tecla == TECLA_ESQ ) {
			jogo->setStatus( Jogo::REINICIAR );
			jogo->setFim( true );
		} else if ( tecla == TECLA_ENTER ) {
			jogo->setPausa( !jogo->isPausa() );
			if ( jogo->isPausa() ) {
				this->setMensagem( "Pausa!", NO_DELAY );
			} else {
				this->removeMensagem();
			}
		}
	} else {
		jogo->setFim( true );
	}		
	gui->repinta();
}

void JogoGraficoControlador::executando() {
	GUI* gui = sistema->getGUI();
	Jogo* jogo = sistema->getJogo();
	JogoAudio* audio = sistema->getJogoAudio();
	Animacao* animacao = sistema->getAnimacao();
	AlgoritmoGerenciador* algGer = sistema->getAlgoritmoGerenciador();

	audio->tocaAudio();

	if ( mensagemDelay != NO_DELAY ) {
		SDL_Delay( mensagemDelay );
		this->removeMensagem();
		mensagemDelay = NO_DELAY;
		return;
	}

	int status = jogo->getStatus();
	if ( status != Jogo::NAO_FIM ) {
		if ( jogo->isFim() ) {
			sistema->reinicia();
			jogo->setFim( false );
			return;
		} else {
			this->setMensagem( "Tecle ou clique para reiniciar.", NO_DELAY );
		}
	}

	if ( jogo->isPausa() )
		return;

	if ( jogo->getMovimento() == NULL ) {
		bool mov = true;
		if ( jogo->isJogadorHumano() )
			mov = jogo->isVezComputador();

		if ( mov && jogo->getStatus() == Jogo::NAO_FIM ) {
			Jogada* jogada;
			int posX, posY;
			
			bool isComp = jogo->isVezComputador();

			bool calculouJogada = algGer->calculaMelhorJogada( &posX, &posY, &jogada, isComp );
			if ( calculouJogada ) {
				Peca* novaPeca = jogo->getPeca( posX, posY )->nova();
				Jogada* novaJog = jogada->nova();
				jogo->setMovimento( animacao->criaMovimentos( novaJog, novaPeca ) );
			} else {
				cout << "Erro no cálculo da melhor jogada." << endl;
				jogo->setFim( true );
			}
		}
	} else {		
		Movimento* movimento = jogo->getMovimento();					
		
		bool animou = animacao->move( movimento, Consts::ANIM_RAIO_INC );
		if ( animou ) {		
			gui->repinta();

			int posX = movimento->getMovimento1()->getPeca()->getPosX();
			int posY = movimento->getMovimento1()->getPeca()->getPosY();

			bool isComp = jogo->isVezComputador();

			Jogada* jogada = movimento->getJogada();
			Peca* peca = jogo->getPeca( posX, posY );

			PecaMov* pmov = new PecaMov( posX, posY, jogada->getPosX(), jogada->getPosY(), isComp );

			jogo->move2( peca, jogada );

			if ( jogada->getCaptura() != NULL ) {
				audio->setNumAudio( JogoAudio::AUDIO_CAPTURA );
			} else {
				if ( jogo->isVezComputador() )
					audio->setNumAudio( JogoAudio::AUDIO_COMP_JOGOU );
				else audio->setNumAudio( JogoAudio::AUDIO_JOG_JOGOU );
			}

			jogo->setUltimoMov( pmov );
			jogo->setVezComputador( !jogo->isVezComputador() );

			peca->setMoveuContador( peca->getMoveuContador() + 1 );

			jogo->getJogadasPossiveis()->deletaTodasAsJogadas();
			jogo->setJogadorJogadaPeca( NULL );
			pecaSelecionada = NULL;

			jogo->setMovimento( NULL );

			status = this->verificaEProcessaXequeMate();
			if ( status == Jogo::NAO_FIM )
				this->verificaSeXeque();
		}						
	}

	gui->repinta();
}

bool JogoGraficoControlador::selecionaPeca( int posX, int posY, bool isComp ) {
	Jogo* jogo = sistema->getJogo();
	JogoAudio* audio = sistema->getJogoAudio();

	Peca* peca = jogo->getPeca( posX, posY );
	if ( peca != NULL ) {
		JogadaLista* lista = jogo->getJogadasPossiveis();
		lista->deletaTodasAsJogadas();
			
		Peca* jogPecas[ Jogo::N_PECAS ];
		Peca* compPecas[ Jogo::N_PECAS ];
		jogo->copia_pecas( jogPecas, compPecas );

		jogo->calculaJogadasPossiveis( lista, jogo, posX, posY, peca->getTipo(), isComp, false );
		jogo->filtraJogadas( lista, jogPecas, compPecas, posX, posY, isComp );
		
		if ( lista->getTam() == 0 ) {
			bool reiEmXeque = jogo->isOutroReiEmXeque( jogPecas, compPecas, !isComp );
			
			std::string msg;
			if ( reiEmXeque ) {			
				msg = "Seu rei está em xeque!";
			} else {
				msg = "Movimento inválido!";
			}
			audio->setNumAudio( JogoAudio::AUDIO_JOGADA_INVALIDA );
			this->setMensagem( msg, MENSAGEM_DELAY );
		}

		jogo->deleta_pecas( jogPecas );
		jogo->deleta_pecas( compPecas );

		return true;
	}
	return false;
}

bool JogoGraficoControlador::verificaSeXeque() {
	Jogo* jogo = sistema->getJogo();
	JogoAudio* audio = sistema->getJogoAudio();

	bool reiEmXeque = jogo->isOutroReiEmXeque( !jogo->isVezComputador() );

	if ( reiEmXeque ) {
		jogo->getJogadasPossiveis()->deletaTodasAsJogadas();
		jogo->setJogadorJogadaPeca( NULL );
		pecaSelecionada = NULL;

		audio->setNumAudio( JogoAudio::AUDIO_XEQUE );
		this->setMensagem( "Xeque!", MENSAGEM_DELAY );
		return true;
	}

	return false;
}

int JogoGraficoControlador::verificaEProcessaXequeMate() {
	Jogo* jogo = sistema->getJogo();
	JogoAudio* audio = sistema->getJogoAudio();

	int status = jogo->isEstaEmXequeMateOuEmpate( true );
	if ( status == Jogo::NAO_FIM )
		status = jogo->isEstaEmXequeMateOuEmpate( false );
	jogo->setStatus( status );

	if ( status != Jogo::NAO_FIM ) {
		std::string mensagem = "";
		int audioNum = JogoAudio::AUDIO_NENHUM;
		switch( status ) {
			case Jogo::JOGADOR_VENCEU:
				jogo->incVitoriasCont( false );
				audioNum = JogoAudio::AUDIO_VENCEU;
				mensagem = "Xeque mate, as brancas venceram!";
				break;
			case Jogo::COMPUTADOR_VENCEU:
				jogo->incVitoriasCont( true );
				mensagem = "Xeque mate, as pretas venceram!";
				audioNum = JogoAudio::AUDIO_PERDEU;
				break;
			case Jogo::EMPATE:
				jogo->incEmpatesCont();
				mensagem = "O jogo empatou!";
				audioNum = JogoAudio::AUDIO_EMPATOU;
				break;
		}

		audio->setNumAudio( audioNum );
		this->setMensagem( mensagem, FIM_JOGO_MENSAGEM_DELAY );
	}
	return status;
}

void JogoGraficoControlador::removeMensagem() {
	GUI* gui = sistema->getGUI();
	JogoGrafico* jogoGrafico = sistema->getJogoGrafico();

	jogoGrafico->getMensagemDesenho()->removeMensagem();
	gui->repinta();
}

void JogoGraficoControlador::setMensagem( std::string mensagem, long delay ) {
	GUI* gui = sistema->getGUI();
	JogoGrafico* jogoGrafico = sistema->getJogoGrafico();

	jogoGrafico->getMensagemDesenho()->setMensagem( mensagem );
	mensagemDelay = delay;

	gui->repinta();
}


