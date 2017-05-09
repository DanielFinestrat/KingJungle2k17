#include "../headerfiles/musicPlayer.h"
#include <iostream>

using namespace std;
using namespace sf;

MusicPlayer::MusicPlayer() : menuMusic("resources/music/menuMusic.wav"),
selecctionMusic("resources/music/selecctionMusic.wav"),
battleMusic("resources/music/battleMusic.wav"),
shot("resources/sfx/shot.wav"),
elevatorMusic("resources/music/elevator.wav"),
fastReload("resources/sfx/fastReload.wav"),
slowReload("resources/sfx/slowReload.wav"),
emptyCartridge("resources/sfx/emptyCartridge.wav"),
coin1("resources/sfx/coin1.wav"),
coin2("resources/sfx/coin2.wav"),
explosion1("resources/sfx/explosion1.wav"),
gameOver1("resources/sfx/gameover1.wav"),
rocketShoot("resources/sfx/rocketShoot.wav"),
grenadeShoot("resources/sfx/grenadeShoot.wav"),
explosion2("resources/sfx/explosion2.wav") {
    initialise();
    musicVolume = 5;
    sfxVolume = 5;
    setMusicVolume(0);
    setSFXVolume(0);
}

bool MusicPlayer::initialise() {
    if (loadAll()) {
        return true;
    }
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
    if (!loadSoundBuffer(elevatorMusic)) return false;
    if (!loadSoundBuffer(shot)) return false;
    if (!loadSoundBuffer(fastReload)) return false;
    if (!loadSoundBuffer(slowReload)) return false;
    if (!loadSoundBuffer(coin1)) return false;
    if (!loadSoundBuffer(coin2)) return false;
    if (!loadSoundBuffer(explosion1)) return false;
    if (!loadSoundBuffer(explosion2)) return false;
    if (!loadSoundBuffer(emptyCartridge)) return false;
    if (!loadSoundBuffer(gameOver1)) return false;

    if (!loadSound(menuMusic)) return false;
    if (!loadSound(selecctionMusic)) return false;
    if (!loadSound(battleMusic)) return false;
    if (!loadSound(elevatorMusic)) return false;
    if (!loadSFX(shot)) return false;
    if (!loadSFX(fastReload)) return false;
    if (!loadSFX(slowReload)) return false;
    if (!loadSFX(coin1)) return false;
    if (!loadSFX(coin2)) return false;
    if (!loadSFX(explosion1)) return false;
    if (!loadSFX(explosion2)) return false;
    if (!loadSFX(emptyCartridge)) return false;
    if (!loadSFX(gameOver1)) return false;
    return true;
}

bool MusicPlayer::loadSoundBuffer(string filename) {
    if (soundBuffers.find(filename) != soundBuffers.end()) return false;

    SoundBuffer *soundBuffer = new SoundBuffer();
    err().rdbuf(NULL);

    if (!soundBuffer->loadFromFile(filename)) {
        cout << "ERROR CARGANDO" << endl;
        delete soundBuffer;
        soundBuffer = NULL;
        return false;
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

bool MusicPlayer::loadSound(string filename) {
    if (sounds.find(filename) != sounds.end()) return false;

    Sound *sound = new Sound();
    err().rdbuf(NULL);

    sound->setBuffer(getSoundBuffer(filename));

    sounds.insert(pair<string, Sound*>(filename, sound));

    return true;
}

bool MusicPlayer::loadSFX(string filename) {
    if (sfx.find(filename) != sfx.end()) return false;

    Sound *sound = new Sound();
    err().rdbuf(NULL);

    sound->setBuffer(getSoundBuffer(filename));

    sfx.insert(pair<string, Sound*>(filename, sound));

    return true;
}

Sound &MusicPlayer::getSound(string filename) {
    return *(sounds.find(filename)->second);
}

Sound &MusicPlayer::getSFX(string filename) {
    return *(sfx.find(filename)->second);
}

void MusicPlayer::playSound(string filename) {
    getSound(filename).play();
}

void MusicPlayer::playSFX(string filename) {
    getSFX(filename).play();
}

void MusicPlayer::pauseSound(string filename) {
    getSound(filename).pause();
}

void MusicPlayer::stopSound(string filename) {
    getSound(filename).stop();
}

int MusicPlayer::getMusicVolume() {
    return musicVolume;
}

int MusicPlayer::getSFXVolume() {
    return sfxVolume;
}

void MusicPlayer::setMusicVolume(int vol) {
    map<string, Sound*>::iterator it;
    musicVolume += vol;
    if (musicVolume <= 10 && musicVolume >= 0) {
        for (it = sounds.begin(); it != sounds.end(); it++) {
            /*std::cout << it->first
                      << std::endl ;*/
            getSound(it->first).setVolume(musicVolume * 10);
        }
        //cout << "musica: " << musicVolume * 10 << endl;
    } else musicVolume = (musicVolume > 10) ? 10 : 0;
}

void MusicPlayer::setSFXVolume(int vol) {
    map<string, Sound*>::iterator it;
    sfxVolume += vol;
    if (sfxVolume <= 10 && sfxVolume >= 0) {
        for (it = sfx.begin(); it != sfx.end(); it++) {
            /*std::cout << it->first
                      << std::endl ;*/
            getSFX(it->first).setVolume(sfxVolume * 10);
        }
        //cout << "sfx: " << sfxVolume * 10 << endl;
    } else sfxVolume = (sfxVolume > 10) ? 10 : 0;
}

void MusicPlayer::setLoop(string filename) {
    getSound(filename).setLoop(true);
}

