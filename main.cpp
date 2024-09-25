#include <iostream>
#include <cmath>

#include "playAudioWavFile.hpp"


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    playAudioWavFile wavFile;

    AudioReturn audioReturn;

    //audioReturn = wavFile.loadAudioWavFile("D:/GitHub/BlockyEngine/applause_y.wav");
    //if (audioReturn != SUCCES){ return audioReturn;}
    audioReturn = wavFile.loadAudioWavFile("D:/GitHub/BlockyEngine/countDown.wav");
    if (audioReturn != SUCCES){ return audioReturn;}
    audioReturn = wavFile.playAudio();
    if (audioReturn != SUCCES){ return audioReturn;}

    return 0;
}
