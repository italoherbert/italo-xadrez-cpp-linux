#include "jogo_audio.h"

#include <SDL2/SDL_mixer.h>

#include <iostream>

void JogoAudio::inicializa() {
	numAudio = AUDIO_NENHUM;		
	
	audioAberturaFundo = Mix_LoadMUS( "audio/abertura-fundo.mid" );
	audioJogoFundo = Mix_LoadMUS( "audio/jogo-fundo.mid" );

	audioJogadorMoveu = Mix_LoadWAV( "audio/jogador-moveu.wav" );
	audioCompMoveu = Mix_LoadWAV( "audio/comp-moveu.wav");
	audioCaptura = Mix_LoadWAV( "audio/captura.wav" );
					
	audioXeque = Mix_LoadWAV( "audio/xeque.wav" );

	audioPerdeu = Mix_LoadWAV( "audio/perdeu.wav" );	
	audioVenceu = Mix_LoadWAV( "audio/venceu.wav" );
	audioEmpatou = Mix_LoadWAV( "audio/empatou.wav");
	
	audioJogadaInvalida = Mix_LoadWAV( "audio/beep.wav");
	
	this->reinicia();
}

void JogoAudio::finaliza() {	
	Mix_FreeMusic( audioAberturaFundo );
	Mix_FreeMusic( audioJogoFundo );
	
	Mix_FreeChunk( audioJogadorMoveu );
	Mix_FreeChunk( audioCompMoveu );
	Mix_FreeChunk( audioCaptura );
		
	Mix_FreeChunk( audioXeque );
	
	Mix_FreeChunk( audioPerdeu );
	Mix_FreeChunk( audioVenceu );
	Mix_FreeChunk( audioEmpatou );
	
	Mix_FreeChunk( audioJogadaInvalida );
}

void JogoAudio::reinicia() {
	if ( Mix_PlayingMusic() ) 
		Mix_HaltMusic();
		
	audioFundo = audioAberturaFundo;
	Mix_PlayMusic( audioFundo, -1 );
}

void JogoAudio::pauseMusica() {
	Mix_PauseMusic();
}

void JogoAudio::resumeMusica() {
	Mix_ResumeMusic();
}

void JogoAudio::setMusica( int musica ) {
	switch( musica ) {
		case AUDIO_FUNDO_ABERTURA:
			if ( Mix_PlayingMusic() )
				Mix_HaltMusic();				
			audioFundo = audioAberturaFundo;
			Mix_PlayMusic( audioFundo, -1 );
			break;
		case AUDIO_FUNDO_JOGO:
			if ( Mix_PlayingMusic() )
				Mix_HaltMusic();				
			audioFundo = audioJogoFundo;
			Mix_PlayMusic( audioFundo, -1 );
			break;
	}	
}

void JogoAudio::tocaAudio() {
	Mix_Chunk* audio = NULL;
	switch( numAudio ) {
		case AUDIO_JOG_JOGOU:
			audio = audioJogadorMoveu;
			break;
		case AUDIO_COMP_JOGOU:
			audio = audioCompMoveu;
			break;
		case AUDIO_CAPTURA:
			audio = audioCaptura;
			break;
		case AUDIO_XEQUE:
			audio = audioXeque;
			break;
		case AUDIO_VENCEU:
			audio = audioVenceu;
			break;
		case AUDIO_PERDEU:
			audio = audioPerdeu;
			break;
		case AUDIO_EMPATOU:
			audio = audioEmpatou;
			break;
		case AUDIO_JOGADA_INVALIDA:
			audio = audioJogadaInvalida;
			break;
	}

	if ( audio != NULL )
		Mix_PlayChannel( -1, audio, 0 );
		
	numAudio = AUDIO_NENHUM;
}

int JogoAudio::getNumAudio() {
	return numAudio;
}

void JogoAudio::setNumAudio( int num ) {
	this->numAudio = num;
}
