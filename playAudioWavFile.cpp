//
// Created by hmkam on 25/09/2024.
//
#include <SDL.h>
#include <SDL_audio.h> // Use SDL_mixer for audio handling
#include <iostream>
#include "playAudioWavFile.hpp"

// https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideaudioexamples.html


#define DEBUG false

#ifdef DEBUG
    #define IFDEBUG if (DEBUG)
#else
    #define IFDEBUG if (false)
#endif


/* The audio function callback takes the following parameters:
   stream:  A pointer to the audio buffer to be filled
   len:     The length (in bytes) of the audio buffer
*/
static uint32_t audio_len;
static uint32_t audio_to_play;
static uint8_t *audio_pos;
static uint8_t *audio_chunk;

SDL_AudioSpec wav_spec;

void fill_audio(void *udata, Uint8 *stream, int len)
{
    /* Only play if we have data left */
    if ( audio_to_play == 0 )
        return;

    /* Mix as much data as possible */
    len = ( len > audio_to_play ? audio_to_play : len );
    SDL_MixAudio(stream, audio_pos, len, 4);
    audio_pos += len;
    audio_to_play -= len;
}

playAudioWavFile::playAudioWavFile() {
}

playAudioWavFile::~playAudioWavFile() {
    // Clean up
    SDL_FreeWAV(audio_chunk);
    SDL_CloseAudio();
    SDL_Quit();
}

AudioReturn playAudioWavFile::loadAudioWavFile(const char * fileType) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return NOT_INITALIZED;
    }

    /* Load the audio data ... */
    // Here you should load your audio data into audio_chunk
    // For example, using SDL_LoadWAV or another method to load audio data
    // For demonstration, let's assume audio_chunk is loaded and audio_len is set

    // Example loading audio data (replace with actual loading code)
    if (SDL_LoadWAV(fileType, &wav_spec, &audio_chunk, &audio_len) == nullptr) {
        std::cerr << "Couldn't load audio file: " << SDL_GetError() << std::endl;
        SDL_CloseAudio();
        SDL_Quit();
        return NO_FILE_LOADED;
    }

    /* Set the audio format */
    wav_spec.samples = 1;  /* Good low-latency value for callback */
    wav_spec.userdata = nullptr;
    wav_spec.callback = fill_audio;

    /* Open the audio device, forcing the desired format */
    if (SDL_OpenAudio(&wav_spec, nullptr) < 0) {
        std::cerr << "Couldn't open audio: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return NO_AUDIO_DEVIC;
    }

    audio_pos = audio_chunk;

    audio_to_play = audio_len;

    return SUCCES;
}

bool playAudioWavFile::playAudio () {

    bool stilPlayingAudio = true;

    /* Wait for sound to complete */
    if (audio_to_play > 0) {

        /* Let the callback function play the audio chunk */
        SDL_PauseAudio(0);

        return stilPlayingAudio;
    }

    return false;
}

void playAudioWavFile::rewindAudio () {

    audio_pos = audio_chunk;

    audio_to_play = audio_len;
}