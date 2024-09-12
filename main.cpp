#include <SDL.h>
#include <SDL_image.h>
#include <SDL_audio.h> // Use SDL_mixer for audio handling

#include <iostream>
#include <cmath>

// https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideaudioexamples.html

static Uint8 *audio_chunk;
static Uint32 audio_len;
static Uint8 *audio_pos;

/* The audio function callback takes the following parameters:
   stream:  A pointer to the audio buffer to be filled
   len:     The length (in bytes) of the audio buffer
*/
void fill_audio(void *udata, Uint8 *stream, int len)
{
    /* Only play if we have data left */
    if (audio_len == 0)
        return;

    /* Mix as much data as possible */
    len = (len > audio_len ? audio_len : len);
    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
    audio_pos += len;
    audio_len -= len;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_AudioSpec wanted;
    // extern void fill_audio(void *udata, Uint8 *stream, int len);

    /* Set the audio format */
    wanted.freq = 22050;
    wanted.format = AUDIO_S16SYS;
    wanted.channels = 2;    /* 1 = mono, 2 = stereo */
    wanted.samples = 1024;  /* Good low-latency value for callback */
    wanted.callback = fill_audio;
    wanted.userdata = NULL;

    /* Open the audio device, forcing the desired format */
    if (SDL_OpenAudio(&wanted, NULL) < 0) {
        std::cerr << "Couldn't open audio: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    /* Load the audio data ... */
    // Here you should load your audio data into audio_chunk
    // For example, using SDL_LoadWAV or another method to load audio data
    // For demonstration, let's assume audio_chunk is loaded and audio_len is set

    // Example loading audio data (replace with actual loading code)
    SDL_AudioSpec wav_spec;
    printf ("D:/GitHub/BlockyEngine/applause_y.wav,  %d,  %d", *audio_chunk, audio_len);
    if (SDL_LoadWAV("D:/GitHub/BlockyEngine/applause_y.wav", &wav_spec, &audio_chunk, &audio_len) == NULL) {
        std::cerr << "Couldn't load audio file: " << SDL_GetError() << std::endl;
        SDL_CloseAudio();
        SDL_Quit();
        return 1;
    }

    audio_pos = audio_chunk;

    /* Let the callback function play the audio chunk */
    SDL_PauseAudio(0);

    /* Wait for sound to complete */
    while (audio_len > 0) {
        SDL_Delay(100);         /* Sleep 1/10 second */
    }

    // Clean up
    SDL_FreeWAV(audio_chunk);
    SDL_CloseAudio();
    SDL_Quit();

    return 0;
}
