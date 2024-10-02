#include <cstdio>
#include "PlayAudioFile.hpp"
#include "windows.h"

static const char *COUNT_DOWN = "../AudioFiles/countDown.mp3";
static const char *APPLAUSE = "../AudioFiles/applause_y.wav";

int main(int argc, char **argv) {
    PlayAudioFile audio1;
    audio1.loadAudioFile(COUNT_DOWN);

    audio1.playAudio(0);
    Sleep(1200);
    audio1.playAudio(0);
    Sleep(1200);
    audio1.playAudio(0);
    Sleep(1200);
    audio1.playAudio(0);
    Sleep(1200);
    audio1.playAudio(0);
    Sleep(1200);
    audio1.playAudio(0);
    Sleep(1200);

    PlayAudioFile audio2;
    audio2.loadAudioFile(APPLAUSE);

    audio2.playAudio(1);
    Sleep(7000);
    return 0;
}
