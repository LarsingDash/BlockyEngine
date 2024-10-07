#include "PlayAudioFile.hpp"
#include "windows.h"

#include <iostream>

static const char *COUNT_DOWN = "../AudioFiles/countDown.mp3";
static const char *APPLAUSE = "../AudioFiles/applause_y.wav";

void Test_Play_Muliple_Audio_Files() {
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
void Test_Max_Channels() {
    PlayAudioFile audio;
    audio.loadAudioFile("../AudioFiles/1.mp3");
    printf("../AudioFiles/1.mp3\n");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/2.mp3");
    printf("../AudioFiles/2.mp3\n");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/3.mp3");
    printf("../AudioFiles/3.mp3\n");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/4.mp3");
    printf("../AudioFiles/4.mp3\n");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/5.mp3");
    printf("../AudioFiles/5.mp3\n");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/6.mp3");
    printf("../AudioFiles/6.mp3\n");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/7.mp3");
    printf("../AudioFiles/7.mp3\n");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/8.mp3");
    printf("../AudioFiles/8.mp3\n");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/9.mp3");
    printf("../AudioFiles/9.mp3\n");
    audio.playAudio(0);
    Sleep(1000);
    audio.loadAudioFile("../AudioFiles/10.mp3");
    printf("../AudioFiles/10.mp3\n");
    audio.playAudio(0);
    Sleep(1000);
}
void Test_Play_On_Key_Press_Audio_Files() {
    PlayAudioFile audio;
    audio.loadAudioFile("../AudioFiles/1.mp3");

    // C++ Program to Detect Keypress in Windows
    // ggfgc++heahhellogfg
    using namespace std;

    cout << " Press Any Key:" << endl;
    while (true) {
        // Iterate through all possible key codes (0 to 255)
        for (int keyCode = 0; keyCode < 256; ++keyCode) {
            // Check if the key with keyCode is currently
            // pressed
            if (GetAsyncKeyState(keyCode) & 0x8000) {
                // Convert the key code to ASCII character
                char keyChar = static_cast<char>(keyCode);
                cout << "Pressed Key: " << keyChar
                     << " (ASCII value: " << keyCode << ")"
                     << endl;
                audio.playAudio(0);
            }
        }

        // Add a small delay to avoid high CPU usage
        Sleep(100);
    }
}

int main(int argc, char **argv) {
    // Test_Play_Muliple_Audio_Files();
    // Test_Play_Muliple_Audio_Files();
    Test_Play_On_Key_Press_Audio_Files();

    return 0;
}
