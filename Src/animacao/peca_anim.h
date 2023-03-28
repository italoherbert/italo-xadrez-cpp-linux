
#ifndef PECA_ANIM_H
#define PECA_ANIM_H

#include "../logica/jogada_roque.h"
#include "../logica/jogo.h"
#include "../logica/movimento.h"
#include "../logica/movimentos_simples_lista.h"

class PecaAnim {
	
	private:
		Jogo* jogo;	
	
	public:
		PecaAnim( Jogo* jogo );
		
		int move( MovimentoSimples* movSimples, int raioInc );
		
		void carregaMovsCavalo( Movimento* mov, Peca* peca );
		
		void carregaMovsRoque( Movimento* mov, JogadaRoque* jogR );
		
		void carregaMovsPeca( Movimento* mov, Peca* peca );
		
};

#endif
