//
// Created by hmkam on 01/10/2024.
//

#include "PlayAudioFile.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

#define DEBUG false

#ifdef DEBUG
    #define IFDEBUG if (DEBUG)
#else
    #define IFDEBUG if (false)
#endif

Mix_Chunk *musicChunk;

PlayAudioFile::PlayAudioFile() {
}

PlayAudioFile::~PlayAudioFile() {
    Mix_FreeChunk(musicChunk);
    SDL_Quit();
}

void PlayAudioFile::loadAudioFile(const char * fileName) {
    int result = 0;
    int flags = MIX_INIT_MP3;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }

    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);

    musicChunk = Mix_LoadWAV(fileName);
}

void PlayAudioFile::playAudio (int loops) {
    Mix_PlayChannel(-1, musicChunk, loops);
}