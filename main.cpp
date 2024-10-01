#include <iostream>
#include <cmath>
#include<windows.h>

#include "playAudioWavFile.hpp"

/*
 * requirments
 * async non blocking audio playback
 *   send and forget
 * multiple audio sorces simultanias play back
 * ( same instance audio, so no replay, but new instance every time audio chould be played, so no playback is stoped and restarted)
 *
 *
*/

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    playAudioWavFile countDown;
    playAudioWavFile countDown2;
    //playAudioWavFile applause;

    AudioReturn audioReturn;

    audioReturn = countDown.loadAudioWavFile("D:/GitHub/BlockyEngine/countDown.wav");
    if (audioReturn != SUCCES){ return audioReturn;}
    //audioReturn = countDown2.loadAudioWavFile("D:/GitHub/BlockyEngine/countDown.wav");
    //if (audioReturn != SUCCES){ return audioReturn;}
    //audioReturn = applause.loadAudioWavFile("D:/GitHub/BlockyEngine/applause_y.wav");
    //if (audioReturn != SUCCES){ return audioReturn;}

    countDown.playAudio();
    //applause.playAudio();

    printf("playing audio 2x\n");

    int milliseconds = 3000;
    Sleep(milliseconds);

    countDown.rewindAudio();
    //countDown2.rewindAudio();
    //applause.rewindAudio();

    countDown.playAudio();
    //countDown2.playAudio();
    //applause.playAudio();

    milliseconds = 2000;
    Sleep(milliseconds);

    return 0;
}
