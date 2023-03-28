
#ifndef JOGO_AUDIO_H
#define JOGO_AUDIO_H

#include <SDL2/SDL_mixer.h>

class JogoAudio {
	
	private:
		int numAudio;
		
		Mix_Music* audioAberturaFundo;
		Mix_Music* audioJogoFundo;		
		Mix_Music* audioFundo;
		
		Mix_Chunk* audioJogadorMoveu;
		Mix_Chunk* audioCompMoveu;
		
		Mix_Chunk* audioCaptura;		
		Mix_Chunk* audioXeque;
		Mix_Chunk* audioPerdeu;
		Mix_Chunk* audioVenceu;
		Mix_Chunk* audioEmpatou;
		Mix_Chunk* audioJogadaInvalida;
		
	public:
		const static int AUDIO_NENHUM = 0;
		const static int AUDIO_JOG_JOGOU = 1;
		const static int AUDIO_COMP_JOGOU = 2;		
		const static int AUDIO_CAPTURA = 3;			
		const static int AUDIO_XEQUE = 4;			
		const static int AUDIO_PERDEU = 5;			
		const static int AUDIO_VENCEU = 6;		
		const static int AUDIO_EMPATOU = 7;
		const static int AUDIO_JOGADA_INVALIDA = 8;
		
		const static int AUDIO_FUNDO_ABERTURA = 9;
		const static int AUDIO_FUNDO_JOGO = 10;

		void inicializa();
		void finaliza();
		
		void reinicia();
		
		void pauseMusica();
		void resumeMusica();
		
		void setMusica( int musica );
		
		void tocaAudio();
		void tocaAudioFundo();
			
		int getNumAudio();
		void setNumAudio( int som );
	
};

#endif
