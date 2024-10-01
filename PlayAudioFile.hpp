//
// Created by hmkam on 01/10/2024.
//

#ifndef PLAYAUDIOFILE_HPP
#define PLAYAUDIOFILE_HPP



class PlayAudioFile {
public:
    PlayAudioFile();
    virtual ~PlayAudioFile();

    void loadAudioFile(const char * fileName);
    void playAudio(int loops);
};



#endif //PLAYAUDIOFILE_HPP
