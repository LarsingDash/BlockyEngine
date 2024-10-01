#include <iostream>
#include <cmath>
#include<windows.h>

#include "playAudioWavFile.hpp"


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    playAudioWavFile wavFile;

    AudioReturn audioReturn;

    //audioReturn = wavFile.loadAudioWavFile("D:/GitHub/BlockyEngine/applause_y.wav");
    //if (audioReturn != SUCCES){ return audioReturn;}
    audioReturn = wavFile.loadAudioWavFile("D:/GitHub/BlockyEngine/countDown.wav");
    if (audioReturn != SUCCES){ return audioReturn;}

    wavFile.playAudio();

    printf("playing audio 2x\n");


    wavFile.playAudio();

    int milliseconds = 5000;
    Sleep(milliseconds);

    wavFile.rewindAudio();

    wavFile.playAudio();

    milliseconds = 7000;
    Sleep(milliseconds);

    return 0;
}
