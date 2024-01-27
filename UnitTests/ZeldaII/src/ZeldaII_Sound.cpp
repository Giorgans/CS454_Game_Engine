#include "../ZeldaII.h"
#include "../../../Engine/paths.h"
#include <iostream>
#include <map>
#include "../../../Engine/Include/sound.h"
#include <allegro5/allegro_audio.h>
#include "../../../Engine/Include/sprite.h"


ALLEGRO_SAMPLE *LevelSound = nullptr;
ALLEGRO_SAMPLE_INSTANCE *LevelSoundInstance = nullptr;
ALLEGRO_SAMPLE *AttackSound = nullptr;
ALLEGRO_SAMPLE_INSTANCE *AttackSoundInstance = nullptr;
ALLEGRO_SAMPLE *TitleSound = nullptr;
ALLEGRO_SAMPLE_INSTANCE *TitleSoundInstance = nullptr;
ALLEGRO_MIXER *Levelmixer = nullptr;
ALLEGRO_MIXER *SFXmixer = nullptr;
ALLEGRO_MIXER *MasterMixer = nullptr;
ALLEGRO_VOICE *voice = nullptr;

bool PlayedOnce=false;
bool levelSoundPlayed = false;

uint64_t LastTime;
SoundManager& soundManager = SoundManager::getInstance();


void LoadSounds(){

    soundManager.initialize();

    if (!LevelSound) {
        soundManager.loadSound(SoundManager::LEVEL,"level", LEVEL_MUSIC_PATH);
    }

    if (!TitleSound) {
        soundManager.loadSound(SoundManager::LEVEL,"title", TITLE_MUSIC_PATH);
    }

    if (!AttackSound) {
        soundManager.loadSound(SoundManager::SFX,"attack",ATTACK_SOUND);
    }

    soundManager.setVolume(SoundManager::SFX,0.8);
    soundManager.setVolume(SoundManager::LEVEL,0.3);
}

void ZeldaII_Sound() {

    if(inputs.at("A") && (GetGameTime() - LastTime)>(1000/6)/5){
        LastTime = GetGameTime();
        soundManager.playSound("attack",false);
    }

    if(inputs.at("start") && !levelSoundPlayed){
        PlayLevelSound();
        levelSoundPlayed = true;
    }

    if(!PlayedOnce){
        PlayTitleScreenSound();
        PlayedOnce= true;
    }

}

void PlayTitleScreenSound(){
    soundManager.playSound("title",true);
}

void PlayLevelSound() {
    soundManager.stopSound("title");
    soundManager.playSound("level",true);
}
