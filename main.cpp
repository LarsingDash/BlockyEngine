#include <cstdio>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

static const char *MY_COOL_MP3 = "D:/GitHub/BlockyEngine/countDown.mp3";

int main(int argc, char **argv) {
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

    Mix_Chunk *musicChunk = Mix_LoadWAV(MY_COOL_MP3);

    Mix_PlayChannel(-1, musicChunk, 0);
    SDL_Delay(1200);
    Mix_PlayChannel(-1, musicChunk, 0);
    SDL_Delay(1200);
    Mix_PlayChannel(-1, musicChunk, 0);
    SDL_Delay(1200);
    Mix_PlayChannel(-1, musicChunk, 0);
    SDL_Delay(1200);
    Mix_PlayChannel(-1, musicChunk, 0);
    SDL_Delay(1200);
    Mix_PlayChannel(-1, musicChunk, 0);
    SDL_Delay(1200);
    Mix_PlayChannel(-1, musicChunk, 0);

    SDL_Delay(5000);

    Mix_FreeChunk(musicChunk);
    SDL_Quit();
    return 0;
}
