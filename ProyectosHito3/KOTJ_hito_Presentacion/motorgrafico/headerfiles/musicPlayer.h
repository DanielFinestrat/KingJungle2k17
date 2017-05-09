
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

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
        bool loadSFX(string filename);
        Sound &getSound(string filename);
        Sound &getSFX(string filename);
        
        void playSound(string filename);
        void playSFX(string filename);
        void pauseSound(string filename);
        void stopSound(string filename);
        int getMusicVolume();
        int getSFXVolume();
        void setMusicVolume(int vol);
        void setSFXVolume(int vol);
        void setLoop(string filename);
        


        const string menuMusic;
        const string selecctionMusic;
        const string battleMusic;
        const string elevatorMusic;
        const string shot;
        const string fastReload;
        const string slowReload;
        const string emptyCartridge;
        const string coin1;		
        const string coin2;		
        const string explosion1;		
        const string explosion2;
        const string rocketShoot;
        const string grenadeShoot;
        const string gameOver1;

        

    private:
        map<string, SoundBuffer*> soundBuffers;
        map<string, Sound*> sounds;
        map<string, Sound*> sfx;
        
        int musicVolume;
        int sfxVolume;
        
};

#endif

