#ifndef JOGO_CONSTANTES_H_
#define JOGO_CONSTANTES_H_

class JogoConstantes {

	public:
		const static int NIVEL_HUMANO = 1;
		const static int NIVEL_FACIL = 2;
		const static int NIVEL_NORMAL = 3;
		const static int NIVEL_DIFICIL = 4;

		const static int JOGADOR_VENCEU = 1;
		const static int COMPUTADOR_VENCEU = 2;
		const static int EMPATE = 3;
		const static int REINICIAR = 4;
		const static int NAO_FIM = 0;

		const static int N_PECAS = 16;
		const static int N_JOGADAS_DOMINIO_CENTRO = 6;

		const static int JOGADA_CENTRO_NORMAL = 1;
		const static int JOGADA_CENTRO_SE_NAO_CAPTURADA = 2;

		const static int TORRE = 1;
		const static int CAVALO = 2;
		const static int BISPO = 3;
		const static int RAINHA = 4;
		const static int REI = 5;
		const static int PEAO = 6;

		const static int PECA_REI_INDICE = 4;
		const static int PECA_PEAO_MEIO_ESQ_INDICE = 11;
		const static int PECA_PEAO_MEIO_DIR_INDICE = 12;
		const static int PECA_CAVALO_ESQ_INDICE = 1;
		const static int PECA_CAVALO_DIR_INDICE = 6;
		const static int PECA_BISPO_ESQ_INDICE = 2;
		const static int PECA_BISPO_DIR_INDICE = 5;
		const static int PECA_TORRE_ESQ_INDICE = 0;
		const static int PECA_TORRE_DIR_INDICE = 7;

};



#endif
