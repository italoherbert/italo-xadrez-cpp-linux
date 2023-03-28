
#ifndef CAVALO_PECA_ANIM_H
#define CAVALO_PECA_ANIM_H

#include "peca_anim.h"

class CavaloPecaAnim : public PecaAnim {
	
	public:	
		CavaloPecaAnim( Jogo* jogo );
				
		int move( Movimento* movimento, int raioInc );
	
};

#endif


