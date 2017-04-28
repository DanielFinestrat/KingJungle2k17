#include "../headerfiles/musicPlayer.h"
#include <iostream>

using namespace std;
using namespace sf;

MusicPlayer::MusicPlayer(): menuMusic("./resources/music/menuMusic.wav"),
                            selecctionMusic("./resources/music/selecctionMusic.wav"),
                            battleMusic("./resources/music/battleMusic.wav"),
                            shot("resources/sfx/shot.wav"),
                            fastReload("resources/sfx/fastReload.wav"),
                            slowReload("resources/sfx/slowReload.wav"),
                            emptyCartridge("resources/sfx/emptyCartridge.wav"){
    initialise();
}

bool MusicPlayer::initialise() {
    if (loadAll()) { return true; }
    return false;
}

void MusicPlayer::cleanUp() {
    map<string, SoundBuffer*>::iterator snd_it;
    for (snd_it = soundBuffers.begin(); snd_it != soundBuffers.end(); snd_it++) {
        delete snd_it->second;
        snd_it->second = NULL;
    }
    soundBuffers.clear();
}

bool MusicPlayer::loadAll() {
    if (!loadSoundBuffer(menuMusic)) return false;
    if (!loadSoundBuffer(selecctionMusic)) return false;
    if (!loadSoundBuffer(battleMusic)) return false;
    if (!loadSoundBuffer(shot)) return false;
    if (!loadSoundBuffer(fastReload)) return false;
    if (!loadSoundBuffer(slowReload)) return false;
    if (!loadSoundBuffer(emptyCartridge)) return false;
    
    if (!loadSound(menuMusic)) return false;
    if (!loadSound(selecctionMusic)) return false;
    if (!loadSound(battleMusic)) return false;
    if (!loadSound(shot)) return false;
    if (!loadSound(fastReload)) return false;
    if (!loadSound(slowReload)) return false;
    if (!loadSound(emptyCartridge)) return false;
  return true;
}

bool MusicPlayer::loadSoundBuffer(string filename){
    if (soundBuffers.find(filename) != soundBuffers.end()) return false;

    SoundBuffer *soundBuffer = new SoundBuffer();
    err().rdbuf(NULL);

    if (!soundBuffer->loadFromFile(filename)) {
        cout<<"ERROR CARGANDO"<<endl;
        delete soundBuffer; soundBuffer = NULL; return false;
    }
    
    Sound toPlay;
    toPlay.setBuffer(*soundBuffer);
    //toPlay.setBuffer(*soundBuffers.find(filename)->second);
    toPlay.play();
    
    soundBuffers.insert(pair<string, SoundBuffer*>(filename, soundBuffer));

    return true;
}

SoundBuffer &MusicPlayer::getSoundBuffer(string filename) {
    return *(soundBuffers.find(filename)->second);
}

bool MusicPlayer::loadSound(string filename){
    if (sounds.find(filename) != sounds.end()) return false;

    Sound *sound = new Sound();
    err().rdbuf(NULL);

    sound->setBuffer(getSoundBuffer(filename));
    
    sounds.insert(pair<string, Sound*>(filename, sound));

    return true;
}

Sound &MusicPlayer::getSound(string filename) {
    return *(sounds.find(filename)->second);
}

void MusicPlayer::playSound(string filename) {
    getSound(filename).play();
}

void MusicPlayer::pauseSound(string filename){
    getSound(filename).pause();
}

void MusicPlayer::stopSound(string filename){
    getSound(filename).stop();
}

void MusicPlayer::setVolume(string filename, int vol){
    getSound(filename).setVolume(vol);
}

void MusicPlayer::setLoop(string filename){
    getSound(filename).setLoop(true);
}