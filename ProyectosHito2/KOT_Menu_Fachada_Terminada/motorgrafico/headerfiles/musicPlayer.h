
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class MusicPlayer {
    
    public:
        MusicPlayer();
        bool initialise();
        void cleanUp();
        bool loadAll();
        
        bool loadSoundBuffer(string filename);
        SoundBuffer &getSoundBuffer(string filename);
        
        bool loadSound(string filename);
        Sound &getSound(string filename);
        
        void playSound(string filename);
        void pauseSound(string filename);
        void stopSound(string filename);
        void setVolume(string filename, int vol);
        void setLoop(string filename);

        const string menuMusic;
        const string selecctionMusic;
        const string battleMusic;
        const string defeat;
        

    private:
        map<string, SoundBuffer*> soundBuffers;
        map<string, Sound*> sounds;
        
};

#endif

