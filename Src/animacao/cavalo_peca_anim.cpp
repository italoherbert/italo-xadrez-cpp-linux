#include "cavalo_peca_anim.h"

#include <cmath>

#include "../logica/jogada.h"

CavaloPecaAnim::CavaloPecaAnim( Jogo* jogo ) : PecaAnim( jogo ) {
	
}

int CavaloPecaAnim::move( Movimento* movimento, int raioInc ) {
	int d1 = PecaAnim::move( movimento->getMovimento1(), raioInc );
	int d2 = PecaAnim::move( movimento->getMovimento2(), raioInc );
	return d1+d2;
}
