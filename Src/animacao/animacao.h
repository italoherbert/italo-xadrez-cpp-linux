
#ifndef ANIMACAO_H
#define ANIMACAO_H

#include "../logica/jogada.h"
#include "../logica/jogada_roque.h"
#include "../logica/movimento.h"
#include "../logica/peca.h"
#include "peca_anim.h"

class Animacao {
	
	private:
		Jogo* jogo;
		PecaAnim* pecaAnim;
		
	public:
		Animacao( Jogo* jogo );
		~Animacao();
		
		bool move( Movimento* movimento, int raioInc );
			
		Movimento* criaMovimentos( Jogada* jogada, Peca* peca );
	
};

#endif
