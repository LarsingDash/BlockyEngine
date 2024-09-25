//
// Created by hmkam on 25/09/2024.
//

#include <cstdint>

#ifndef PLAYAUDIOWAVFILE_HPP
#define PLAYAUDIOWAVFILE_HPP

enum AudioReturn {
    SUCCES,             //
    NOT_INITALIZED,     // Couldn't initialize SDL
    NO_FILE_LOADED,     // Couldn't load audio file
    NO_AUDIO_DEVIC      // Couldn't open audio
};

class playAudioWavFile {
public:
    playAudioWavFile();
    virtual ~playAudioWavFile();

    AudioReturn loadAudioWavFile(const char * fileName);
    AudioReturn playAudio();


private:
    //void fill_audio(void *udata, Uint8 *stream, int len);
};

#endif //PLAYAUDIOWAVFILE_HPP
