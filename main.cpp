#include <cstdio>
#include "PlayAudioFile.hpp"
#include "windows.h"

static const char *COUNT_DOWN = "../AudioFiles/countDown.mp3";
static const char *APPLAUSE = "../AudioFiles/applause_y.wav";

void Test_Play() {
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
}

int main(int argc, char **argv) {



    PlayAudioFile audio;
    audio.loadAudioFile("../AudioFiles/1.mp3");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/2.mp3");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/3.mp3");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/4.mp3");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/5.mp3");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/6.mp3");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/7.mp3");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/8.mp3");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/9.mp3");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/10.mp3");
    audio.playAudio(0);
    Sleep(1000);
    return 0;
}
